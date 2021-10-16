var Service, Characteristic;
var SerialPort = require('serialport');
var blueSwitchStatus = false;
var portAC = new SerialPort('/dev/rfcomm0', {baudRate: 9600});
var portFAN = new SerialPort('/dev/rfcomm1', {baudRate: 9600});

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