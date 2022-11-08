<template>
  <div class="m-3 flex justify-center flex-col space-y-2">
    <h1 class="text-4xl text-center">LogMe - SmartMeterLogger</h1>

    <div class="flex justify-center">
      <div v-if="sensor_store.sensors">
        <div
          v-for="(sensor, index) in sensor_store.sensors"
          key="sensor"
          class="box"
        >
          <router-link :to="'/sensor/' + index">
            <div>
              <sensor-component
                :index="index"
                :history="sensor_store.history[index]"
                :meter_name="sensor['sensor']"
                :meter_count="sensor['1-0:1.8.0/255']"
                :meter_power="sensor['1-0:16.7.0/255']"
              ></sensor-component>
            </div>
          </router-link>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import SensorComponent from "../components/SensorComponent.vue";
import { useSensorStore } from "../stores/sensorStore";

const sensor_store = useSensorStore();
</script>
