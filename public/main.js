var socket = io.connect();

aIsDown = false;

$(window).keydown(function(e){
  switch(e.which){
    case 65:
      if(aIsDown) return;
      aIsDown = true;
      socket.emit('keydown', 'abort');
      break;
   }
});

$(window).keyup(function(e){
  switch(e.which){
    case 65:
      if(!aIsDown) return;
      aIsDown = false;
      socket.emit('keyup', 'abort');
      break;
   }
});

$(window).resize(function(){location.reload();});

var rov_canvas = document.getElementById('rovCanvas');
var rov_context = rov_canvas.getContext('2d');

rov_canvas.width = window.innerWidth;
rov_canvas.height = window.innerHeight;

var constatus = "Not connected";
var connected = false;

var x = 80;
var y = 30;

var rovdata = {};

var mbar = 0;
var temp = 0;
var depth = 0;
var heading = 0;
var pitch = 0;
var roll = 0;
var volt_raw = 0;
var volt = 0;
var current_raw = 0;
var current = 0;
var lights = false;
var hover = false;
var pilot = false;
var pilotset = 0;

var power = 0;
var motor = 0;
var motor_1 = 0;
var motor_2 = 0;
var motor_3 = 0;
var motor_4 = 0;
var motor_5 = 0;
var motor_6 = 0;

var gamepad_detected = false;
var gamepadSupportAvailable = navigator.getGamepads || !!navigator.webkitGetGamepads || !!navigator.webkitGamepads;
var button_pressed = new Array(16);
var button_value = new Array(16);
var axis_value = new Array(16);

function zero_depth_window() {
  socket.emit("button","zero_depth");
}


function zeroPad(num, places) {
  var zero = places - num.toString().length + 1;
  return Array(+(zero > 0 && zero)).join("0") + num;
}

function readgamepad() {
  var value;
  var pressed;
  var gamepad = navigator.getGamepads()[0];
  var axes = gamepad.axes.length;
  var buttons = gamepad.buttons.length;
  if (gamepad) {
//       socket.emit("gamepad","gamepad loop");
// Init
    if (!gamepad_detected) { 
//       socket.emit("gamepad",gamepad.id);
//       socket.emit("gamepad","index "+gamepad.index);
//       socket.emit("gamepad",axes+" Axes" );
//       socket.emit("gamepad",buttons+" Buttons" );
       for (i=0 ; i < axes ; i++) {
         axis_value[i] = 0.0;
       }
       for (i=0 ; i < buttons ; i++) {
         button_value[i] = 0.0;
       }
       gamepad_detected = true;
    }
    // Check button
    for (i=0 ; i <= gamepad.buttons.length ; i++) {
      if (typeof(gamepad.buttons[i]) == 'object') {
        value = gamepad.buttons[i].value;
        pressed = gamepad.buttons[i].pressed;
        if (i == 6 || i == 7) {
          if (value > (button_value[i]+0.1)) {
            button_value[i] = value;
            socket.emit("gamepad","button "+i+" value "+Math.floor(value*100));
          }
          if (value < (button_value[i]-0.1)) {
            button_value[i] = value;
            socket.emit("gamepad","button "+i+" value "+Math.floor(value*100));
          }
        } else {
          if (pressed) {
            if (!button_pressed[i]) {
              socket.emit("gamepad","button "+i+" value "+value);
              button_pressed[i] = true;
            }
          } else {
            if (button_pressed[i]) {
              socket.emit("gamepad","button "+i+" value 0");
              button_pressed[i] = false;
            }
          }
        }
      }
    }
    for (i=0 ; i < axes ; i++) {
      value = gamepad.axes[i];
      if (gamepad.axes[i] > axis_value[i]+0.5) {
         axis_value[i] = gamepad.axes[i];
         socket.emit("gamepad","axis "+i+" value "+Math.floor(gamepad.axes[i]*100));
      }
      if (gamepad.axes[i] < axis_value[i]-0.5) {
         axis_value[i] = gamepad.axes[i];
         socket.emit("gamepad","axis "+i+" value "+Math.floor(gamepad.axes[i]*100));
      }
    }
  }  
}

function update(rovdata) {
  var t;

  version = rovdata.Version;
  mbar = rovdata.Pressure;
  t = rovdata.Depth;
  depth = t.toFixed(2);
  temp_out = rovdata.Temp_Out;
  temp_in = rovdata.Temp_In;
  volt = rovdata.Volt;
  current = rovdata.Amps;
  calibrated = rovdata.Calibrated;
  heading = Math.floor(rovdata.Heading);
  pitch = Math.floor(rovdata.Pitch);
  roll = Math.floor(rovdata.Roll);
  imusys = rovdata.Sys;
  imugyro = rovdata.Gyro;
  imuaccel = rovdata.Accel;
  imumag = rovdata.Mag;
  accl_x = rovdata.Accl_X;
  accl_y = rovdata.Accl_Y;
  accl_z = rovdata.Accl_Z;
  pilot = rovdata.Pilot;
  pilotset = Math.floor(rovdata.Pilotset);
  hover = rovdata.Hover;
  hoverset = Math.floor(rovdata.Hoverset);
  hover = rovdata.Hover;
  lights = rovdata.Lights;
  power = rovdata.Power;
  motor = rovdata.Motor;
  camx = rovdata.Camx_pos-1500;

  motor_1 = rovdata.Motor_1;
  motor_2 = rovdata.Motor_2;
  motor_3 = rovdata.Motor_3;
  motor_4 = rovdata.Motor_4;
  motor_5 = rovdata.Motor_5;
  motor_6 = rovdata.Motor_6;
}

function display(rovdata) {
  var today=new Date().toISOString().replace(/T/, ' ').replace(/\..+/, '')
  rov_context.clearRect(0, 0, rov_canvas.width, rov_canvas.height);
  rov_context.font = '14pt Verdana';
  rov_context.lineWidth = 1;
  rov_context.fillStyle = "#aaaa55";
  rov_context.fillText( today, 10, 20);
  rov_context.fillText( "GPS: N/A", 10, 40);
  rov_context.fillText( "Moki ROV (Raspberry PI)", 10, 60);
  if (constatus == 'Disonnected') {
    rov_context.beginPath();
    rov_context.fillStyle = "#aa0000";
    rov_context.font = '20pt Verdana';
    rov_context.fillText("DISCONNECTED", (rov_canvas.width/2-110), rov_canvas.height/2-140);
    rov_context.fill();
  }

  rov_context.font = '14pt Verdana';
  rov_context.fillStyle = "#aaaa55";
  rov_context.fillText( "Main V", (rov_canvas.width/4), 20);
  rov_context.fillText( "Main A", (rov_canvas.width/4), 40);
  rov_context.fillText( ": "+volt, (rov_canvas.width/4)+80, 20);
  rov_context.fillText( ": "+current, (rov_canvas.width/4)+80, 40);
  rov_context.fillText( "Power ", (rov_canvas.width/4) , 60);
  rov_context.fillText( ":", (rov_canvas.width/4) + 80, 60);
  rov_context.fill();
  rov_context.beginPath();
  if (motor) {
    rov_context.fillStyle = "#00aa00";
    rov_context.fillText( "  "+power+" %", (rov_canvas.width/4) + 80, 60);
  } else {
    rov_context.fillStyle = "#aaaa55";
    rov_context.fillText( "  "+power+" %", (rov_canvas.width/4) + 80, 60);
  }
  rov_context.fill();

  rov_context.beginPath();
  rov_context.fillStyle = "#aaaa55";
  rov_context.fillText( "Heading", (rov_canvas.width/2), 20);
  rov_context.fillText( "Roll", (rov_canvas.width/2), 40);
  rov_context.fillText( "Pitch", (rov_canvas.width/2), 60);

  if (calibrated) {
    rov_context.fillText( ": "+heading, (rov_canvas.width/2)+80, 20);
    rov_context.fillText( ": "+roll, (rov_canvas.width/2)+80, 40);
    rov_context.fillText( ": "+pitch, (rov_canvas.width/2)+80, 60);
    rov_context.fill();
  } else {
    rov_context.fillStyle = "#aa0000";
    rov_context.fillText( ": IMU SENSOR", (rov_canvas.width/2)+80, 20);
    rov_context.fillText( ": CALIBRATION", (rov_canvas.width/2)+80, 40);
    rov_context.fillText( ": NEEDED", (rov_canvas.width/2)+80, 60);
    rov_context.fill();
  }

  rov_context.beginPath();
  rov_context.fillStyle = "#aaaa55";
  rov_context.fillText( "Mbar", (rov_canvas.width/4)*3, 20);
  rov_context.fillText( "Depth", (rov_canvas.width/4)*3, 40);
  rov_context.fillText( "Temp", (rov_canvas.width/4)*3, 60);

  if (mbar > 0) {
    rov_context.fillText( ": "+Math.floor(mbar), (rov_canvas.width/4)*3+80, 20);
    rov_context.fillText( ": "+depth+" cm", (rov_canvas.width/4)*3+80, 40);
    rov_context.fillText( ": "+temp_out+" / "+temp_in+" °C", (rov_canvas.width/4)*3+80, 60);
  } else {
    rov_context.fillStyle = "#aa0000";
    rov_context.fillText( ": NO", (rov_canvas.width/4)*3+80, 20);
    rov_context.fillText( ": DEPTH", (rov_canvas.width/4)*3+80, 40);
    rov_context.fillText( ": SENSOR", (rov_canvas.width/4)*3+80, 60);
  }

// Visual Gamepad Axis
  if (!gamepad_detected) {
    rov_context.beginPath();
    rov_context.fillStyle = "#aa0000";
    rov_context.fillText("NO CONTROLLER", (rov_canvas.width/2-80), rov_canvas.height/4*3);
    rov_context.fill();
  } else {
  rov_context.beginPath();
  rov_context.strokeStyle = "#aaaa55";
  rov_context.arc((rov_canvas.width/2)-60, (rov_canvas.height/2)+200, 30, 0, 2*Math.PI);
  rov_context.stroke();
  rov_context.beginPath();
  rov_context.arc((rov_canvas.width/2)+60, (rov_canvas.height/2)+200, 30, 0, 2*Math.PI);
  rov_context.stroke();

// Green cross gamepad
    rov_context.strokeStyle = "#00aa00";
    rov_context.beginPath();
    rov_context.moveTo((rov_canvas.width/2)-60-15,rov_canvas.height/2+200);
    rov_context.lineTo((rov_canvas.width/2)-60+15,rov_canvas.height/2+200);
    rov_context.moveTo((rov_canvas.width/2)+60-15,rov_canvas.height/2+200);
    rov_context.lineTo((rov_canvas.width/2)+60+15,rov_canvas.height/2+200);
    rov_context.moveTo((rov_canvas.width/2)-60,rov_canvas.height/2+200-15);
    rov_context.lineTo((rov_canvas.width/2)-60,rov_canvas.height/2+200+15);
    rov_context.moveTo((rov_canvas.width/2)+60,rov_canvas.height/2+200-15);
    rov_context.lineTo((rov_canvas.width/2)+60,rov_canvas.height/2+200+15);
    rov_context.stroke();

// Red dot Gamepad
    rov_context.beginPath();
    rov_context.fillStyle = "#aa0000";
    rov_context.arc((rov_canvas.width/2)-60+Math.floor(axis_value[0]*20), (rov_canvas.height/2)+200+Math.floor(axis_value[1]*20), 5, 0, 2*Math.PI);
    rov_context.fill();
    rov_context.beginPath();
    rov_context.fillStyle = "#aa0000";
    rov_context.arc((rov_canvas.width/2)+60+Math.floor(axis_value[2]*20), (rov_canvas.height/2)+200+Math.floor(axis_value[3]*20), 5, 0, 2*Math.PI);
    rov_context.fill();
  }


// HUD
  rov_context.beginPath();
  rov_context.fillStyle = "#aa0000";
  if (pitch > 0) {
     rov_context.arc((rov_canvas.width/2), (rov_canvas.height/2)-pitch, 50, (roll/180)*Math.PI, Math.PI+((roll/180)*Math.PI), false);
  } else {
     rov_context.arc((rov_canvas.width/2), (rov_canvas.height/2)-pitch, 50, (roll/180)*Math.PI, Math.PI+((roll/180)*Math.PI), false);
  }
  rov_context.lineWidth = 3;
  rov_context.strokeStyle = '#aa0000';
  rov_context.stroke();
// Cross
  rov_context.fillStyle = "#00aa00";
  rov_context.strokeStyle = "#00aa00";
  rov_context.beginPath();
  rov_context.moveTo((rov_canvas.width/2) - 100, rov_canvas.height/2);
  rov_context.lineTo((rov_canvas.width/2) + 100, rov_canvas.height/2);
  rov_context.stroke();
  rov_context.beginPath();
  rov_context.moveTo((rov_canvas.width/2) , (rov_canvas.height/2) -100);
  rov_context.lineTo((rov_canvas.width/2) , (rov_canvas.height/2) +100);
  rov_context.stroke();
// Camera Dot
  rov_context.beginPath();
  rov_context.fillStyle = "#aa0000";
  rov_context.arc((rov_canvas.width/2), (rov_canvas.height/2)-Math.floor(camx/10*2), 5, 0, 2*Math.PI);
  rov_context.fill();

// Depth
  if (mbar > 0) {
  rov_context.beginPath();
  rov_context.fillStyle = "#000000";
  rov_context.rect(10,rov_canvas.height/2-220,60,440);
  rov_context.fill();

  rov_context.fillStyle = "#00aa00";
  rov_context.strokeStyle = "#00aa00";
  rov_context.lineWidth = 1;
  rov_context.beginPath();
  for (i = -8; i <= 8; i++) {
    if (Math.floor(depth)-i >= 0) {
      if ( (i-Math.floor(depth)) % 5) {
          rov_context.moveTo(10, rov_canvas.height/2-(i*25));
          rov_context.lineTo(20, rov_canvas.height/2-(i*25));
      } else {
          rov_context.fillText( Math.floor(depth)-i, 32, rov_canvas.height/2+5-(i*25));
          rov_context.moveTo(10, rov_canvas.height/2-(i*25));
          rov_context.lineTo(30, rov_canvas.height/2-(i*25));
      }
      rov_context.stroke();
    }
  }
  rov_context.fillStyle = "#aa0000";
  rov_context.strokeStyle = "#aa0000";
  rov_context.lineWidth = 3;
  rov_context.beginPath();
  rov_context.moveTo(10, rov_canvas.height/2);
  rov_context.lineTo(50, rov_canvas.height/2);
  rov_context.stroke();
  // rov_context.fillText( depth, 90, rov_canvas.height/2 + 5);
  }

// Heading
  rov_context.fillStyle = "#00aa00";
  rov_context.strokeStyle = "#00aa00";
  rov_context.lineWidth = 1;
  rov_context.beginPath();
  for (i = -10; i <= 10; i++) {
      if ( Math.floor(heading+i) % 5) {
          rov_context.moveTo((rov_canvas.width/2)+(i*35),65);
          rov_context.lineTo((rov_canvas.width/2)+(i*35),75);
      } else {
//          var heading_tmp = (heading+i).toString();
//          var heading_length = heading_tmp.length;
          if (heading+i < 0) {
          //  rov_context.fillText(Math.floor(heading+i+360), (rov_canvas.width/2)+(i*35)-18, 100);
          } else if (heading+i >= 360) {
            rov_context.fillText(Math.floor(heading+i-360), (rov_canvas.width/2)+(i*35)-18, 100);
          } 

          if ((heading+i >= 100) && (heading+i < 360)) {
              rov_context.fillText(Math.floor(heading+i), (rov_canvas.width/2)+(i*35)-18, 100);
            } else if ((heading+i >= 10) && (heading+i < 360)) {
              rov_context.fillText(zeroPad(Math.floor(heading+i),3), (rov_canvas.width/2)+(i*35)-18, 100);
            } else if (heading+i < 10) {
              rov_context.fillText(zeroPad(Math.floor(heading+i),3), (rov_canvas.width/2)+(i*35)-18, 100);
          }
          rov_context.moveTo((rov_canvas.width/2)+(i*35), 65);
          rov_context.lineTo((rov_canvas.width/2)+(i*35), 85);
      }
      rov_context.stroke();
  }
  rov_context.fillStyle = "#aa0000";
  rov_context.strokeStyle = "#aa0000";
  rov_context.lineWidth = 3;
  rov_context.beginPath();
  rov_context.moveTo(rov_canvas.width/2, 65);
  rov_context.lineTo(rov_canvas.width/2, 110);
  rov_context.stroke();
  
// Motor
  rov_context.fillStyle = "#00aa00";
  rov_context.strokeStyle = "#00aa00";
  rov_context.lineWidth = 1;
  rov_context.font = '14pt Verdana';
  rov_context.fillText("Motor", (rov_canvas.width/4*3), rov_canvas.height/2+10);
  rov_context.beginPath();
  rov_context.font = '10pt Verdana';
  rov_context.rect((rov_canvas.width/4*3)+20, rov_canvas.height/2+30,100,20);
  rov_context.rect((rov_canvas.width/4*3)+20, rov_canvas.height/2+60,100,20);
  rov_context.rect((rov_canvas.width/4*3)+20, rov_canvas.height/2+90,100,20);
  rov_context.rect((rov_canvas.width/4*3)+20, rov_canvas.height/2+120,100,20);
  rov_context.rect((rov_canvas.width/4*3)+20, rov_canvas.height/2+150,100,20);
  rov_context.rect((rov_canvas.width/4*3)+20, rov_canvas.height/2+180,100,20);
  rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+30,100,20);
  rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+60,100,20);
  rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+90,100,20);
  rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+120,100,20);
  rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+150,100,20);
  rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+180,100,20);
  rov_context.stroke();
  rov_context.beginPath();
  rov_context.fillText("1", (rov_canvas.width/4*3), rov_canvas.height/2+45);
  rov_context.fillText("2", (rov_canvas.width/4*3), rov_canvas.height/2+75);
  rov_context.fillText("3", (rov_canvas.width/4*3), rov_canvas.height/2+105);
  rov_context.fillText("4", (rov_canvas.width/4*3), rov_canvas.height/2+135);
  rov_context.fillText("5", (rov_canvas.width/4*3), rov_canvas.height/2+165);
  rov_context.fillText("6", (rov_canvas.width/4*3), rov_canvas.height/2+195);
  rov_context.fill();
  rov_context.beginPath();
  rov_context.fillStyle = "#aa0000"; 
  if (motor_1 != 0) {
    rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+35,motor_1,10);
  }
  if (motor_2 != 0) {
    rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+65,motor_2,10);
  }
  if (motor_3 != 0) {
    rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+95,motor_3,10);
  }
  if (motor_4 != 0) {
    rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+125,motor_4,10);
  }
  if (motor_5 != 0) {
    rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+155,motor_5,10);
  }
  if (motor_6 != 0) {
    rov_context.rect((rov_canvas.width/4*3)+120, rov_canvas.height/2+185,motor_6,10);
  }
  rov_context.fill();


// IMU Status Text
  rov_context.beginPath();
  rov_context.font = '14pt Verdana';
  rov_context.fillStyle = "#aaaa00";
  rov_context.fillText("ACCL X:", 150, 150);
  rov_context.fillText("ACCL Y:", 150, 200);
  rov_context.fillText("ACCL Z:", 150, 250);
  rov_context.fillText("IMU SYS:", 150, 300);
  rov_context.fillText("IMU GYRO:", 150, 350);
  rov_context.fillText("IMU ACCEL:", 150, 400);
  rov_context.fillText("IMU MAG:", 150, 450);
  rov_context.fillStyle = "#aa0000";
  rov_context.fillText( accl_x+"  ", 240, 150);
  rov_context.fillText( accl_y+"  ", 240 ,200);
  rov_context.fillText( accl_z+"  ", 240, 250);
  rov_context.fillStyle = "#aa0000";
  if (imusys == 3) {
    rov_context.fillStyle = "#00aa00";
  }
  rov_context.fillText( imusys+"  ", 300, 300);
  rov_context.fillStyle = "#aa0000";
  if (imugyro == 3) {
    rov_context.fillStyle = "#00aa00";
  }
  rov_context.fillText( imugyro+"  ", 300, 350);
  rov_context.fillStyle = "#aa0000";
  if (imuaccel == 3) {
    rov_context.fillStyle = "#00aa00";
  }
  rov_context.fillText( imuaccel+"  ", 300, 400);
  rov_context.fillStyle = "#aa0000";
  if (imumag == 3) {
    rov_context.fillStyle = "#00aa00";
  }
  rov_context.fillText( imumag+"  ", 300, 450);
  rov_context.fill();


// HUD Status Text
  rov_context.beginPath();
  rov_context.font = '14pt Verdana';
  rov_context.fillStyle = "#aaaa00";
  rov_context.fillText("MOTOR:", (rov_canvas.width/4)*3, 150);
  if (motor) {
      rov_context.fillStyle = "#00aa00";
      rov_context.fillText( "ARMED", (rov_canvas.width/4)*3+80, 150);
  } else {
      rov_context.fillStyle = "#aa0000";
      rov_context.fillText( "DISARM", (rov_canvas.width/4)*3+80, 150);
  }
  rov_context.fill();
  rov_context.fillStyle = "#aaaa00";
  rov_context.fillText("LIGHTS:", (rov_canvas.width/4)*3, 200);
  if (lights) {
      rov_context.fillStyle = "#00aa00";
      rov_context.fillText( "ON", (rov_canvas.width/4)*3+80, 200);
  } else {
      rov_context.fillStyle = "#aa0000";
      rov_context.fillText( "OFF", (rov_canvas.width/4)*3+80, 200);
  }
  rov_context.fill();
  rov_context.fillStyle = "#aaaa00";
  rov_context.fillText("HOVER:", (rov_canvas.width/4)*3, 250);
  if (hover) {
      rov_context.fillStyle = "#00aa00";
      rov_context.fillText( "ON", (rov_canvas.width/4)*3+80, 250);
      rov_context.fillStyle = "#aa0000";
      rov_context.fillText( " ("+hoverset+")  ", (rov_canvas.width/4)*3+110, 250);
  } else {
      rov_context.fillStyle = "#aa0000";
      rov_context.fillText( "OFF", (rov_canvas.width/4)*3+80, 250);
  }
  rov_context.fill();
  rov_context.fillStyle = "#aaaa00";
  rov_context.fillText("PILOT:", (rov_canvas.width/4)*3, 300);
  if (pilot) {
      rov_context.fillStyle = "#00aa00";
      rov_context.fillText( "AUTO", (rov_canvas.width/4)*3+80, 300);
      rov_context.fillText( ": "+pilotset+"  ", (rov_canvas.width/4)*3+140, 300);
  } else {
      rov_context.fillStyle = "#aa0000";
      rov_context.fillText( "STANDBY   ", (rov_canvas.width/4)*3+80, 300);
  }
  rov_context.fill();

// Show version on display
   if (version) {
      rov_context.beginPath();
      rov_context.fillStyle = "#00aa00";
      rov_context.font = '10pt Verdana';
      rov_context.fillText("Version: "+version,rov_canvas.width/2-70,rov_canvas.height-20);
      rov_context.fill();
  }

// Show gamepad support browser
   if (!gamepadSupportAvailable) {
      rov_context.beginPath();
      rov_context.fillStyle = "#aa0000";
      rov_context.font = '10pt Verdana';
      rov_context.fillText("Gamepad NOT supported",rov_canvas.width-200,rov_canvas.height-20);
      rov_context.fill();
    } else {
      rov_context.beginPath();
      rov_context.fillStyle = "#00aa00";
      rov_context.font = '10pt Verdana';
      rov_context.fillText("Gamepad enabled",rov_canvas.width-200,rov_canvas.height-20);
      rov_context.fill();
    }
}

function mainloop() {
  display(rovdata);
  readgamepad();
}

function init() {
  setInterval(mainloop, 20);
}

socket.on("connect", function () {
  constatus = 'Connected';
  power = 0;
  motor_1 = 0;
  motor_2 = 0;
  motor_3 = 0;
  motor_4 = 0;
  motor_5 = 0;
  motor_6 = 0;
});

socket.on("disconnect", function () {
  constatus = 'Disonnected';
});

socket.on("rovdata", function(rovdata) {
  update(rovdata); 
})

socket.on("command", function(cmd) {
  command = cmd;; 
});

init();

