var five = require("johnny-five");
var board = new five.Board({ repl: "false" });

var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://10.10.10.23');


client.on('connect', function() {
    client.subscribe('hello');

    board.on("ready", function() {
        var led = new five.Led(6);

        client.on('message', function(topic, message) {
            // message is Buffer 
            console.log(message.toString());
            if(message.toString() == "ledon"){
            	led.on();
            }else if(message.toString() == "ledoff"){
            	led.off();
            }else if(message.toString() == "ledfadein"){
            	led.fadeIn(500);
            }else if(message.toString() == "ledfadeout"){
            	led.fadeOut(500);
            }


        });

    });

    // client.publish('presence', 'Hello mqtt');
});
