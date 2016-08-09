var osc = require('node-osc');

var oscServer = new osc.Server(8001, '172.20.10.3');
oscServer.on("message", function(msg, rinfo) {
    console.log("TUIO message:");
    console.log(msg);
});
