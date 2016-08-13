var mqtt    = require('mqtt');
var client  = mqtt.connect('mqtt://10.10.10.23');
 
client.on('connect', function () {
  client.subscribe('hello');
  // client.publish('presence', 'Hello mqtt');
});
 
client.on('message', function (topic, message) {
  // message is Buffer 
  console.log(message.toString());
});
