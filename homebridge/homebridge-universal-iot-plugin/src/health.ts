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

    constructor(connected: boolean,
                lastUpTime: number,
                state: State,
                lastStateChange: number,
                stateState: boolean
    ) {
        this.connected = connected;
        this.lastUpTime = lastUpTime;
        this.state = state;
        this.lastStateChange = lastStateChange
        this.staleState = stateState
    }
}

