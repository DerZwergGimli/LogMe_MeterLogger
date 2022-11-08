<template>
  <h5 class="box-header">Interface</h5>
  <div class="box-content space-y-2">
    <div class="grid grid-cols-3 gap-4 border-2 rounded-md p-2">
      <div>Index</div>
      <div class="text-right">{{ index }}</div>
      <div></div>
      <div>Name</div>
      <div class="text-right">{{ meter_name }}</div>
      <div></div>
      <div>Count</div>
      <div class="text-right">{{ (meter_count / 1000).toFixed(2) }}</div>
      <div>kWh</div>
      <div>Power</div>
      <div class="text-right">{{ meter_power }}</div>
      <div>W</div>
    </div>
    <div v-if="history" class="border-2 rounded-md p-2">
      <chart-history-component
        :xvalues="history.time"
        :datapoints="history.value"
      ></chart-history-component>
    </div>
  </div>
</template>

<script setup lang="ts">
import ChartHistoryComponent from "../components/ChartHistoryComponent.vue";
const props = defineProps([
  "index",
  "meter_name",
  "meter_id",
  "meter_count",
  "meter_power",
  "history",
]);
</script>

<style scoped></style>
