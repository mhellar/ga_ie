var ws = require("nodejs-websocket");
var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://ec2-35-161-110-220.us-west-2.compute.amazonaws.com');

// Scream server example: "hi" -> "HI!!!" 
var server = ws.createServer(function(conn) {
    console.log("New connection")

    client.on('connect', function() {
    client.subscribe('hello');
    client.on('message', function(topic, message) {
        conn.sendText(message);
    });
    });

    conn.on("text", function(str) {
        console.log("Received " + str)
        conn.sendText(str.toUpperCase() + "!!!")
    })
    conn.on("close", function(code, reason) {
        console.log("Connection closed")
    })
}).listen(8001)


