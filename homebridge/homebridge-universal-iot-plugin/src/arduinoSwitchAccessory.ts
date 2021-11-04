import {Service, PlatformAccessory, CharacteristicValue} from 'homebridge';

import {UniversalIOTPlatform} from './platform';
import {StorageWrapper} from "./storageWrapper";

let defaultState = {on: false};

export class ArduinoSwitchAccessory {
    private service: Service;
    private state = defaultState;

    constructor(
        private readonly platform: UniversalIOTPlatform,
        private readonly accessory: PlatformAccessory,
        private readonly storage: StorageWrapper
    ) {

        this.setDeviceProps();
        this.service = this.accessory.getService(this.platform.Service.Switch) || this.accessory.addService(this.platform.Service.Switch);

        this.service.getCharacteristic(this.platform.Characteristic.On)
            .onGet(this.handleOnGet.bind(this))
            .onSet(this.handleOnSet.bind(this));

    }

    private setDeviceProps() {
        this.accessory.getService(this.platform.Service.AccessoryInformation)!
            .setCharacteristic(this.platform.Characteristic.Manufacturer, 'made-by-neel')
            .setCharacteristic(this.platform.Characteristic.Model, 'ArdSwitch')
            .setCharacteristic(this.platform.Characteristic.SerialNumber, 'ArdSwitch-01')
            .setCharacteristic(this.platform.Characteristic.Name, "Arduino Driven Switch")
    }

    async handleOnGet() {
        this.platform.log.info('Getting value of ', this.accessory.displayName);
        let state = await this.storage.retrieve(defaultState);
        this.platform.log.info('Value:', state);
        return state.on
    }

    handleOnSet(value) {
        let newState = {on: value};
        this.platform.log.info('Setting value of switch to', value);
        this.storage.store(newState);
    }
}