import Vue from 'vue';

import 'keen-ui/dist/keen-ui.css';

import './assets/styles/global.css';

import App from './components/App';

import h264Helper from './helpers/h264Helper';

Vue.filter('naluTypeDisplayed', h264Helper.naluTypeDisplayed);

const app = new Vue({
  render: (h) => h(App),
});

app.$mount('[data-app]');
