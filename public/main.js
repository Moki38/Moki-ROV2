
var rov_canvas = document.getElementById('rovCanvas');
var rov_context = rov_canvas.getContext('2d');

var constatus = "Not connected";
var connected = false;
//var socket = io.connect();

var gamepad_detected = false;
var gamepadSupportAvailable = navigator.getGamepads || !!navigator.webkitGetGamepads || !!navigator.webkitGamepads;
var button_pressed = new Array(16);
var button_value = new Array(16);
var axis_value = new Array(16);

function display() {
  var today=new Date().toISOString().replace(/T/, ' ').replace(/\..+/, '')
  rov_context.clearRect(0, 0, rov_canvas.width, rov_canvas.height);
  rov_context.font = '14pt Verdana';
  rov_context.lineWidth = 1;
  rov_context.fillStyle = "#aaaa55";
  rov_context.fillText( today, 10, 20);
  rov_context.fillText( "Moki ROV (Raspberry PI)", 10, 60);
  rov_context.fillText(constatus, 10, rov_canvas.height-20);

// Show gamepad support browser
   if (!gamepadSupportAvailable) {
      rov_context.beginPath();
      rov_context.fillStyle = "#aa0000";
      rov_context.font = '10pt Verdana';
      rov_context.fillText("Gamepad NOT supported by browser!",600,rov_canvas.height-5);
      rov_context.fill();
    } else {
      rov_context.beginPath();
      rov_context.fillStyle = "#00aa00";
      rov_context.font = '10pt Verdana';
      rov_context.fillText("Gamepad supported by browser!",620,rov_canvas.height-5);
      rov_context.fill();
    }
}

function mainloop() {
  display();
}

function init() {
  setInterval(mainloop, 20);
}

init();

