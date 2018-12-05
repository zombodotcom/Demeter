import Vue from 'vue'
import App from './App.vue'
// import VueMqtt from 'vue-mqtt';

Vue.config.productionTip = false
// Vue.use(VueMqtt, 'mqtt:://192.168.0.100',{port: 9001, username: "zombo", password:"pi"});
new Vue({
  render: h => h(App),
}).$mount('#app')
