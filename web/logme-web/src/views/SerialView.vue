<script setup lang="ts">
const baseurl = window.location.origin;
</script>

<template>
  <div class="m-3 text-center">
    <a
      :href="baseurl + '/webserial'"
      type="button"
      class="text-white bg-blue-700 hover:bg-blue-800 focus:outline-none focus:ring-4 focus:ring-blue-300 font-medium rounded-full text-sm px-5 py-2.5 text-center mr-2 mb-2 dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800"
      >extend</a
    >

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
