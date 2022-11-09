<script setup lang="ts">
const baseurl = window.location.origin;
import { useDark, useToggle, usePreferredDark } from "@vueuse/core";

const isDark = useDark();
const toggleDark = useToggle(isDark);
</script>

<template>
  <nav
    class="bg-white border-gray-200 px-2 sm:px-4 py-2.5 rounded dark:bg-gray-900 shadow-lg shadow-pink-500/50 rounded-b-lg"
  >
    <div class="container flex flex-wrap justify-between items-center mx-auto">
      <a href="#" class="flex items-center space-x-1">
        <svg width="32" height="32" viewBox="0 0 32 32">
          <path
            :fill="isDark ? 'white' : 'black'"
            d="M26 16a9.928 9.928 0 0 0-1.14-4.618l-1.495 1.496A7.948 7.948 0 0 1 24 16zm-2.586-6L22 8.586L17.285 13.3A2.966 2.966 0 0 0 16 13a3 3 0 1 0 3 3a2.966 2.966 0 0 0-.3-1.285zM16 17a1 1 0 1 1 1-1a1.001 1.001 0 0 1-1 1zm0-9a7.952 7.952 0 0 1 3.122.635l1.496-1.496A9.986 9.986 0 0 0 6 16h2a8.01 8.01 0 0 1 8-8z"
          />
          <path
            :fill="isDark ? 'white' : 'black'"
            d="M16 30a14 14 0 1 1 14-14a14.016 14.016 0 0 1-14 14Zm0-26a12 12 0 1 0 12 12A12.014 12.014 0 0 0 16 4Z"
          />
        </svg>
        <span
          class="self-center text-xl font-semibold whitespace-nowrap dark:text-white"
          >LogMe</span
        >
      </a>
      <button
        data-collapse-toggle="navbar-default"
        type="button"
        class="inline-flex items-center p-2 ml-3 text-sm text-gray-500 rounded-lg md:hidden hover:bg-gray-100 focus:outline-none focus:ring-2 focus:ring-gray-200 dark:text-gray-400 dark:hover:bg-gray-700 dark:focus:ring-gray-600"
        aria-controls="navbar-default"
        aria-expanded="false"
      >
        <span class="sr-only">Open main menu</span>
        <svg
          class="w-6 h-6"
          aria-hidden="true"
          fill="currentColor"
          viewBox="0 0 20 20"
          xmlns="http://www.w3.org/2000/svg"
        >
          <path
            fill-rule="evenodd"
            d="M3 5a1 1 0 011-1h12a1 1 0 110 2H4a1 1 0 01-1-1zM3 10a1 1 0 011-1h12a1 1 0 110 2H4a1 1 0 01-1-1zM3 15a1 1 0 011-1h12a1 1 0 110 2H4a1 1 0 01-1-1z"
            clip-rule="evenodd"
          ></path>
        </svg>
      </button>
      <div class="hidden w-full md:block md:w-auto" id="navbar-default">
        <ul
          class="flex flex-col p-4 mt-4 bg-gray-50 rounded-lg border border-gray-100 md:flex-row md:space-x-8 md:mt-0 md:text-sm md:font-medium md:border-0 md:bg-white dark:bg-gray-800 md:dark:bg-gray-900 dark:border-gray-700"
        >
          <li>
            <router-link
              to="/"
              class="block py-2 pr-4 pl-3 text-gray-700 rounded hover:bg-gray-100 md:hover:bg-transparent md:border-0 md:hover:text-blue-700 md:p-0 dark:text-gray-400 md:dark:hover:text-white dark:hover:bg-gray-700 dark:hover:text-white md:dark:hover:bg-transparent"
              >Home</router-link
            >
          </li>
          <li>
            <router-link
              to="serial"
              class="block py-2 pr-4 pl-3 text-gray-700 rounded hover:bg-gray-100 md:hover:bg-transparent md:border-0 md:hover:text-blue-700 md:p-0 dark:text-gray-400 md:dark:hover:text-white dark:hover:bg-gray-700 dark:hover:text-white md:dark:hover:bg-transparent"
              >WebSerial</router-link
            >
          </li>
          <li>
            <router-link
              to="update"
              class="block py-2 pr-4 pl-3 text-gray-700 rounded hover:bg-gray-100 md:hover:bg-transparent md:border-0 md:hover:text-blue-700 md:p-0 dark:text-gray-400 md:dark:hover:text-white dark:hover:bg-gray-700 dark:hover:text-white md:dark:hover:bg-transparent"
              >Update</router-link
            >
          </li>
          <li>
            <router-link
              to="settings"
              class="block py-2 pr-4 pl-3 text-gray-700 rounded hover:bg-gray-100 md:hover:bg-transparent md:border-0 md:hover:text-blue-700 md:p-0 dark:text-gray-400 md:dark:hover:text-white dark:hover:bg-gray-700 dark:hover:text-white md:dark:hover:bg-transparent"
              >Settings</router-link
            >
          </li>
          <li>
            <button @click="toggleDark()">
              <svg v-if="isDark" width="20" viewBox="0 0 32 32">
                <path
                  fill="white"
                  d="M13.502 5.414a15.075 15.075 0 0 0 11.594 18.194a11.113 11.113 0 0 1-7.975 3.39c-.138 0-.278.005-.418 0a11.094 11.094 0 0 1-3.2-21.584M14.98 3a1.002 1.002 0 0 0-.175.016a13.096 13.096 0 0 0 1.825 25.981c.164.006.328 0 .49 0a13.072 13.072 0 0 0 10.703-5.555a1.01 1.01 0 0 0-.783-1.565A13.08 13.08 0 0 1 15.89 4.38A1.015 1.015 0 0 0 14.98 3Z"
                />
              </svg>
              <svg v-else width="20" viewBox="0 0 32 32">
                <path
                  fill="black"
                  d="M15 2h2v5h-2zm6.688 6.9l3.506-3.506l1.414 1.414l-3.506 3.506zM25 15h5v2h-5zm-3.312 8.1l1.414-1.413l3.506 3.506l-1.414 1.414zM15 25h2v5h-2zm-9.606.192L8.9 21.686l1.414 1.414l-3.505 3.506zM2 15h5v2H2zm3.395-8.192l1.414-1.414L10.315 8.9L8.9 10.314zM16 12a4 4 0 1 1-4 4a4.005 4.005 0 0 1 4-4m0-2a6 6 0 1 0 6 6a6 6 0 0 0-6-6Z"
                />
              </svg>
            </button>
          </li>
        </ul>
      </div>
    </div>
  </nav>
</template>
