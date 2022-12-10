<template>
  <v-card
      :color="item.color"
      dark
  >
    <div class="">
      <div>
        <v-card-title
            class="text-h5"
            v-text="item.title"
        ></v-card-title>
        <v-card-subtitle align="left" v-text="item.artist"></v-card-subtitle>
        <v-row>

        </v-row>
        <v-card-actions>


          <v-btn
              @click="driveCar('forward', 0.22)"
              text
              height="40px"
              width="40px"
              right

          >
            <v-icon>mdi-arrow-up-bold</v-icon>
          </v-btn>
          <v-btn
              @click="driveCar('backward', 0.22)"
              text
              height="40px"
              width="40px"
              right

          >
            <v-icon>mdi-arrow-down-bold</v-icon>
          </v-btn>
          <v-btn @click="driveCar('right', 0.22)"
                 text
                 height="40px"
                 width="40px"
                 right

          >
            <v-icon>mdi-arrow-right-bold</v-icon>
          </v-btn>
          <v-btn
              @click="driveCar('left', 0.22)"
              text
              height="40px"
              width="40px"
              right

          >
            <v-icon>mdi-arrow-left-bold</v-icon>
          </v-btn>
          <v-btn
              @click="driveCar('stop', 0.22)"
              text
              height="40px"
              width="40px"
              right

          >
            <v-icon>mdi-stop</v-icon>
          </v-btn>

        </v-card-actions>
      </div>

    </div>
  </v-card>
</template>
<script>
import rc_car from '../data/rc_car'

export default {
  name: 'RCCar',
  props: {
    item: {}
  },
  mixins: [rc_car]
}
</script>