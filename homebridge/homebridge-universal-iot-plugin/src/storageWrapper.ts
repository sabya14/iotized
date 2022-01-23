import {Logger} from "homebridge";
import {JsonDB} from 'node-json-db';
import {Config} from 'node-json-db/dist/lib/JsonDBConfig'

export class StorageWrapper {

    constructor(
        public readonly dir: string,
        private readonly log: Logger,
        public readonly type: string,
        public readonly name: string,
        public readonly id: string,
        public db: JsonDB
    ) {
        this.log.info(`Switch ${name} is stored in file ${this.dir}`);
    }

    public static createAsync = async (dir, log, type, name, id) => {
        let db = new JsonDB(new Config("db.json", true, false, '/'));
        db.reload();
        return new StorageWrapper(dir, log, type, name, id, db);
    };

    public clear() {
        this.log.info("Clearing all storage")
        this.db.push("/", {})
    }

    async store(value) {
        this.log.info("Setting value for:", this.name, value)
        this.db.push("/" + this.id, value)
    }

    async retrieve(defaultValue) {
        try {
            return this.db.getData("/" + this.id);
        } catch (e) {
            this.log.error(e)
            this.log.warn("Got error while fetching data, returning default value")
            return defaultValue;

        }
    }
}
