<script setup lang="ts">
import InfluxConfig from "../components/InfluxConfig.vue";
</script>

<template>
  <div class="m-3">
    <h1 class="text-4xl">Settings</h1>

    <div class="flex justify-center">
      <div>
        <div class="box">
          <h5 class="box-header">Info</h5>
          <div class="box-content">
            <div class="flex flex-row space-x-2">
              <p>IP</p>
              <p>0.0.0.0</p>
            </div>

            <div class="flex flex-row space-x-2">
              <p>Wifi</p>
              <p>Some-Name</p>
            </div>
          </div>
        </div>

        <div class="box">
          <InfluxConfig />
        </div>
      </div>
    </div>
  </div>
</template>
