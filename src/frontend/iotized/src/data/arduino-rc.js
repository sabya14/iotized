import {jsonFetcher} from "./client";


export const changeDirection = ({direction, speed=0.5}) => jsonFetcher('/api/devices/mode/1/', {
    method: "PUT",
    headers: {
        'Content-Type': 'application/json'
    },
    body: JSON.stringify({
        id: 1,
        name: "car",
        data: {
            "direction": direction
        },
        "config": {
            "speed": speed
        },
        "device": "arduino1"
    })
});


export const arduinoRC = () => {
    return {
        changeDirection,
    };
};

export default arduinoRC
