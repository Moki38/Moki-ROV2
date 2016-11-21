var express = require('express');
var app = express();
var server = require("http").Server(app);
var io = require("socket.io")(server);
var fs = require("fs")
var shell = require("shelljs");
var jsonfile = require('jsonfile')
jsonfile.spaces = 4

var config_file = 'config.js'
var config = {};

var app = express();

app.use(express.static('public'));

app.get('/', function(req, res) {
  res.sendfile('index.html')
})

app.get('/config', function(req, res) {
  res.end(req.cookies);

  config.i2c = {device: '/dev/i2c-1'}
  ipaddr = shell.exec('hostname -i', {silent:true}).stdout
  ipaddr = ipaddr.replace(/[\n$]/g, '');

  config.network = {ipaddr : ipaddr}
  jsonfile.writeFileSync( __dirname + '/' + config_file , config)
})

io.on('connection', function (socket) {
  console.log('connectiong');
  socket.emit('connect');
  
// when the user disconnects.. perform this
  socket.on('disconnect', function () {
  });
});

var server = app.listen(3000, function () {

  var host = server.address().address
  var port = server.address().port

  console.log("Moki-ROV2 Started, listening at http://%s:%s", host, port);
})

