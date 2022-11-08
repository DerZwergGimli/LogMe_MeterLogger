<script setup lang="ts">
const baseurl = window.location.origin;
</script>

<template>
  <div class="m-3 text-center">
    <a :href="baseurl + '/update'">extend</a>
    <div class="flex justify-center">
      <iframe
        class="w-full h-screen"
        :src="baseurl + '/update'"
        title="description"
      ></iframe>
    </div>
  </div>
</template>
