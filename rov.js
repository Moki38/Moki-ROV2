var express = require('express');
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var fs = require("fs")
var shell = require("shelljs");
var jsonfile = require('jsonfile')
jsonfile.spaces = 4
var serialport = require('serialport');

var config_file = 'config.js'
var config = jsonfile.readFileSync(config_file)

//console.log(config);

var rovdata = {};

rovdata.Config = false;

rovdata.Hover = false;
rovdata.Power = 0;
rovdata.Lights = false;
rovdata.Pilot = false;
rovdata.Motor = false;
rovdata.Depth_Offset = 0;

var hoverset = 0;
var hoverevent = 'Stop';
var pilotset = 0;
var pilotevent = 'Stop';

var arduino = 0;
var port;
  
var event;
var last_event;

var SerialPort = require('serialport');
if (shell.test('-c', config.serial.device)) {
  port = new SerialPort(config.serial.device, {
    baudrate: 115200,
    parser: SerialPort.parsers.readline('\n')
  });
  arduino = 1;
}

var kill = shell.exec(config.camera.kill, {silent:true, async:true});
var camera = shell.exec(config.camera.command+" -o \""+config.camera.output+"\" -i \""+config.camera.input+"\"", {silent:true, async:true});

rovdata.Camx_pos = 1600;
rovdata.Camx_move = 0;

camera.stdout.on('data', function(data) {
  console.log(data);
  /* ... do something with data ... */
});

function parse_serial(line) {
  var res = line.split(":");
  switch(res[0]) {
    case    'Time':
      rovdata.Time = res[1];
      break;
    case    'Pressure':
      rovdata.Pressure = res[1];
      break;
    case    'Temperature':
      rovdata.Temperature = res[1];
      break;
    case    'Depth':
      rovdata.Depth = res[1] - rovdata.Depth_Offset;
      break;
    case    'Altitude':
      rovdata.Altitude = res[1];
      break;
    case    'X':
      rovdata.X = res[1];
      break;
    case    'Y':
      rovdata.Y = res[1];
      break;
    case    'Z':
      rovdata.Z = res[1];
      break;
    case    'Sys':
      rovdata.Sys = res[1];
      break;
    case    'Gyro':
      rovdata.Gyro = res[1];
      break;
    case    'Accel':
      rovdata.Accel = res[1];
      break;
    case    'Mag':
      rovdata.Mag = res[1];
      break;
    case    'Volt':
      rovdata.Volt = res[1];
      break;
    case    'Amps':
      rovdata.Amps = res[1];
      break;
    case    'Motor_1':
      rovdata.Motor_1 = res[1];
      break;
    case    'Motor_1_RPM':
      rovdata.Motor_1_RPM = res[1];
      break;
    case    'Motor_1_V':
      rovdata.Motor_1_V = res[1];
      break;
    case    'Motor_1_A':
      rovdata.Motor_1_A = res[1];
      break;
    case    'Motor_1_Temp':
      rovdata.Motor_1_Temp = res[1];
      break;
    case    'Motor_2':
      rovdata.Motor_2 = res[1];
      break;
    case    'Motor_2_RPM':
      rovdata.Motor_2_RPM = res[1];
      break;
    case    'Motor_2_V':
      rovdata.Motor_2_V = res[1];
      break;
    case    'Motor_2_A':
      rovdata.Motor_2_A = res[1];
      break;
    case    'Motor_2_Temp':
      rovdata.Motor_2_Temp = res[1];
      break;
    case    'Motor_3':
      rovdata.Motor_3 = res[1];
      break;
    case    'Motor_3_RPM':
      rovdata.Motor_3_RPM = res[1];
      break;
    case    'Motor_3_V':
      rovdata.Motor_3_V = res[1];
      break;
    case    'Motor_3_A':
      rovdata.Motor_3_A = res[1];
      break;
    case    'Motor_3_Temp':
      rovdata.Motor_3_Temp = res[1];
      break;
    case    'Motor_4':
      rovdata.Motor_4 = res[1];
      break;
    case    'Motor_4_RPM':
      rovdata.Motor_4_RPM = res[1];
      break;
    case    'Motor_4_V':
      rovdata.Motor_4_V = res[1];
      break;
    case    'Motor_4_A':
      rovdata.Motor_4_A = res[1];
      break;
    case    'Motor_4_Temp':
      rovdata.Motor_4_Temp = res[1];
      break;
    case    'Motor_5':
      rovdata.Motor_5 = res[1];
      break;
    case    'Motor_5_RPM':
      rovdata.Motor_5_RPM = res[1];
      break;
    case    'Motor_5_V':
      rovdata.Motor_5_V = res[1];
      break;
    case    'Motor_5_A':
      rovdata.Motor_5_A = res[1];
      break;
    case    'Motor_5_Temp':
      rovdata.Motor_5_Temp = res[1];
      break;
    case    'Motor_6':
      rovdata.Motor_6 = res[1];
      break;
    case    'Motor_6_RPM':
      rovdata.Motor_6_RPM = res[1];
      break;
    case    'Motor_6_V':
      rovdata.Motor_6_V = res[1];
      break;
    case    'Motor_6_A':
      rovdata.Motor_6_A = res[1];
      break;
    case    'Motor_6_Temp':
      rovdata.Motor_6_Temp = res[1];
      break;
    case    'Stop':
      rovdata.Motor_1 = 0;
      rovdata.Motor_2 = 0;
      rovdata.Motor_3 = 0;
      rovdata.Motor_4 = 0;
      rovdata.Motor_5 = 0;
      rovdata.Motor_6 = 0;
      break;
    default:
      console.log('Serial data: ' + line);
  }
}

if (arduino) {
  port.on('data', function(line) {
  parse_serial(line);
});

} else {
// No Arduino found
  rovdata.Volt = 'N/A';
  rovdata.Amps = 'N/A';
  rovdata.X = 0;
  rovdata.Y = 0;
  rovdata.Z = 0;
  rovdata.Depth = 0;
  rovdata.Temperature = 0;
}

app.use(express.static('public'));

app.get('/', function(req, res) {
  res.sendfile('index.html')
})

app.get('/config', function(req, res) {

  if (req.query.action) {
    if (req.query.action == 'edit') {
      res.sendFile("config.html", {"root": __dirname+'/public'});

    } else if (req.query.action == 'read') {
      config = jsonfile.readFileSync(config_file)

    } else if (req.query.action == 'write') {
      jsonfile.writeFileSync( __dirname + '/' + config_file , config)

    } else if (req.query.action == 'init') {
      config.i2c = {device: '/dev/i2c-1'}
      config.serial = {device: '/dev/ttyACM0'}
      ipaddr = shell.exec('hostname -i', {silent:true}).stdout
      ipaddr = ipaddr.replace(/[\n$]/g, '');
      config.network = {ipaddr : ipaddr}
      jsonfile.writeFileSync( __dirname + '/' + config_file , config)
    }
  }
  res.end();
})

io.on('connection', function (socket) {
  socket.emit('connect');

var buttonctrl = function(button_data) {
  console.log('buttonctrl ' + button_data);
  if (button_data == 'zero_depth') {
    rovdata.Depth_Offset = rovdata.Depth;
  } 
};

var gamepadctrl = function(gamepad) {
  var res = gamepad.split(" ");
  if (res[0] == "button") {
// A Button
    if ((res[1] == 0) && (res[3] == 1)) {
  console.log ('Gamepad Button A');
      if (rovdata.Hover) {
        rovdata.Hover = false;
      } else { 
        rovdata.Hover = true;
        hoverset = rovdata.Depth
      } 
    }
// B Button
    if ((res[1] == 1) && (res[3] == 1)) {
  console.log ('Gamepad Button B');
      if (rovdata.Pilot) {
        rovdata.Pilot = false;
      } else { 
        rovdata.Pilot = true;
        pilotset = rovdata.X
      } 
    }
// X Button
    if ((res[1] == 2) && (res[3] == 1)) {
      console.log ('Gamepad Button X');
      rovdata.Power = 0;
      if (arduino) {
        port.write('Power:'+rovdata.Power+'\n');
      }
    }
//Y Button
    if ((res[1] == 3) && (res[3] == 1)) {
  console.log ('Gamepad Button Y');
      lights();
    }
//View (8) Button
    if ((res[1] == 8) && (res[3] == 1)) {
      console.log('VIEW Button, pressed');
      disarmmotor();
    }
//Menu (9) Button
    if ((res[1] == 9) && (res[3] == 1)) {
      console.log('MENU Button, pressed');
      armmotor();
    }
// LB Button
    if ((res[1] == 4) && (res[3] == 1)) {
      console.log('LB Button, pressed');
      if (rovdata.Power > 0) {
        rovdata.Power = rovdata.Power - 10;
      }
      if (arduino) {
        port.write('Power:'+rovdata.Power+'\n');
      }
    }
// RB Button
    if ((res[1] == 5) && (res[3] == 1)) {
      console.log('RB Button, pressed');
      if (rovdata.Power < 100) {
        rovdata.Power = rovdata.Power + 10;
      }
      if (arduino) {
        port.write('Power:'+rovdata.Power+'\n');
      }
    }
// 6 Left trigger (0-100)
// 7 Right trigger (0-100)
    event = 'Stop';
    if ((res[1] == 6) && (res[3] > 30)) { event = 'Roll_l'; };
    if (arduino) {
      if (event != last_event) {
        port.write(event+':'+res[3]+'\n');
        last_event = event;
      }
    }
    if ((res[1] == 7) && (res[3] > 30)) { event = 'Roll_r'; };
    if (arduino) {
      if (event != last_event) {
        port.write(event+':'+res[3]+'\n');
        last_event = event;
      }
    }
// 12 Pad up
    if ((res[1] == 12) && (res[3] == 1)) {
    console.log('12 Pad up, pressed');
      if (rovdata.Camx_move == 0) {
        if (rovdata.Camx_pos > 1100) {
          rovdata.Camx_pos -= 100;
          port.write('Camx:'+rovdata.Camx_pos+'\n');
        }
      }
      rovdata.Camx_move = 1;
    }
    if ((res[1] == 12) && (res[3] == 0)) {
    console.log('12 Pad up, released');
      rovdata.Camx_move = 0;
    }
// 13 Pad down
    if ((res[1] == 13) && (res[3] == 1)) {
      if (rovdata.Camx_move == 0) {
        if (rovdata.Camx_pos < 1900) {
          rovdata.Camx_pos += 100;
          port.write('Camx:'+rovdata.Camx_pos+'\n');
        }
      }
      rovdata.Camx_move = 1;
    }
    if ((res[1] == 13) && (res[3] == 0)) {
      rovdata.Camx_move = 0;
    }
// 14 Pad left
    if ((res[1] == 14) && (res[3] == 1)) {
    console.log('14 Pad right, pressed');
      if (rovdata.Camy_move == 0) {
        if (rovdata.Camy_pos > 1100) {
          rovdata.Camy_pos -= 100;
          port.write('Camy:'+rovdata.Camy_pos+'\n');
        }
      }
      rovdata.Camy_move = 1;
    }
    if ((res[1] == 14) && (res[3] == 0)) {
    console.log('14 Pad up, released');
      rovdata.Camy_move = 0;
    }
// 15 Pad right
    if ((res[1] == 15) && (res[3] == 1)) {
      if (rovdata.Camy_move == 0) {
        if (rovdata.Camy_pos < 1900) {
          rovdata.Camy_pos += 100;
          port.write('Camy:'+rovdata.Camx_pos+'\n');
        }
      }
      rovdata.Camy_move = 1;
    }
    if ((res[1] == 15) && (res[3] == 0)) {
      rovdata.Camy_move = 0;
    }
  };

  if (res[0] == "axis") {
    event = 'Stop';
// Axis 0 (LS hor)
    if ((res[1] == 0) && (res[3] > 30)) { event = 'Right'; };
    if ((res[1] == 0) && (res[3] < -30)) { event = 'Left'; };
// Axis 1 (LS vert)
    if ((res[1] == 1) && (res[3] > 30)) { event = 'Reverse'; };
    if ((res[1] == 1) && (res[3] < -30)) { event = 'Forward'; };
// Axis 2 (RS hor)
    if ((res[1] == 2) && (res[3] > 30)) { event = 'Strafe_r'; };
    if ((res[1] == 2) && (res[3] < -30)) { event = 'Strafe_l'; };
// Axis 3 (RS vert)
    if ((res[1] == 3) && (res[3] > 30)) { event = 'Dive'; };
    if ((res[1] == 3) && (res[3] < -30)) { event = 'Up'; };
  
    if (arduino) {
      if (event != last_event) {
        port.write(event+':'+res[3]+'\n');
        last_event = event;
      }
    }
  };
}
  
// when the user disconnects.. perform this
socket.on('disconnect', function () {
});

var interval = setInterval(function () {
  socket.emit("rovdata", rovdata);
  if (rovdata.Config == false) {
    push_config();
  };
  if (rovdata.Hover) {
    hover();
  };
  if (rovdata.Pilot) {
    pilot();
  };
}, 500);

socket.on('gamepad', function(data) {
  gamepadctrl(data);
});

socket.on('button', function(data) {
  buttonctrl(data);
});

socket.on('keydown', function(event) {
  socket.emit("command",event);
  switch (event) {
    case 'abort':
      rovdata.Motor = false;
      port.write('DISARM:0'+'\n');
      break;
  }
});

var push_config = function() {

  console.log('Push Config');

  rovdata.Config = true;
// Motor
  if (arduino) {
    if (config.motor[1].host == 'ARDUINO') {
      port.write('CFG_M1_PROTO:'+config.motor[1].proto+'\n');
      if (config.motor[1].proto == 1) {
        port.write('CFG_M1_ADDR:'+config.motor[1].pin+'\n');
      }
      if (config.motor[1].proto == 2) {
        port.write('CFG_M1_POLE:'+config.motor[1].pole+'\n');
        port.write('CFG_M1_ADDR:'+config.motor[1].address+'\n');
      }
      port.write('CFG_M1_N:'+config.motor[1].neutral+'\n');
      port.write('CFG_M1_MIN:'+config.motor[1].min+'\n');
      port.write('CFG_M1_MAX:'+config.motor[1].max+'\n');
      port.write('CFG_M1_REV:'+config.motor[1].reverse+'\n');
      port.write('CFG_M1_DIR:'+config.motor[1].direction+'\n');
    }
    if (config.motor[2].host == 'ARDUINO') {
      port.write('CFG_M2_PROTO:'+config.motor[2].proto+'\n');
      if (config.motor[2].proto == 1) {
        port.write('CFG_M2_ADDR:'+config.motor[2].pin+'\n');
      }
      if (config.motor[2].proto == 2) {
        port.write('CFG_M2_POLE:'+config.motor[2].pole+'\n');
        port.write('CFG_M2_ADDR:'+config.motor[2].address+'\n');
      }
      port.write('CFG_M2_N:'+config.motor[2].neutral+'\n');
      port.write('CFG_M2_MIN:'+config.motor[2].min+'\n');
      port.write('CFG_M2_MAX:'+config.motor[2].max+'\n');
      port.write('CFG_M2_REV:'+config.motor[2].reverse+'\n');
      port.write('CFG_M2_DIR:'+config.motor[2].direction+'\n');
    }
    if (config.motor[3].host == 'ARDUINO') {
      port.write('CFG_M3_PROTO:'+config.motor[3].proto+'\n');
      if (config.motor[3].proto == 1) {
        port.write('CFG_M3_ADDR:'+config.motor[3].pin+'\n');
      }
      if (config.motor[3].proto == 2) {
        port.write('CFG_M3_POLE:'+config.motor[3].pole+'\n');
        port.write('CFG_M3_ADDR:'+config.motor[3].address+'\n');
      }
      port.write('CFG_M3_N:'+config.motor[3].neutral+'\n');
      port.write('CFG_M3_MIN:'+config.motor[3].min+'\n');
      port.write('CFG_M3_MAX:'+config.motor[3].max+'\n');
      port.write('CFG_M3_REV:'+config.motor[3].reverse+'\n');
      port.write('CFG_M3_DIR:'+config.motor[3].direction+'\n');
    }
    if (config.motor[4].host == 'ARDUINO') {
      port.write('CFG_M4_PROTO:'+config.motor[4].proto+'\n');
      if (config.motor[4].proto == 1) {
        port.write('CFG_M4_ADDR:'+config.motor[4].pin+'\n');
      }
      if (config.motor[4].proto == 2) {
        port.write('CFG_M4_POLE:'+config.motor[4].pole+'\n');
        port.write('CFG_M4_ADDR:'+config.motor[4].address+'\n');
      }
      port.write('CFG_M4_N:'+config.motor[4].neutral+'\n');
      port.write('CFG_M4_MIN:'+config.motor[4].min+'\n');
      port.write('CFG_M4_MAX:'+config.motor[4].max+'\n');
      port.write('CFG_M4_REV:'+config.motor[4].reverse+'\n');
      port.write('CFG_M4_DIR:'+config.motor[4].direction+'\n');
    }
    if (config.motor[5].host == 'ARDUINO') {
      port.write('CFG_M5_PROTO:'+config.motor[5].proto+'\n');
      if (config.motor[5].proto == 1) {
        port.write('CFG_M5_ADDR:'+config.motor[5].pin+'\n');
      }
      if (config.motor[5].proto == 2) {
        port.write('CFG_M5_POLE:'+config.motor[5].pole+'\n');
        port.write('CFG_M5_ADDR:'+config.motor[5].address+'\n');
      }
      port.write('CFG_M5_N:'+config.motor[5].neutral+'\n');
      port.write('CFG_M5_MIN:'+config.motor[5].min+'\n');
      port.write('CFG_M5_MAX:'+config.motor[5].max+'\n');
      port.write('CFG_M5_REV:'+config.motor[5].reverse+'\n');
      port.write('CFG_M5_DIR:'+config.motor[5].direction+'\n');
    }
    if (config.motor[6].host == 'ARDUINO') {
      port.write('CFG_M6_PROTO:'+config.motor[6].proto+'\n');
      if (config.motor[6].proto == 1) {
        port.write('CFG_M6_ADDR:'+config.motor[6].pin+'\n');
      }
      if (config.motor[6].proto == 2) {
        port.write('CFG_M6_POLE:'+config.motor[6].pole+'\n');
        port.write('CFG_M6_ADDR:'+config.motor[6].address+'\n');
      }
      port.write('CFG_M6_N:'+config.motor[6].neutral+'\n');
      port.write('CFG_M6_MIN:'+config.motor[6].min+'\n');
      port.write('CFG_M6_MAX:'+config.motor[6].max+'\n');
      port.write('CFG_M6_REV:'+config.motor[6].reverse+'\n');
      port.write('CFG_M6_DIR:'+config.motor[6].direction+'\n');
    }
    port.write('MOTOR_SETUP:1\n');
  
// Light

    if (config.light[1].host == 'ARDUINO') {
      port.write('CFG_L1_PROTO:'+config.light[1].proto+'\n');
      if (config.light[1].proto == 'PWM') {
        port.write('CFG_L1_ADDR:'+config.light[1].pin+'\n');
      }
      if (config.light[1].proto == 'I2C') {
        port.write('CFG_L1_ADDR:'+config.light[1].address+'\n');
      }
      port.write('CFG_L1_ON:'+config.light[1].on+'\n');
      port.write('CFG_L1_OFF:'+config.light[1].off+'\n');
    }

    if (config.light[2].host == 'ARDUINO') {
      port.write('CFG_L2_PROTO:'+config.light[2].proto+'\n');
      if (config.light[2].proto == 'PWM') {
        port.write('CFG_L2_ADDR:'+config.light[2].pin+'\n');
      }
      if (config.light[2].proto == 'I2C') {
        port.write('CFG_L2_ADDR:'+config.light[2].address+'\n');
      }
      port.write('CFG_L2_ON:'+config.light[2].on+'\n');
      port.write('CFG_L2_OFF:'+config.light[2].off+'\n');
    }
    port.write('LIGHT_SETUP:1\n');

// Sensors
    if (config.sensor.IMU.host == 'ARDUINO') {
      if (config.sensor.IMU.proto == 'PWM') {
        port.write('CFG_IMU_ADDR:'+config.sensor.IMU.pin+'\n');
        port.write('CFG_IMU_PROTO:1\n');
      }
      if (config.sensor.IMU.proto == 'I2C') {
        port.write('CFG_IMU_ADDR:'+config.sensor.IMU.address+'\n');
        port.write('CFG_IMU_PROTO:2\n');
      }
      if (config.sensor.IMU.type == 'BNO055') {
        port.write('CFG_IMU_TYPE:1\n');
      }
    }
    port.write('IMU_SETUP:1\n');

    if (config.sensor.DEPTH.host == 'ARDUINO') {
      if (config.sensor.DEPTH.proto == 'PWM') {
        port.write('CFG_DEPTH_ADDR:'+config.sensor.DEPTH.pin+'\n');
        port.write('CFG_DEPTH_PROTO:1\n');
      }
      if (config.sensor.DEPTH.proto == 'I2C') {
        port.write('CFG_DEPTH_ADDR:'+config.sensor.DEPTH.address+'\n');
        port.write('CFG_DEPTH_PROTO:2\n');
      }
      if (config.sensor.DEPTH.type == 'MS5837') {
        port.write('CFG_DEPTH_TYPE:1\n');
      }
    }
    port.write('DEPTH_SETUP:1\n');

    if (config.sensor.CURRENT.host == 'ARDUINO') {
      if (config.sensor.CURRENT.proto == 'ANALOG') {
        port.write('CFG_CURRENT_ADDR:'+config.sensor.CURRENT.pin+'\n');
        port.write('CFG_CURRENT_PROTO:3\n');
      }
      if (config.sensor.CURRENT.type == 'ATTOPILOT_A180') {
        port.write('CFG_CURRENT_TYPE:1\n');
      }
    }
    port.write('CURRENT_SETUP:1\n');

    if (config.sensor.AMP.host == 'ARDUINO') {
      if (config.sensor.AMP.proto == 'ANALOG') {
        port.write('CFG_AMP_ADDR:'+config.sensor.AMP.pin+'\n');
        port.write('CFG_AMP_PROTO:3\n');
      }
      if (config.sensor.AMP.type == 'ATTOPILOT_A180') {
        port.write('CFG_AMP_TYPE:1\n');
      }
    }
    port.write('AMP_SETUP:1\n');

// Camera Tilt

    if (config.camera.tilt.x.host == 'ARDUINO') {
      port.write('CFG_CX_PROTO:'+config.camera.tilt.x.proto+'\n');
      if (config.camera.tilt.x.proto == 'PWM') {
        port.write('CFG_CX_ADDR:'+config.camera.tilt.x.pin+'\n');
      }
      if (config.light[2].proto == 'I2C') {
        port.write('CFG_CX_ADDR:'+config.camera.tilt.x.address+'\n');
      }
      port.write('CFG_CX_N:'+config.camera.tilt.x.neutral+'\n');
      port.write('CFG_CX_MIN:'+config.camera.tilt.x.on+'\n');
      port.write('CFG_CX_MAX:'+config.camera.tilt.x.off+'\n');
    }

    port.write('CAM_SETUP:1\n');
  } // Arduino
}

var lights = function() {
  if (rovdata.Lights == false) {
    console.log("LIGHTS: ON");
    if (arduino) {
      port.write('Light1:'+config.light[1].on+'\n');
      port.write('Light2:'+config.light[2].on+'\n');
    }
    rovdata.Lights = true;
  } else {
    console.log("LIGHTS: OFF");
    if (arduino) {
      port.write('Light1:'+config.light[1].off+'\n');
      port.write('Light2:'+config.light[1].off+'\n');
    }
    rovdata.Lights = false;
  }
}

var armmotor = function() {
    console.log("MOTOR: ON");
    rovdata.Motor = true;
    port.write('ARM:1'+'\n');
}

var disarmmotor = function() {
    console.log("MOTOR: OFF");
    rovdata.Motor = false;
    port.write('DISARM:0'+'\n');
}

var pilot = function() {
  if (pilotset < rovdata.X) {
    console.log("PILOT: RIGHT");
    event = 'Right';
    if (arduino) {
      port.write(event+':30\n');
    } 
  }
  if (pilotset > rovdata.X) {
    console.log("PILOT: LEFT");
    event = 'Left';
    if (arduino) {
      port.write(event+':30\n');
    } 
  } 
  if (pilotset ) {
    event = 'Stop';
    if (arduino) {
      port.write(event+':1\n');
    } 
  } 
}

var hover = function() {
  if (hoverset < (rovdata.Depth-5)) {
    console.log("HOVER: UP");
    hoverevent = event = 'Up';
    if (arduino) {
      port.write(event+':30\n');
    } 
  }
  if (hoverset > (rovdata.Depth+5)) {
    console.log("HOVER: DOWN");
    hoverevent = event = 'Dive';
    if (arduino) {
      port.write(event+':30\n');
    } 
  } 
  if (hoverset) {
    if (hoverevent != 'Stop') {
      hoverevent = event = 'Stop';
      if (arduino) {
        port.write(event+':1\n');
      } 
    } 
  }
}

}); /// END io.connection

server.listen(80, function () {

  var host = server.address().address
  var port = server.address().port

  console.log("Moki-ROV2 Started, listening at http://%s:%s", host, port);
})

