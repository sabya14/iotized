let Service, Characteristic;
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

let blueSwitchStatus = false;
const portAC = new SerialPort('/dev/rfcomm0', {baudRate: 9600}).setEncoding('utf8');
const portFAN = new SerialPort('/dev/rfcomm1', {baudRate: 9600}).setEncoding('utf8');

const parserAC = portAC.pipe(new Readline({ delimiter: '\n' }));
const parserFan = portFAN.pipe(new Readline({ delimiter: '\n' }));

parserAC.on('data', data =>{
    console.log('got word from arduino ac:', data);
});
parserFan.on('data', data =>{
    console.log('got word from arduino fan:', data);
});

module.exports = function (homebridge) {
    Service = homebridge.hap.Service;
    Characteristic = homebridge.hap.Characteristic;
    homebridge.registerAccessory('homebridge-bluetoothportswitch', 'bluetoothportswitch', blueSwitch);
}

function blueSwitch(log, config) {
    this.log = log;
    this.name = config['name'];
    this.service = new Service.Switch(this.name);
    this.informationService = new Service.AccessoryInformation();

    this.service
        .getCharacteristic(Characteristic.On)
        .on('get', this.getOn.bind(this))
        .on('set', this.setOn.bind(this));

    setInterval(() => {
        // Try to get health of ports, if port is dead, try to reconnect
        try {


        } catch (err) {
            console.log("Err " + err.message)
        }
    }, 500);
}

blueSwitch.prototype.getServices = function () {
    return [this.service];
}

blueSwitch.prototype.getOn = function (next) {
    next(null, blueSwitchStatus);
}

blueSwitch.prototype.setOn = function (on, next) {
    function extracted(selectedPort, value, deviceName) {
        selectedPort.write(value, function (err) {
            if (err) {
                return console.log("Error on write: ", err.message);
            }
            blueSwitchStatus = value === '1';
            console.log("[+] Message written: " + value + " on port " + deviceName);
        });
    }

    let selectedPort = portAC;
    if (this.name === 'Fan')
        selectedPort = portFAN
    if (on === true)
        extracted(selectedPort, "1", this.name);
    else if (on === false)
        extracted(selectedPort, "0", this.name);
    next(null);
}