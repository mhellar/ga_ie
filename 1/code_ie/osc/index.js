var osc = require('node-osc');

var oscServer = new osc.Server(8337, '10.2.0.147');
oscServer.on("message", function(msg, rinfo) {
    console.log("TUIO message:");
    console.log(msg);
});
