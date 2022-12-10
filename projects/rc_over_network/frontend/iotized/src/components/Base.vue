<template>
  <v-container>
    <v-card
        max-width="1000"
        class="mx-auto"
    >
      <v-app-bar
          dark
          color="teal"
      >
        <v-toolbar-title>My Devices</v-toolbar-title>

        <v-spacer></v-spacer>

        <v-btn icon>
          <v-icon>mdi-magnify</v-icon>
        </v-btn>
      </v-app-bar>

      <v-container>
        <v-row>
          <v-col
              v-for="(item, i) in rc_car"
              :key="i"
          >
            <RCCar :item="item"/>
          </v-col>

        </v-row>
        <v-row>
          <v-col
              v-for="(item, i) in acs"
              :key="i"
          >
            <AC :item="item"/>
          </v-col>
        </v-row>
      </v-container>
    </v-card>
  </v-container>

</template>

<script>
import RCCar from "@/components/RCCar";
import AC from "@/components/AC_Remote";

export default {
  name: 'HelloWorld',
  components: {RCCar, AC},
  data: () => ({
    rc_car: [
      {
        color: '#1F7087',
        src: 'https://cdn.vuetifyjs.com/images/cards/foster.jpg',
        title: 'RC CAR',
        artist: 'Drive the rc car',
      },
    ],
    acs: [
      {
        color: '#dd1673',
        src: 'https://cdn.vuetifyjs.com/images/cards/foster.jpg',
        title: 'AC',
        artist: 'Control the AC',
      },
    ],
  }),
}
</script>
