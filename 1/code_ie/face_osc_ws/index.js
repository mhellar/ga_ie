var osc = require('node-osc');
var app = require('express')();

var server = app.listen(3000);
var io = require('socket.io')(server);

app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});


var oscServer = new osc.Server(8338, 'localhost');
oscServer.on("message", function(msg, rinfo) {
    console.log("TUIO message:");
    console.log(msg);
    io.sockets.emit('data', {
        val: msg
    });
});
