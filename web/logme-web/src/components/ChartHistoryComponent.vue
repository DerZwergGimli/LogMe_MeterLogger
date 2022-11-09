<script lang="ts" setup>
import { ref } from "vue";

const props = defineProps(["xvalues", "datapoints"]);

const chartOptions = ref({
  chart: {
    id: "line-chart",
    type: "line",
    animations: {
      enabled: true,
      easing: "linear",
    },
    toolbar: {
      show: true,
    },
    zoom: {
      enabled: false,
    },
  },
  stroke: {
    curve: "smooth",
  },
  xaxis: {
    type: "datetime",
    categories: props.xvalues,
  },
});

const series = ref([
  {
    name: "series-1",
    data: props.datapoints,
  },
]);
</script>

<template>
  <div id="chart">
    <apexchart
      type="line"
      height="350"
      :options="chartOptions"
      :series="series"
    ></apexchart>
  </div>
</template>
