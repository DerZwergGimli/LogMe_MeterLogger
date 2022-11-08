// stores/counter.js
import { defineStore } from "pinia";

export const useSensorStore = defineStore("sensors", {
  state: () => ({
    ws: {} as WebSocket,
    sensors: [] as any,
    history: [{ time: [] as Array<number>, value: [] as Array<number> }],
  }),

  // could also be defined as
  // state: () => ({ count: 0 })
  actions: {
    init() {
      const baseurl = window.location.origin.replace("http://", "");

      if (import.meta.env.DEV) {
        this.ws = new WebSocket("ws://192.168.179.107/sensors");
      } else {
        this.ws = new WebSocket("ws://" + baseurl + "/sensors");
      }

      this.ws.onmessage = (event: any) => {
        if (event.data.includes("sensor")) {
          let data = JSON.parse(event.data);
          let found = this.sensors.findIndex(
            (sensor: any) => sensor.sensor === data.sensor
          );

          if (found == -1) {
            this.sensors.push(data);
          } else {
            this.sensors[found] = data;
            this.history[0].time.push(Date.now());
            this.history[0].value.push(data["1-0:16.7.0/255"]);
          }
        }
      };
    },
  },
});
