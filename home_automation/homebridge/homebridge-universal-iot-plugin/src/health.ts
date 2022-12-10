export enum State {
    Up = 1,
    Down = 0
}

export class Health {

    connected: boolean;
    lastUpTime: number;
    state: State;
    lastStateChange: number;
    staleState: boolean
    data: string

    constructor(connected: boolean,
                lastUpTime: number,
                state: State,
                lastStateChange: number,
                stateState: boolean,
                data: string = ""
    ) {
        this.connected = connected;
        this.lastUpTime = lastUpTime;
        this.state = state;
        this.lastStateChange = lastStateChange
        this.staleState = stateState
        this.data = data;
    }
}

export class RGBHealth {

    connected: boolean;
    lastUpTime: number;
    state: State;
    lastStateChange: number;
    staleState: boolean
    data: string
    hue: number
    saturation: number
    colorTemp: number
    brightness: number

    constructor(connected: boolean,
                lastUpTime: number,
                state: State,
                lastStateChange: number,
                stateState: boolean,
                data: string = "",
                hue: number,
                saturation: number,
                colorTemp: number,
                brightness: number,
    ) {
        this.connected = connected;
        this.lastUpTime = lastUpTime;
        this.state = state;
        this.lastStateChange = lastStateChange
        this.staleState = stateState
        this.data = data;
        this.hue = hue;
        this.brightness = brightness;
        this.colorTemp = colorTemp;
        this.saturation = saturation;
    }
}
