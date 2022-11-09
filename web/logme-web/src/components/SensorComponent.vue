<template>
  <h5 class="box-header text-center">Interface {{ index }}</h5>
  <div class="box-content space-y-2">
    <div class="grid grid-cols-2 gap-4 rounded-md p-2 max-w-md">
      <div>Index</div>
      <div class="value">
        <div class="basis-3/4 text-right">{{ index }}</div>
        <div class="basis-1/4"></div>
      </div>

      <div>Name</div>
      <div class="value">
        <div class="basis-3/4 text-right">{{ meter_name }}</div>
        <div class="basis-1/4"></div>
      </div>

      <div>Count</div>
      <div class="value">
        <div class="basis-3/4 text-right">
          {{ (meter_count / 1000).toFixed(2) }}
        </div>
        <div class="basis-1/4">kWh</div>
      </div>

      <div>Power</div>
      <div class="value">
        <div class="basis-3/4 text-right">{{ meter_power }}</div>
        <div class="basis-1/4">W</div>
      </div>
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

<style scoped>
.value {
  @apply flex flex-row space-x-1 bg-blue-100 text-blue-800 font-semibold rounded dark:bg-blue-200 dark:text-blue-800;
}
</style>
