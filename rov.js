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

var arduino = 0;
var port;

var SerialPort = require('serialport');
if (shell.test('-c', config.serial.device)) {
  port = new SerialPort(config.serial.device, {
    baudrate: 9600,
    parser: SerialPort.parsers.readline('\n')
  });
  arduino = 1;
}

var kill = shell.exec('kill -9 `pidof mjpg_streamer`', {silent:true, async:true});
var camera = shell.exec('/usr/local/bin/mjpg_streamer -o \"output_http.so -w /root/mjpg-streamer/mjpg-streamer-experimental/www\" -i \"input_raspicam.so -x 1366 -y 768\"', {silent:true, async:true});

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
//  port.write('SER1:100');
}

if (arduino) {
port.on('data', function(line) {
  parse_serial(line);
});
}

app.use(express.static('public'));

app.get('/', function(req, res) {
  res.sendfile('index.html')
})

app.get('/config', function(req, res) {
  res.end(req.cookies);

  config.i2c = {device: '/dev/i2c-1'}
  
  config.serial = {device: '/dev/ttyACM0'}

  ipaddr = shell.exec('hostname -i', {silent:true}).stdout
  ipaddr = ipaddr.replace(/[\n$]/g, '');
  config.network = {ipaddr : ipaddr}
  jsonfile.writeFileSync( __dirname + '/' + config_file , config)
})

io.on('connection', function (socket) {
//  console.log('connecting');
  socket.emit('connect');
  
// when the user disconnects.. perform this
  socket.on('disconnect', function () {
  });

var interval = setInterval(function () {
  socket.emit("rovdata", rovdata);
  if (rovdata.hover) {
    hover();
  };
  lights();
}, 500);

socket.on('gamepad', function(gamepad) {
  gamepadctrl(gamepad);
});

socket.on('power', function(data) {
  power = data;
//  console.log('Power request: %d', data);
  if (power == 0) {
    motor_stop();
  }
});

var lights = function() {
   if (rovdata.lights) {
     console.log("LIGHTS: ON");
    if (arduino) {
      port.write('Light1:1600');
      port.write('Light2:1600');
    }
     socket.emit("command","Light ON");
   } else {
     socket.emit("command","Light Off");
    if (arduino) {
      port.write('Light1:1600');
      port.write('Light2:1600');
    }
   }
   lightsonce = true;
}

var motor = function() {
      if (!motoronce) {
        if (rovdata.motor) {
          console.log("MOTOR: ON");
          port.write('ARM');
          socket.emit("command","Motor ON");
        } else {
          console.log("Motor: OFF");
          port.write('DISARM');
          socket.emit("command","Motor Off");
        }
      motoronce = true;
      }
}

var hover = function() {
   if (hoverset < rovdata.depth) {
      console.log("HOVER: UP");
  } 
   if (hoverset > rovdata.depth) {
      console.log("HOVER: DOWN");
  } 
}


var motor_stop = function() {
  console.log("motor", "stopall");
    if (arduino) {
      port.write('STOP:1');
    }
  socket.emit("motor", "stopall");
}

var motor_1 = function(position) {
    if (arduino) {
      port.write('Motor1:'+position);
    }
  console.log("motor1", position);
  socket.emit("motor1", position);
}

var motor_2 = function(position) {
    if (arduino) {
      port.write('Motor2:'+position);
    }
  console.log("motor2", position);
  socket.emit("motor2", position);
}

var motor_3 = function(position) {
    if (arduino) {
      port.write('Motor3:'+position);
    }
  console.log("motor3", position);
  socket.emit("motor3", position);
}

var motor_4 = function(position) {
    if (arduino) {
      port.write('Motor4:'+position);
    }
  console.log("motor4", position);
  socket.emit("motor4", position);
}
});

server.listen(3000, function () {

  var host = server.address().address
  var port = server.address().port

  console.log("Moki-ROV2 Started, listening at http://%s:%s", host, port);
})

