import axios from 'axios';

export default {
    methods: {
        tempControl(command) {
            return axios.put("/api/devices/mode/3/", {
                id: 3,
                name: 'ac',
                data: {
                    command: command
                },
                config: {
                    bluetoothOnly: true
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