<script setup lang="ts">
const baseurl = window.location.origin;
</script>

<template>
  <div class="m-3 text-center">
    <a :href="baseurl + '/webserial'">extend</a>
    <div class="flex justify-center">
      <iframe
        class="w-full h-screen"
        :src="baseurl + '/webserial'"
        title="description"
      ></iframe>
    </div>
  </div>
</template>

<style scoped>
.frame {
  height: 100%;
}
</style>
