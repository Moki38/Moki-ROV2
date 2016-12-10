var socket = io.connect();

$(window).resize(function(){location.reload();});

var rov_canvas = document.getElementById('rovCanvas');
var rov_context = rov_canvas.getContext('2d');

rov_canvas.width = window.innerWidth;
rov_canvas.height = window.innerHeight;

//function zero_depth_window() {
//  socket.emit("button","zero_depth");
//}

function zeroPad(num, places) {
  var zero = places - num.toString().length + 1;
  return Array(+(zero > 0 && zero)).join("0") + num;
}

function update(rovdata) {
  var t;
  mbar = rovdata.Pressure;
}

function display() {
  var today=new Date().toISOString().replace(/T/, ' ').replace(/\..+/, '')
  rov_context.clearRect(0, 0, rov_canvas.width, rov_canvas.height);
  rov_context.font = '14pt Verdana';
  rov_context.lineWidth = 1;
  rov_context.fillStyle = "#aaaa55";
  rov_context.fillText( today, 10, 20);
  rov_context.fillText( "Moki ROV (Raspberry PI)", 10, 60);
  rov_context.fill();
}

function mainloop() {
  display();
}

function init() {
  setInterval(mainloop, 20);
}

init();

