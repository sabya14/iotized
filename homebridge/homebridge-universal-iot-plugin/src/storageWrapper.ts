import {Logger} from "homebridge";

const Storage = require('node-persist');

export class StorageWrapper {

    constructor(
        public readonly dir: string,
        private readonly log: Logger,
        public readonly type: string,
        public readonly name: string,
        public readonly id: string,
        public readonly storageHandler: object
    ) {
        this.log.info(`Switch ${name} is stored in file ${this.dir}`);
    }

    public static createAsync = async (dir, log, type, name, id) => {
        let storage = await Storage.init({dir: dir});
        return new StorageWrapper(dir, log, type, name, id, storage);
    };

    public clear() {
        this.log.info("Clearing all storage")
        Storage.clear();
    }

    public store(value) {
        this.log.info("Getting value for:", this.name)
        Storage.setItem(this.id, value);
    }

    public retrieve(defaultValue) {
        return Storage.getItem(this.id, (error, data) => {
            if (error) {
                this.log.warn("Got error while fetching data, returning default value")
                return defaultValue;
            }

            if (data === undefined) {
                this.log.warn("Got undefined while fetching data, returning default value")
                data = defaultValue;
            }

            return data;
        });
    }
}