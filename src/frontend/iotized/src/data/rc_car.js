import axios from 'axios';

export default {
    methods: {
        driveCar(direction, speed) {
            return axios.put("/api/devices/mode/1/", {
                id: 1,
                name: 'car',
                data: {
                    direction: direction
                },
                config: {
                    speed: speed
                },
                device: 'arduino1'
            }).then(response => {
                console.log("Success")
                console.log(response)
            }).catch(error => {
                console.log(error)
            })
        }
    }


}