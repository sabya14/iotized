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
              @click="tempControl('1')"
              text
              height="40px"
              width="40px"
              right

          >
            <v-icon>mdi-lightbulb-on-outline</v-icon>
          </v-btn>
          <v-btn
              @click="tempControl('2')"
              text
              height="40px"
              width="40px"
              right

          >
            <v-icon>mdi-lightbulb-off-outline</v-icon>
          </v-btn>
        </v-card-actions>
      </div>

    </div>
  </v-card>
</template>
<script>
import ac_remote from '../data/ac_remote'

export default {
  name: 'AC',
  props: {
    item: {}
  },
  mixins: [ac_remote]
}
</script>