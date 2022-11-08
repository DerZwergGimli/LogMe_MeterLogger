import { createApp } from "vue";
import "./index.css";
import "./style.css";
import App from "./App.vue";
import HomeView from "./views/HomeView.vue";
import SettingsView from "./views/SettingsView.vue";
import SerialView from "./views/SerialView.vue";
import UpdateView from "./views/UpdateView.vue";
import { createRouter, createWebHashHistory } from "vue-router";
import "flowbite";

const routes = [
  { path: "/", component: HomeView },
  { path: "/settings", component: SettingsView },
  { path: "/serial", component: SerialView },
  { path: "/update", component: UpdateView },
];

const router = createRouter({
  history: createWebHashHistory(),
  routes,
});

createApp(App).use(router).mount("#app");
