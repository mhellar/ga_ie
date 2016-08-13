var five = require("johnny-five");
var board = new five.Board();

board.on("ready", function() {
  var led = new five.Led(6);
led.pulse(500);
});