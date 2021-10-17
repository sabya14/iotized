var SerialPort = require('serialport');

var portAC = new SerialPort('/dev/rfcomm0', {baudRate: 9600});
var portFAN = new SerialPort('/dev/rfcomm1', {baudRate: 9600});

function blueSwitch() {
    setInterval(() => {
        // Try to get health of ports, if port is dead, try to reconnect
        try {
            let acHealth = portAC.read();
            let fanHealth = portFAN.read();
            console.log("Fan health", fanHealth)
            console.log("AC health", acHealth)
        } catch (err) {
            console.log("Err " + err.message)
        }
    }, 100);
}
