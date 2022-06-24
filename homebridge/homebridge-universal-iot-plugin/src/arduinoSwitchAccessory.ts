import {PlatformAccessory, Service} from 'homebridge';
import SerialPort from 'serialport'
import {UniversalIOTPlatform} from './platform';
import {StorageWrapper} from "./storageWrapper";
import {Device} from "./device";
import {Health, State} from "./health";

const path = require('path');

const Readline = require('@serialport/parser-readline');
let refreshInterval = 1000;


export class ArduinoSwitchAccessory {
    private service: Service;
    private devPort: SerialPort;
    private devHealth: Health = new Health(false, -1, State.Down, -1, false);

    constructor(
        private readonly platform: UniversalIOTPlatform,
        private readonly accessory: PlatformAccessory,
        private readonly storage: StorageWrapper,
        private readonly device: Device
    ) {
        this.setDeviceProps();
        this.service = this.accessory.getService(this.platform.Service.Switch) || this.accessory.addService(this.platform.Service.Switch);

        this.service.getCharacteristic(this.platform.Characteristic.On)
            .onGet(this.handleOnGet.bind(this))
            .onSet(this.handleOnSet.bind(this));


        this.initWithPastState().then(r => {
            this.platform.log.info("Device info", device)
            this.devPort = new SerialPort(this.device.port, {baudRate: 9600}).setEncoding('utf8');
            this.devPort.on('open', () => {
                this.platform.log.info(`Listening to device ${this.device.name}`);
            });
            this.onCloseOfDevPort();
            this.onErrorOfDevPort();

            const parser = this.devPort.pipe(new Readline({delimiter: '\n'}));
            let lastHealth = this.devHealth
            this.onDataFromDevPort(parser, lastHealth);
        });
    }

    private onDataFromDevPort(parser, lastHealth: Health) {
        if (this.devHealth === undefined) return;
        parser.on('data', data => {
            this.devHealth.connected = true;
            this.devHealth.lastUpTime = Date.now()
            if (lastHealth != this.devHealth) {
                this.storage.store(this.devHealth)
                lastHealth = this.devHealth
            }
            if (this.devHealth.staleState) {
                this.handleOnSet(this.devHealth.state).then(r => {
                    this.platform.log.info("Handled state state")
                })
            }
        });
    }

    private onErrorOfDevPort() {
        this.devPort.on('error', (e) => {
            this.platform.log.info(`Port exception, Trying to re-connect to device ${this.device.name}`);
            this.platform.log.error(e)
            this.devHealth.connected = false;
            this.storage.store(this.devHealth)
            setTimeout(this.reconnect.bind(this), refreshInterval);
        });
    }

    private onCloseOfDevPort() {
        this.devPort.on('close', () => {
            this.platform.log.info(`Port closed, Trying to re-connect to device ${this.device.name}`);
            this.devHealth.connected = false;
            this.storage.store(this.devHealth)
            setTimeout(this.reconnect.bind(this), refreshInterval);
        });
    }

    private reconnect = () => {
        if (!this.devHealth.connected) {
            this.devPort.open();
        }
    }

    private setDeviceProps() {
        this.accessory.getService(this.platform.Service.AccessoryInformation)!
            .setCharacteristic(this.platform.Characteristic.Manufacturer, 'made-by-neel')
            .setCharacteristic(this.platform.Characteristic.Model, 'ArdSwitch')
            .setCharacteristic(this.platform.Characteristic.SerialNumber, 'ArdSwitch-01')
            .setCharacteristic(this.platform.Characteristic.Name, this.device.name)
    }

    async initWithPastState() {
        let devHealth = await this.storage.retrieve(this.devHealth);
        if (devHealth !== undefined)
            this.devHealth = devHealth;
    }

    async handleOnGet() {
        this.platform.log.info('Getting value of ', this.accessory.displayName);
        let health = await this.storage.retrieve(this.devHealth);
        this.platform.log.info('Current Health:', health.state);
        return health.state.valueOf();
    }


    async handleOnSet(value) {
        this.platform.log.info('Value received', value);
        let stale = false
        if (!this.devHealth.connected) {
            stale = true
        }
        this.devHealth = new Health(this.devHealth.connected, this.devHealth.lastUpTime, State.Up, Date.now(), stale);
        if (!value) {
            this.devHealth.state = State.Down;
        }

        this.handleWrite(value).then(() => {
            this.platform.log.info('Setting value of switch to', this.devHealth.state);
            this.storage.store(this.devHealth);
        }).catch((e) => {
            this.platform.log.error(e);
        });


    }

    private handleWrite(value) {
        value = value == true ? '1' : '0';
        return new Promise((resolve, reject) => {
            if (!this.devHealth.connected) return reject(Error('Serial port not open'));
            this.devPort.write(value, (error) => {
                if (error) {
                    console.log('Error [writeAndDrain]: ' + error);
                    reject(error);
                } else {
                    resolve(null);
                }
            });
        });
    }
}