import Vue from 'vue'
import App from './App.vue'
import VueMqtt from 'vue-mqtt';

Vue.config.productionTip = false
Vue.use(VueMqtt, 'ws://iot.eclipse.org/ws');
new Vue({
  render: h => h(App),
}).$mount('#app')
