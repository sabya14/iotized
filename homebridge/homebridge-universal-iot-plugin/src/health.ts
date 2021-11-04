export enum State {
    Up = 1,
    Down = 0
}

export class Health {

    connected: boolean;
    lastUpTime: number;
    state: State;

    constructor(connected: boolean,
                lastUpTime: number,
                state: State
    ) {
        this.connected = connected;
        this.lastUpTime = lastUpTime;
        this.state = state;
    }
}

