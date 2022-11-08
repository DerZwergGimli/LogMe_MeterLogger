<template>
  <div class="box m-3 border-2 rounded-md p-2 space-y-2">
    <sensor-component
      :index="$route.params.id"
      :history="sensor_store.history[props.id]"
      :meter_name="sensor_store.sensors[props.id]['sensor']"
      :meter_count="sensor_store.sensors[props.id]['1-0:1.8.0/255']"
      :meter_power="sensor_store.sensors[props.id]['1-0:16.7.0/255']"
    ></sensor-component>
    <vue-json-pretty
      class="border-2 rounded-md p-2"
      :data="sensor_store.sensors[props.id]"
    />
  </div>
</template>

<script setup lang="ts">
import VueJsonPretty from "vue-json-pretty";
import "vue-json-pretty/lib/styles.css";
import { defineProps } from "vue";

import SensorComponent from "../components/SensorComponent.vue";
import { useSensorStore } from "../stores/sensorStore";

const props = defineProps(["id"]);

const sensor_store = useSensorStore();
</script>

<style scoped></style>
