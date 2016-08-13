var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://localhost');
var app = require('express')();

var server = app.listen(3000);
var io = require('socket.io')(server);

app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});

client.on('connect', function() {
    client.subscribe('hello');
    io.on('connection', function(socket) {
        socket.on('message', function(msg) {
        	console.log(msg);
        	client.publish('hello', msg);
        });
    });
});

client.on('message', function(topic, message) {
    // message is Buffer 
    incoming = message.toString()
    console.log(incoming);
    // io.sockets.emit('data',
    //     incoming
    // );
});
