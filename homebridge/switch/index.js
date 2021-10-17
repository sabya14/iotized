let Service, Characteristic;
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

let blueSwitchStatus = false;
module.exports = function (homebridge) {
    Service = homebridge.hap.Service;
    Characteristic = homebridge.hap.Characteristic;
    homebridge.registerAccessory('homebridge-bluetoothportswitch', 'bluetoothportswitch', blueSwitch);
}

function blueSwitch(log, config) {
    this.log = log;
    this.name = config['name'];
    this.port = config["port"]
    this.devPort = new SerialPort(this.port, {baudRate: 9600}).setEncoding('utf8');
    const parser = this.devPort.pipe(new Readline({delimiter: '\n'}));
    parser.on('data', data => {
        console.log(`Health of ${this.name} - ${data}`);
    });

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
    let value = '0';
    if (on === true) value = '1';
    this.devPort.write(value, function (err) {
        if (err) {
            return console.log("Error on write: ", err.message);
        }
        blueSwitchStatus = value === '1';
        console.log(`Data written: ${value} to device ${this.name}`);
    });
    next(null);
}