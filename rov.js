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
    case    'Pong':
      rovdata.Pong = res[1];
      console.log('Serial DEBUG: ' + line);
      break;
    case    'Pressure':
      rovdata.Pressure = res[1];
      break;
    case    'Temp_OUT':
      rovdata.Temp_OUT = res[1];
      break;
    case    'Temp_IN':
      rovdata.Temp_IN = res[1];
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
    case    'ACCL_X':
      rovdata.Accl_X = res[1];
      break;
    case    'ACCL_Y':
      rovdata.Accl_Y = res[1];
      break;
    case    'ACCL_Z':
      rovdata.Accl_Z = res[1];
      console.log('Accl DEBUG: ' + rovdata.Accl_X + ' ' + rovdata.Accl_Y + ' ' + rovdata.Accl_Z);
      break;
    case    'Heading':
      rovdata.Heading = res[1];
      break;
    case    'Roll':
      rovdata.Roll = res[1];
      break;
    case    'Pitch':
      rovdata.Pitch = res[1];
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
//  console.log('Serial DEBUG: ' + line);
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
  rovdata.Temp_OUT = 0;
  rovdata.Temp_IN = 0;
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
        port.write('Hover:'+'-1\n');
      } else { 
        rovdata.Hover = true;
        rovdata.Hoverset = rovdata.Depth
        port.write('Hover:'+rovdata.Depth+'\n');
      } 
    }
// B Button
    if ((res[1] == 1) && (res[3] == 1)) {
      console.log ('Gamepad Button B');
      if (rovdata.Pilot) {
        rovdata.Pilot = false;
        port.write('Pilot:'+'-1\n');
      } else { 
        rovdata.Pilot = true;
        rovdata.Pilotset = rovdata.X
        port.write('Pilot:'+rovdata.X+'\n');
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
    if ((res[1] == 6) && (res[3] > 50)) { event = 'Strafe_l'; };
    if (arduino) {
      if (event != last_event) {
        port.write(event+':'+res[3]+'\n');
        last_event = event;
      }
    }
    if ((res[1] == 7) && (res[3] > 50)) { event = 'Strafe_r'; };
    if (arduino) {
      if (event != last_event) {
        port.write(event+':'+res[3]+'\n');
        last_event = event;
      }
    }
// 12 Pad up
    if ((res[1] == 12) && (res[3] == 1)) {
    console.log('12 Pad up, pressed');
    if (rovdata.Hover == true) {
      rovdata.Hoverset--;
      port.write('Hover:'+rovdata.Hoverset+'\n');
    } else {
      if (rovdata.Camx_move == 0) {
        if (rovdata.Camx_pos > 1100) {
          rovdata.Camx_pos -= 100;
          port.write('Camx:'+rovdata.Camx_pos+'\n');
        }
      }
      rovdata.Camx_move = 1;
    }
  }
    if ((res[1] == 12) && (res[3] == 0)) {
    console.log('12 Pad up, released');
      rovdata.Camx_move = 0;
    }
// 13 Pad down
    if ((res[1] == 13) && (res[3] == 1)) {
    if (rovdata.Hover == true) {
      rovdata.Hoverset++;
      port.write('Hover:'+rovdata.Hoverset+'\n');
    } else {
      if (rovdata.Camx_move == 0) {
        if (rovdata.Camx_pos < 1900) {
          rovdata.Camx_pos += 100;
          port.write('Camx:'+rovdata.Camx_pos+'\n');
        }
      }
      rovdata.Camx_move = 1;
    }
   }
    if ((res[1] == 13) && (res[3] == 0)) {
      rovdata.Camx_move = 0;
    }
// 14 Pad left
    if ((res[1] == 14) && (res[3] == 1)) {
      console.log('14 Pad right, pressed');
      if (rovdata.Pilot == true) {
        rovdata.Pilotset--;
        if (rovdata.Pilotset < 0) {
          rovdata.Pilotset = 359;
        }
        port.write('Pilot:'+rovdata.Pilotset+'\n');
      } else {
        if (rovdata.Camy_move == 0) {
          if (rovdata.Camy_pos > 1100) {
            rovdata.Camy_pos -= 100;
            port.write('Camy:'+rovdata.Camy_pos+'\n');
          }
        }
        rovdata.Camy_move = 1;
      }
    }
    if ((res[1] == 14) && (res[3] == 0)) {
      console.log('14 Pad up, released');
      rovdata.Camy_move = 0;
    }
// 15 Pad right
    if ((res[1] == 15) && (res[3] == 1)) {
      if (rovdata.Pilot == true) {
        rovdata.Pilotset++
        if (rovdata.Pilotset > 359) {
          rovdata.Pilotset = 0;
        }
        port.write('Pilot:'+rovdata.Pilotset+'\n');
      } else {
        if (rovdata.Camy_move == 0) {
          if (rovdata.Camy_pos < 1900) {
            rovdata.Camy_pos += 100;
            port.write('Camy:'+rovdata.Camx_pos+'\n');
          }
        }
        rovdata.Camy_move = 1;
      }
    }
    if ((res[1] == 15) && (res[3] == 0)) {
      rovdata.Camy_move = 0;
    }
  };

  if (res[0] == "axis") {
    event = 'Stop';
// Axis 0 (LS hor)
    if ((res[1] == 0) && (res[3] > 50)) { event = 'Right'; };
    if ((res[1] == 0) && (res[3] < -50)) { event = 'Left'; };
// Axis 1 (LS vert)
    if ((res[1] == 1) && (res[3] > 50)) { event = 'Reverse'; };
    if ((res[1] == 1) && (res[3] < -50)) { event = 'Forward'; };
// Axis 2 (RS hor)
    if ((res[1] == 2) && (res[3] > 50)) { event = 'Roll_r'; };
    if ((res[1] == 2) && (res[3] < -50)) { event = 'Roll_l'; };
// Axis 3 (RS vert)
    if ((res[1] == 3) && (res[3] > 50)) { event = 'Dive'; };
    if ((res[1] == 3) && (res[3] < -50)) { event = 'Up'; };
  
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
  port.write('PING:0\n');
}, 200);

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

}); /// END io.connection

server.listen(80, function () {

  var host = server.address().address
  var port = server.address().port

  console.log("Moki-ROV2 Started, listening at http://%s:%s", config.network.ipaddr, port);
})

