<template>
  <v-app id="inspire">
    <v-navigation-drawer
        v-model="drawer"
        app
    >
    </v-navigation-drawer>
    <v-main>
      <Base/>
    </v-main>
  </v-app>
</template>

<script>
import Base from '../components/Base';

export default {
  components: {
      Base
  },
  data: () => ({ drawer: false }),
}
</script>