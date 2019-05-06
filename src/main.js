import Vue from 'vue';

import 'keen-ui/dist/keen-ui.css';

import './assets/styles/global.css';

import App from './components/App';

import nalHelper from './helpers/nalHelper';

Vue.filter('nalTypeDisplayed', nalHelper.nalTypeDisplayed);

const app = new Vue({
  render: (h) => h(App),
});

app.$mount('[data-app]');
