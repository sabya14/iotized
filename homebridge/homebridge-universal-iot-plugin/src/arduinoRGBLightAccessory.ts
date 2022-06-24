import {PlatformAccessory, Service} from 'homebridge';
import SerialPort from 'serialport'
import {UniversalIOTPlatform} from './platform';
import {StorageWrapper} from "./storageWrapper";
import {Device} from "./device";
import {Health, RGBHealth, State} from "./health";
import {CharacteristicValue} from "hap-nodejs/dist/types";
import {ArduinoSwitchAccessory} from "./arduinoSwitchAccessory";

const path = require('path');

const Readline = require('@serialport/parser-readline');
let refreshInterval = 1000;


let defaultRGBData = "100,100,100,50#";

export class ArduinoRGBLightAccessory {
    private service: Service;
    private devPort: SerialPort;
    private devHealth: RGBHealth = new RGBHealth(false, -1, State.Down, -1, false, defaultRGBData, 100, 100, 100, 50);

    constructor(
        private readonly platform: UniversalIOTPlatform,
        private readonly accessory: PlatformAccessory,
        private readonly storage: StorageWrapper,
        private readonly device: Device
    ) {

        this.setDeviceProps();
        this.service = this.accessory.getService(this.platform.Service.Lightbulb) || this.accessory.addService(this.platform.Service.Lightbulb);

        this.service.getCharacteristic(this.platform.Characteristic.On)
            .onGet(this.handleOnGet.bind(this))
            .onSet(this.handleOnSet.bind(this));


        this.service.getCharacteristic(this.platform.Characteristic.Hue)
            .onGet(this.handleHueGet.bind(this))
            .onSet(this.handleHueSet.bind(this))

        this.service.getCharacteristic(this.platform.Characteristic.Brightness)
            .onGet(this.handleBrightnessGet.bind(this))
            .onSet(this.handleBrightnessSet.bind(this))

        this.service.getCharacteristic(this.platform.Characteristic.Saturation)
            .onGet(this.handleSaturationGet.bind(this))
            .onSet(this.handleSaturationSet.bind(this))

        this.service.getCharacteristic(this.platform.Characteristic.ColorTemperature)
            .onGet(this.handleColorTempGet.bind(this))
            .onSet(this.handleColorTempSet.bind(this))

        this.service.getCharacteristic(this.platform.Characteristic.SupportedCharacteristicValueTransitionConfiguration)
            .onGet(this.handleOnGetValueTransition.bind(this))
            .onSet(this.handleOnSetValueTransition.bind(this));


        this.initWithPastState().then(r => {
            this.platform.log.info("Device info", device)
            this.devPort = new SerialPort(this.device.port, {baudRate: 9600}).setEncoding('ascii');
            this.devPort.on('open', () => {
                this.platform.log.info(`After opening port listening to device  ${this.device.name}`);
                if (this.devHealth.state == State.Up) {
                    this.platform.log.info("Device was on, so trying to set last known value")
                    this.handleOnSet(true);
                }
            })

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
            .setCharacteristic(this.platform.Characteristic.Model, 'ArdLight')
            .setCharacteristic(this.platform.Characteristic.SerialNumber, 'ArdLight-01')
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
        this.platform.log.info('Value received for Setting (On/off)', value);
        this.platform.log.info('Value received for Setting (On/off) and currentHealth', this.devHealth);
        let stale = false
        if (!this.devHealth.connected) {
            stale = true
        }
        this.devHealth = new RGBHealth(
            this.devHealth.connected,
            this.devHealth.lastUpTime,
            State.Up,
            Date.now(),
            stale,
            this.devHealth.data,
            this.devHealth.hue,
            this.devHealth.saturation,
            this.devHealth.colorTemp,
            this.devHealth.brightness
        );
        if (!value) {
            this.devHealth.state = State.Down;
            this.handleRgbValueSet(this.devHealth, true);
        } else {
            this.devHealth.state = State.Up;
            let rgbAndBrightness = this.handleRgbValueSet(this.devHealth);
        }

    }


    private handleRgbValueSet(devHealth: RGBHealth, swichtOff: boolean = false) {
        if (swichtOff) {
            this.setRgbValue(
                0, 0, 0, false
            )
                .then(() => {
                    this.platform.log.info('Setting value of rgb to', devHealth.state, devHealth.data);
                }).catch((e) => {
                this.platform.log.error(e);

            });

        } else {
            this.setRgbValue(
                this.devHealth.hue,
                this.devHealth.saturation,
                this.devHealth.brightness
            )
                .then(() => {
                    this.platform.log.info('Setting value of rgb to', devHealth.state, devHealth.data);
                }).catch((e) => {
                this.platform.log.error(e);

            });


        }
    }

    async handleHueGet() {
        this.platform.log.info('Getting value of for ', this.accessory.displayName);
        this.platform.log.info('Getting value of hue ', this.platform.Characteristic.Hue);
        let health: RGBHealth = await this.storage.retrieve(this.devHealth);
        this.platform.log.info('Current Health:', health.state);
        let characteristic: CharacteristicValue = this.devHealth.hue;
        return characteristic;
    }


    async handleHueSet(value) {
        this.setRgbValue(
            value,
            (<number>this.service.getCharacteristic(this.platform.Characteristic.Saturation).value),
            (<number>this.service.getCharacteristic(this.platform.Characteristic.Brightness).value)
        )
            .then(() => {
            }).catch((e) => {
            this.platform.log.error(e);

        });
    }

    async setRgbValue(hue, saturation, brightness, persist: boolean = true) {
        this.platform.log.info('Setting rgb from hsv value ', hue, ",", saturation, ",", brightness);
        let rgbAndBrightness = this.HSVtoRGB(hue / 360, saturation / 100, brightness / 100);
        this.platform.log.info("RGB value", rgbAndBrightness);
        if (persist) {
            this.devHealth.data = rgbAndBrightness
            this.devHealth.hue = hue
            this.devHealth.saturation = saturation
            this.devHealth.brightness = brightness

        }
        return new Promise((resolve, reject) => {
            if (!this.devHealth.connected) return reject(Error('Serial port not open'));
            this.devPort.write(rgbAndBrightness, (error) => {
                if (error) {
                    console.log('Error [writeAndDrain]: ' + error);
                    reject(error);
                } else {
                    this.platform.log.info('Setting value of rgb to', this.devHealth.state, this.devHealth.data);
                    this.storage.store(this.devHealth);
                    resolve(null);
                }
            });
        });
    }

    async handleOnGetValueTransition() {
        this.platform.log.info('Getting value SupportedCharacteristicValueTransitionConfiguration for ', this.accessory.displayName);
        this.platform.log.info('Getting value of SupportedCharacteristicValueTransitionConfiguration ', this.platform.Characteristic.SupportedCharacteristicValueTransitionConfiguration);
        let health: RGBHealth = await this.storage.retrieve(this.devHealth);
        this.platform.log.info('Current Health:', health.state);
        let characteristic: CharacteristicValue = this.devHealth.brightness;
        return this.service.getCharacteristic(this.platform.Characteristic.SupportedCharacteristicValueTransitionConfiguration).value
    }


    async handleOnSetValueTransition(value) {
        this.platform.log.info('Setting SupportedCharacteristicValueTransitionConfiguration to', value);
    }


    async handleSaturationGet() {
        this.platform.log.info('Getting value saturation for ', this.accessory.displayName);
        this.platform.log.info('Getting value of saturation ', this.platform.Characteristic.Saturation);
        let health: RGBHealth = await this.storage.retrieve(this.devHealth);
        this.platform.log.info('Current Health:', health.state);
        let characteristic: CharacteristicValue = this.devHealth.saturation;
        return characteristic;
    }


    async handleBrightnessGet() {
        this.platform.log.info('Getting value brightness for ', this.accessory.displayName);
        this.platform.log.info('Getting value of brightness ', this.platform.Characteristic.Brightness);
        let health: RGBHealth = await this.storage.retrieve(this.devHealth);
        this.platform.log.info('Current Health:', health.state);
        let characteristic: CharacteristicValue = this.devHealth.brightness;
        return characteristic;
    }


    async handleBrightnessSet(value) {
        this.platform.log.info('Setting brightness to', value);
        this.setRgbValue(
            (<number>this.service.getCharacteristic(this.platform.Characteristic.Hue).value),
            (<number>this.service.getCharacteristic(this.platform.Characteristic.Saturation).value),
            value,
        )
            .then(() => {
            }).catch((e) => {
            this.platform.log.error(e);

        });
    }


    async handleSaturationSet(value) {
        this.platform.log.info('Setting saturation to', value);
        this.setRgbValue(
            (<number>this.service.getCharacteristic(this.platform.Characteristic.Hue).value),
            value,
            (<number>this.service.getCharacteristic(this.platform.Characteristic.Brightness).value),
        )
            .then(() => {
            }).catch((e) => {
            this.platform.log.error(e);

        });
    }

    async handleColorTempGet() {
        // TODO later
        return this.service.getCharacteristic(this.platform.Characteristic.ColorTemperature).value;
    }


    async handleColorTempSet(value) {
        // TODO later
        this.platform.log.info('Value received for color temp', value);
    }

    private mix(a, b, v) {
        return (1 - v) * a + v * b;
    }

    private HSVtoRGB(h, s, v) {
        var r, g, b;
        var i = Math.floor(h * 6);
        var f = h * 6 - i;
        var p = v * (1 - s);
        var q = v * (1 - f * s);
        var t = v * (1 - (1 - f) * s);

        switch (i % 6) {
            case 0:
                r = v, g = t, b = p;
                break;
            case 1:
                r = q, g = v, b = p;
                break;
            case 2:
                r = p, g = v, b = t;
                break;
            case 3:
                r = p, g = q, b = v;
                break;
            case 4:
                r = t, g = p, b = v;
                break;
            case 5:
                r = v, g = p, b = q;
                break;
        }
        return `${Math.round(r * 255)},${Math.round(g * 255)},${Math.round(b * 255)}#`
    }

}