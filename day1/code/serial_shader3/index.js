var com = require("serialport");
var express = require('express');

var app = express();
var server = app.listen(3000);
app.use(express.static('public'));
var io = require('socket.io')(server);

var serialPort = new com.SerialPort("/dev/cu.usbmodem1411", {
    baudrate: 9600,
    parser: com.parsers.readline('\n')
});

//Serve index.html when some make a request of the server
app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});

serialPort.on('open', function() {
    console.log('Port open');
});

serialPort.on('data', function(data) {
    io.sockets.emit('data', data);
    console.log(data);
});


