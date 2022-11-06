<script setup lang="ts">
import NavigationView from "./views/NavigationView.vue";
</script>

<template>
  <div id="app">
    <NavigationView />
    <router-view></router-view>
  </div>
</template>

<style scoped></style>
