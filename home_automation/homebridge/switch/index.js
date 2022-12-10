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
    this.lastCheckTime = Date.now()
    this.devPort = new SerialPort(this.port, {baudRate: 9600}).setEncoding('utf8');
    this.devPort.on('open', () => {
        this.connected = true;
    });
    this.devPort.on('close', () => {
        this.connected = false;
        setTimeout(this.reconnect.bind(this), 1000);
    });
    this.devPort.on('error', () => {
        setTimeout(this.reconnect.bind(this), 1000);
    });

    this.reconnect = () => {
        if (!this.connected) {
            this.devPort.open();
        }
    }
    this.parser = this.devPort.pipe(new Readline({delimiter: '\n'}));
    this.parser.on('data', data => {
        console.log(`Health of ${this.name} - ${data}`);
    });


    const parser = this.devPort.pipe(new Readline({delimiter: '\n'}));
    parser.on('data', data => {
        console.log(`Health of ${this.name} - ${data}`);
        this.healthToggle = true;
        this.lastCheckTime = Date.now()
    });
    this.service = new Service.Switch(this.name);
    this.informationService = new Service.AccessoryInformation();
    this.service
        .getCharacteristic(Characteristic.On)
        .on('get', this.getOn.bind(this))
        .on('set', this.setOn.bind(this));


    setInterval(() => {
        // Every .5 sec set health to be false, it will again be toggled when its gets health data.
        let timeElapsed = Date.now() - this.lastCheckTime;
        if (timeElapsed > 1200) {
            console.log(`Device ${this.name} health ${this.healthToggle} as it last connected ${timeElapsed} ms ago`);
            this.devPort.close();
            this.lastCheckTime = Date.now();
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
    let value = '0';
    if (on === true) value = '1';
    let device = this.name;
    this.devPort.write(value, function (err) {
        if (err) {
            return console.log("Error on write: ", err.message);
        }
        blueSwitchStatus = value === '1';
        console.log(`Data written: ${value} to device ${device}`);
    });
    next(null);
}