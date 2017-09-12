var express = require('express');
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var fs = require("fs")
var shell = require("shelljs");
var jsonfile = require('jsonfile')
jsonfile.spaces = 4
var serialport = require('serialport');
var winston = require('winston');
require('winston-logstash');
var logger = new (winston.Logger);
var config_file = 'config.js'
var config = jsonfile.readFileSync(config_file)

//
// Write datalog to filefile (see config.js)
//
if (config.datalogger.logfile == true) {
    logger.add(winston.transports.File, {
        filename: config.datalogger.logfile_name,
        json: true,
        maxsize: config.datalogger.maxsize,
        maxfiles: config.datalogger.maxfiles,
        colorize: false
    });
}

//
// Write datalog to logstash (see config.js)
//
if (config.datalogger.logstash == true) {
    logger.add(winston.transports.Logstash, {
        json: true,
        port: config.datalogger.port,
        node_name: config.datalogger.nodename,
        host: config.datalogger.host 
    });
}

//
// Setup rovdata struct, for storing rovdata
//
var rovdata = {};

//
// Init rovdata vars
//
rovdata.Version = shell.cat('VERSION').stdout.trim();
rovdata.Hover = false;
rovdata.Power = 0;
rovdata.Pilot = false;
rovdata.Depth_Offset = 0;
rovdata.Armed = 0;
rovdata.Thruster_1 = 0;
rovdata.Thruster_2 = 0;
rovdata.Thruster_3 = 0;
rovdata.Thruster_4 = 0;
rovdata.Thruster_5 = 0;
rovdata.Thruster_6 = 0;

//
// arduino found (or not)
//
var arduino = 0;

//
// Camera setup
//
var kill = shell.exec(config.camera.kill, {silent:true, async:true});
var camera = shell.exec(config.camera.command+" -o \""+config.camera.output+"\" -i \""+config.camera.input+"\"", {silent:true, async:true});
rovdata.Camx_pos = 1600;
rovdata.Camx_move = 0;

//
// Serialport vars
//
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

//
// Parse the data from the serialline, from arduino
//
function parse_serial(line) {
    line = line.replace(/[\r$]/g, '');
    var res = line.split(":");
    switch(res[0]) {
      case    'Time':
          rovdata.Time = Number(res[1]);
          break;
      case    'Ping':
          rovdata.Ping = 1;
          break;
      case    'Pong':
          rovdata.Pong = 1;
          break;
      case    'Pressure':
          rovdata.Pressure = Number(res[1]);
          break;
      case    'Hover_Gag':
          rovdata.Hover_Gap = Number(res[1]);
          break;
      case    'Hover_Input':
          rovdata.Hover_Input = Number(res[1]);
          break;
      case    'Hover_Output':
          rovdata.Hover_Output = Number(res[1]);
          break;
      case    'Hover_Setpoint':
          rovdata.Hover_Setpoint = Number(res[1]);
          break;
      case    'Hover_Up':
          rovdata.Hover_Up = Number(res[1]);
          break;
      case    'Hover_Dive':
          rovdata.Hover_Dive = Number(res[1]);
          break;
      case    'Pilot_Gap':
          rovdata.Pilot_Gap = Number(res[1]);
          break;
      case    'Pilot_Heading_Input':
          rovdata.Pilot_Input = Number(res[1]);
          break;
      case    'Pilot_Heading_Output':
          rovdata.Pilot_Output = Number(res[1]);
          break;
      case    'Pilot_Heading_Setpoint':
          rovdata.Pilot_Setpoint = Number(res[1]);
          break;
      case    'Pilot_Heading_Output_Left':
          rovdata.Pilot_Left = Number(res[1]);
          break;
      case    'Pilot_Heading_Output_Right':
          rovdata.Pilot_Right = Number(res[1]);
          break;
      case    'Temp_Out':
          rovdata.Temp_Out = Number(res[1]);
          break;
      case    'Temp_In':
          rovdata.Temp_In = Number(res[1]);
          break;
      case    'Depth':
          rovdata.Depth = Number(res[1] - rovdata.Depth_Offset);
          break;
      case    'Altitude':
          rovdata.Altitude = Number(res[1]);
          break;
      case    'X':
          rovdata.X = Number(res[1]);
          break;
      case    'Y':
          rovdata.Y = Number(res[1]);
          break;
      case    'Z':
          rovdata.Z = Number(res[1]);
          break;
      case    'ACCL_X':
          rovdata.Accl_X = Number(res[1]);
          break;
      case    'ACCL_Y':
          rovdata.Accl_Y = Number(res[1]);
          break;
      case    'ACCL_Z':
          rovdata.Accl_Z = Number(res[1]);
          break;
      case    'Heading':
          rovdata.Heading = Number(res[1]);
          break;
      case    'Roll':
          rovdata.Roll = Number(res[1]);
          break;
      case    'Pitch':
          rovdata.Pitch = Number(res[1]);
          break;
      case    'Sys':
          rovdata.Sys = Number(res[1]);
          break;
      case    'Gyro':
          rovdata.Gyro = Number(res[1]);
          break;
      case    'Accel':
          rovdata.Accel = Number(res[1]);
          break;
      case    'Mag':
          rovdata.Mag = Number(res[1]);
          break;
      case    'Volt':
          rovdata.Volt = Number(res[1]);
          break;
      case    'Amps':
          rovdata.Amps = Number(res[1]);
          break;
      case    'Power':
          rovdata.Power = Number(res[1]);
          break;
      case    'Thruster_1':
          rovdata.Thruster_1 = Number(res[1]);
          break;
      case    'Thruster_2':
          rovdata.Thruster_2 = Number(res[1]);
          break;
      case    'Thruster_3':
          rovdata.Thruster_3 = Number(res[1]);
          break;
      case    'Thruster_4':
          rovdata.Thruster_4 = Number(res[1]);
          break;
      case    'Thruster_5':
          rovdata.Thruster_5 = Number(res[1]);
          break;
      case    'Thruster_6':
          rovdata.Thruster_6 = Number(res[1]);
          break;
      case    'Stop':
          rovdata.Thruster_1 = 0;
          rovdata.Thruster_2 = 0;
          rovdata.Thruster_3 = 0;
          rovdata.Thruster_4 = 0;
          rovdata.Thruster_5 = 0;
          rovdata.Thruster_6 = 0;
          break;
      default:
          console.log('Serial data: '+line);
    }
// Check IMU calibration 
    if (rovdata.Sys != 3 && rovdata.Gyro != 3 && rovdata.Accel != 3 && rovdata.Mag != 3) {
        rovdata.Calibrated = 0; 
    } else {
        rovdata.Calibrated = 1; 
    }

// 
// Write logdata to logger
//
    logger.log('info', rovdata);
}

// 
// If we opened the serialport, we can expect data from it.
//
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
    rovdata.Temp_Out = 0;
    rovdata.Temp_In = 0;
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

//
// Socket.io to HTML5 webclient
//
io.on('connection', function (socket) {
    socket.emit('connect');

//
// Button pushed on HTML5 webclient
//
var buttonctrl = function(button_data) {
    if (button_data == 'zero_depth') {
        rovdata.Depth_Offset = rovdata.Depth;
    } 
};

//
// Gamepadcontroller data recieved from HTML5 webclient
//
var gamepadctrl = function(gamepad) {
    var res = gamepad.split(" ");
    if (res[0] == "button") {
// A Button
        if ((res[1] == 0) && (res[3] == 1)) {
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
            if (rovdata.Pilot) {
                rovdata.Pilot = false;
                port.write('Pilot:'+'400\n');
            } else { 
                rovdata.Pilot = true;
                rovdata.Pilotset = rovdata.Heading;
                port.write('Pilot:'+rovdata.Heading+'\n');
            } 
        }
// X Button
        if ((res[1] == 2) && (res[3] == 1)) {
            rovdata.Power = 0;
            if (arduino) {
                port.write('Power:'+rovdata.Power+'\n');
            }
        }
//Y Button
        if ((res[1] == 3) && (res[3] == 1)) {
            lights();
        }
//View (8) Button
        if ((res[1] == 8) && (res[3] == 1)) {
            disarmmotor();
        }
//Menu (9) Button
        if ((res[1] == 9) && (res[3] == 1)) {
            armmotor();
        }
// LB Button
        if ((res[1] == 4) && (res[3] == 1)) {
            if (rovdata.Power > 0) {
                rovdata.Power = parseInt(rovdata.Power, 10) - 10;
            }
            if (arduino) {
                port.write('Power:'+rovdata.Power+'\n');
            }
        }
// RB Button
        if ((res[1] == 5) && (res[3] == 1)) {
            if (rovdata.Power < 100) {
                rovdata.Power = parseInt(rovdata.Power, 10) + 10;
            }
            if (arduino) {
                port.write('Power:'+rovdata.Power+'\n');
            }
        }
// 6 Left trigger (0-100)
        event = 'Stop';
        if ((res[1] == 6) && (res[3] > 50)) {
            event = 'Strafe_l';
        }
        if (arduino) {
            if (event != last_event) {
                port.write(event+':'+res[3]+'\n');
                last_event = event;
            }
        }
// 7 Right trigger (0-100)
        if ((res[1] == 7) && (res[3] > 50)) {
           event = 'Strafe_r';
        }
        if (arduino) {
            if (event != last_event) {
                port.write(event+':'+res[3]+'\n');
                last_event = event;
            }
        }
// 12 Pad up
        if ((res[1] == 12) && (res[3] == 1)) {
            if (rovdata.Hover == true) {
                rovdata.Hoverset--;
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
        if ((res[1] == 12) && (res[3] == 0)) {
            rovdata.Camx_move = 0;
        }
// 13 Pad down
        if ((res[1] == 13) && (res[3] == 1)) {
            if (rovdata.Hover == true) {
                rovdata.Hoverset++;
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
        if ((res[1] == 13) && (res[3] == 0)) {
            rovdata.Camx_move = 0;
        }
// 14 Pad left
        if ((res[1] == 14) && (res[3] == 1)) {
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
        if ((res[1] == 0) && (res[3] > 50)) {
            event = 'Right';
        };
        if ((res[1] == 0) && (res[3] < -50)) {
           event = 'Left';
        };
// Axis 1 (LS vert)
        if ((res[1] == 1) && (res[3] > 50)) {
            event = 'Reverse';
        };
        if ((res[1] == 1) && (res[3] < -50)) {
            event = 'Forward';
        };
// Axis 2 (RS hor)
        if ((res[1] == 2) && (res[3] > 50)) {
            event = 'Roll_r';
        };
        if ((res[1] == 2) && (res[3] < -50)) {
            event = 'Roll_l';
        };
// Axis 3 (RS vert)
        if ((res[1] == 3) && (res[3] > 50)) {
            event = 'Dive';
        };
        if ((res[1] == 3) && (res[3] < -50)) {
            event = 'Up';
        };
  
        if (arduino) {
            if (event != last_event) {
                port.write(event+':'+res[3]+'\n');
                rovdata.event = event;
                last_event = event;
            }
        }
    };
}

//  
// when the user disconnects.. perform this
//
socket.on('disconnect', function () {
});

//
// Send rovdata to HTML5 client, every 200ms
//
var interval = setInterval(function () {
    socket.emit("rovdata", rovdata);
}, 200);

//
// Send PING to arduino, every 2500ms
//
var ping_interval = setInterval(function () {
    port.write('Ping:0\n');
}, 2500);

//
// Recieved gamepad data from HTML5 client
//
socket.on('gamepad', function(data) {
    gamepadctrl(data);
});

//
// Recieved button data from HTML5 client
//
socket.on('button', function(data) {
    buttonctrl(data);
});

//
// Recieved keyboard data from HTML5 client
//
socket.on('keydown', function(event) {
  socket.emit("command",event);
  switch (event) {
      case 'abort':
          rovdata.Motor = false;
          port.write('DISARM:0'+'\n');
          break;
      }
});

//
// Lights function
//
var lights = function() {
    if (rovdata.Lights == false) {
        if (arduino) {
            port.write('Light1:1\n');
            port.write('Light2:1\n');
        }
        rovdata.Lights = true;
    } else {
        if (arduino) {
            port.write('Light1:0\n');
            port.write('Light2:0\n');
        }
        rovdata.Lights = false;
    }
}

//
// Thruster ARM
//
var armmotor = function() {
    rovdata.Armed = 1;
    port.write('ARM:1'+'\n');
}

//
// Thruster DISARM
//
var disarmmotor = function() {
    rovdata.Armed = 0;
    port.write('DISARM:0'+'\n');
    rovdata.Power = 0;
    port.write('Power:'+rovdata.Power+'\n');
}

}); /// END io.connection

server.listen(80, function () {
    var host = server.address().address
    var port = server.address().port
    console.log("Moki-ROV2 Started, listening at http://%s:%s", config.network.ipaddr, port);
})

