<script setup lang="ts">
import NavigationView from "./views/NavigationView.vue";
import { useSensorStore } from "./stores/sensorStore";

const sensor_store = useSensorStore();
sensor_store.init();
</script>

<template>
  <div id="app">
    <NavigationView />
    <router-view></router-view>
  </div>
</template>

<style scoped></style>
