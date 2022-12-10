import {
    API,
    DynamicPlatformPlugin,
    Logger,
    PlatformAccessory,
    PlatformConfig,
    Service,
    Characteristic
} from 'homebridge';

import {PLATFORM_NAME, PLUGIN_NAME} from './settings';
import {ArduinoSwitchAccessory} from './arduinoSwitchAccessory';
import {ArduinoRGBLightAccessory} from './arduinoRGBLightAccessory';
import {ArduinoRGBLightAccessoryV2} from './arduinoRGBLightAccessoryV2';
import {StorageWrapper} from "./storageWrapper";
import {Device} from "./device";

export class UniversalIOTPlatform implements DynamicPlatformPlugin {
    public readonly Service: typeof Service = this.api.hap.Service;
    public readonly Characteristic: typeof Characteristic = this.api.hap.Characteristic;

    public readonly accessories: PlatformAccessory[] = [];

    constructor(
        public readonly log: Logger,
        public readonly config: PlatformConfig,
        public readonly api: API,
    ) {
        this.log.debug('Finished initializing platform:', this.config.name);

        this.api.on('didFinishLaunching', () => {
            log.debug('Executed didFinishLaunching callback');
            this.discoverDevices().then(r => {
                log.info("Discovery over")
            });
        });
    }

    /**
     * This function is invoked when homebridge restores cached accessories from disk at startup.
     * It should be used to setup event handlers for characteristics and update respective values.
     */
    configureAccessory(accessory: PlatformAccessory) {
        this.log.info('Loading accessory from cache:', accessory.displayName);
        // add the restored accessory to the accessories cache so we can track if it has already been registered
        this.accessories.push(accessory);
    }

    clearDevices() {
        this.api.unregisterPlatformAccessories(PLUGIN_NAME, PLATFORM_NAME, this.accessories);
    }

    /**
     * This is an example method showing how to register discovered accessories.
     * Accessories must only be registered once, previously created accessories
     * must not be registered again to prevent "duplicate UUID" errors.
     */

    async discoverDevices() {
        let devicesInfo = this.config["devices_info"];
        for (const deviceData of devicesInfo) {
            let device = new Device(deviceData["name"], deviceData["id"], deviceData["type"], deviceData["port"]);
            const uuid = this.api.hap.uuid.generate(device.id);
            this.log.info("Device, Device UUID: ", device, uuid)
            let storage = await StorageWrapper.createAsync(this.api.user.persistPath(), this.log, device.type, device.name, device.id);
            const existingAccessory = this.accessories.find(accessory => accessory.UUID === uuid);

            if (existingAccessory) {
                this.log.info('Restoring existing accessory from cache:', existingAccessory.displayName);
                if (device.type === 'lightBulb') {
                    new ArduinoRGBLightAccessory(this, existingAccessory, storage, device);
                }
                else if (device.type === 'rgbBulb') {
                    new ArduinoRGBLightAccessoryV2(this, existingAccessory, storage, device);
                }
                else {
                    new ArduinoSwitchAccessory(this, existingAccessory, storage, device);
                }

            } else {
                this.log.info('Adding new accessory:', device.name);
                const accessory = new this.api.platformAccessory(device.name, uuid);
                accessory.context.device = device;
                if (device.type === 'lightBulb') {
                    new ArduinoRGBLightAccessory(this, accessory, storage, device);
                }
                else if (device.type === 'rgbBulb') {
                    new ArduinoRGBLightAccessoryV2(this, accessory, storage, device);
                }
                else {
                    new ArduinoSwitchAccessory(this, accessory, storage, device);
                }
                this.api.registerPlatformAccessories(PLUGIN_NAME, PLATFORM_NAME, [accessory]);
            }
        }
    }
}
