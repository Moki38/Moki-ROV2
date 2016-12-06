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

var rovdata = {};

rovdata.Hover = false;
rovdata.Power = 0;
rovdata.Lights = false;
rovdata.Pilot = false;
rovdata.Motor = false;

var hoverset = 0;
var pilotset = 0;

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

var kill = shell.exec('kill -9 `pidof mjpg_streamer`', {silent:true, async:true});
var camera = shell.exec('/usr/local/bin/mjpg_streamer -o \"output_http.so -w /root/mjpg-streamer/mjpg-streamer-experimental/www\" -i \"input_raspicam.so -x 1366 -y 768\"', {silent:true, async:true});

rovdata.Camx_pos = 1500;
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
      rovdata.Depth = res[1];
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
  res.end(req.cookies);

  config.i2c = {device: '/dev/i2c-1'}
  
  config.serial = {device: '/dev/ttyACM0'}

  ipaddr = shell.exec('hostname -I', {silent:true}).stdout
  ipaddr = ipaddr.replace(/[\n$]/g, '');
  config.network = {ipaddr : ipaddr}
  jsonfile.writeFileSync( __dirname + '/' + config_file , config)
})

io.on('connection', function (socket) {
  socket.emit('connect');

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
// 15 Pad right

// Axis 0 (LS hor)
// Axis 1 (LS vert)
// Axis 2 (RS hor)
// Axis 3 (RS vert)
  };

  if (res[0] == "axis") {
    event = 'Stop';
    if ((res[1] == 0) && (res[3] > 30)) { event = 'Right'; };
    if ((res[1] == 0) && (res[3] < -30)) { event = 'Left'; };
    if ((res[1] == 1) && (res[3] > 30)) { event = 'Reverse'; };
    if ((res[1] == 1) && (res[3] < -30)) { event = 'Forward'; };
    if ((res[1] == 2) && (res[3] > 30)) { event = 'Strafe_r'; };
    if ((res[1] == 2) && (res[3] < -30)) { event = 'Strafe_l'; };
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
  if (rovdata.Hover) {
    hover();
  };
}, 500);

socket.on('gamepad', function(data) {
  gamepadctrl(data);
});

var lights = function() {
  if (rovdata.Lights == false) {
    console.log("LIGHTS: ON");
    if (arduino) {
      port.write('Light1:1600'+'\n');
      port.write('Light2:1600'+'\n');
    }
    socket.emit("command","Light ON");
    rovdata.Lights = true;
  } else {
    console.log("LIGHTS: OFF");
    if (arduino) {
      port.write('Light1:1000'+'\n');
      port.write('Light2:1000'+'\n');
    }
    socket.emit("command","Light Off");
    rovdata.Lights = false;
  }
}

var armmotor = function() {
    console.log("MOTOR: ON");
    rovdata.Motor = true;
    port.write('ARM:1'+'\n');
    socket.emit("command","Motor ON");
}

var disarmmotor = function() {
    console.log("MOTOR: OFF");
    rovdata.Motor = false;
    port.write('DISARM:0'+'\n');
    socket.emit("command","Motor OFF");
}

var hover = function() {
  if (hoverset < rovdata.Depth) {
    console.log("HOVER: UP");
  } 
  if (hoverset > rovdata.Depth) {
    console.log("HOVER: DOWN");
  } 
}

}); /// END io.connection

server.listen(80, function () {

  var host = server.address().address
  var port = server.address().port

  console.log("Moki-ROV2 Started, listening at http://%s:%s", host, port);
})

