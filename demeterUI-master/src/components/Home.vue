<template>
  <div>
    <div class="nav">
      <img src="../assets/Logo3.png" style="height: 130px; width: 130px;background-color:white"></img>
      <!-- <span style="color: white;font-weight: bold; font-size: 35pt; font-family: Georgia;text-align: center;">Demeter</span> -->
      <div class="topnav" style="margin-left:0px;">
        <a v-bind:class="{ 'active':  currentNav == 'home' }" href="#home" @click="changeTab('home')">Home</a>
        <a v-bind:class="{ 'active':  currentNav == 'graphs' } "href="#future" @click="changeTab('graphs')">Live Data</a>
        <a v-bind:class="{ 'active':  currentNav == 'about' } "href="#about" @click="changeTab('about')">About Us</a>
      </div>
    </div>
    <div name="home" class="main" v-if="currentNav == 'home'">
      <div class="box" style="">
        <span class="center-text">Manual Control</span><br/><br/><br/>
        <div style="float: left;text-align: left;">
          <div v-for="(item,key) in sprinklers" style="padding-left: 10px">
            <a href="#" @click="enableOne(key)" class="SmallButton">Enable</a>
            <a href="#" @click="disableOne(key)" class="SmallButton">Disable</a>
            <span class="status-text">Sprinkler '{{key}}' Online Status: <span v-bind:class="{ 't-green':  item==true, 't-red': item==false }">{{item}}</span></span><br/>
          </div>
        </div>
        <br/>
        <a href="#" @click="enableAll" class="LargeButton" style="margin-top: 50px;margin-right: 50px;">Enable All Sprinklers</a>
        <a href="#" @click="disableAll" class="LargeButton">Disable All Sprinklers</a>
      </div>
      <div class="box">
        <span class="center-text">Automatic Control</span>
      </div>
    </div>
    <div name="graphs" class="graphs" v-show="currentNav == 'graphs'">
      <span class="center-text" style="margin-top: 15px;">Data From PI (Refresh for latest)</span><br/><br/><button class="LargeButton" @click="reRender">REFRESH DATA</button><br/><br/>
      <span class="center-text" style="color: #1e90ff;margin-top: 15px;">Temperature</span>
      <div id="temp" class="box" style="width: 90%">
      </div>
      <span class="center-text" style="color: #1e90ff;margin-top: 15px;">Moisture</span>
      <div id="moist" class="box" style="width: 90%">
      </div>
      <span class="center-text" style="color: #1e90ff;margin-top: 15px;">Humidity</span>
      <div id="humid" class="box" style="width: 90%">
      </div>
      <span class="center-text" style="color: #1e90ff;margin-top: 15px;">Ambient</span>
      <div id="ambient" class="box" style="width: 90%">
      </div>
    </div>
    <div name="about" class="main" v-if="currentNav == 'about'">
      <div class="box" style="width: 33%">
        Dennon
      </div>
      <div class="box" style="width: 33%">
        Tom
      </div>
      <div class="box" style="width: 33%">
        Alex
      </div>
    </div>
  </div>
</template>

<script>
import Datepicker from 'vuejs-datepicker';
import * as d3 from "d3v4";
export default {
  name: 'Home',
  components: {
    Datepicker
  },
  data: function(){
    return {
      isActive: true,
      currentNav: "home",
      sprinklers: {
        '1': false,
        '2': false,
        '3': false,
        '4': false,
        '5': false
      }
    }
  },
  mounted() {
    var mqtt = require('mqtt')
    console.log(mqtt);
    //this.client = mqtt.connect({port: 1883, host: '192.168.0.100', username: 'zombo', password:'pi', keepalive:10000});
    //this.client = mqtt.connect('mqtt://test.mosquito.org');
//console.log(this.client);

    this.currentNav = "home";
    this.isActive = true;
    //this.client.subscribe('temp');
    console.log(this.client);
    console.log("HIT")
    //this.client.on('connect', function () {
    //  console.log("CONNECTED");
    //  this.client.subscribe('temp', function (err) {
     //   if (!err) {
     //     client.publish('temp', 'Hello mqtt')
     //   }
    //  })
    //})
    //this.client.on('message', function (topic, message) {
    //  console.log("HIT")
    //  console.log(message);
    //});
  },
  props: {
    msg: String
  },
  methods: {
    changeTab(tab){
      this.currentNav = tab;
      if(tab == 'graphs'){
        this.reRender();
      }
    },
    reRender(){
      this.renderGraph('temp');
      this.renderGraph('moist');
      this.renderGraph('humid');
      this.renderGraph('ambient');
    },
    enableOne(val){
      this.sprinklers[val] = true;
    },
    disableOne(val){
      this.sprinklers[val] = false;
    },
    enableAll(){
      for(let i in this.sprinklers){
        this.sprinklers[i] = true;
      }
    },
    disableAll(){
      for(let i in this.sprinklers){
        this.sprinklers[i] = false;
      }
    },
    renderGraph(arg){
      d3.select("#" + arg).html("");

      // set the dimensions and margins of the graph
      var margin = {top: 20, right: 20, bottom: 30, left: 50},
          width = 960 - margin.left - margin.right,
          height = 450 - margin.top - margin.bottom;

      // parse the date / time
      //3-12-2018 17:50:48
      var parseTime = d3.timeParse("%d-%m-%y %H:%M:%S");

      // set the ranges
      var x = d3.scaleTime().range([0, width]);
      var y = d3.scaleLinear().range([height, 0]);

      // define the line
      var valueline = d3.line()
          .x(function(d) { return x(d.date); })
          .y(function(d) { return y(d.close); });

      // append the svg obgect to the body of the page
      // appends a 'group' element to 'svg'
      // moves the 'group' element to the top left margin
      var svg = d3.select("#" + arg).append("svg")
          .attr("width", width + margin.left + margin.right)
          .attr("height", height + margin.top + margin.bottom)
        .append("g")
          .attr("transform",
                "translate(" + margin.left + "," + margin.top + ")");
    	console.log("req");
    	var d3data;
    	d3.text("/" + arg + "/log000.txt", function(error, d3data){
    	d3data = '[' + d3data;
    	d3data = d3data.substring(0, d3data.length-1);
      d3data = d3data.substring(0, d3data.length-1);
    	d3data = d3data + "]";
      d3data = JSON.parse(d3data);
      var data = d3data;
      if (error) throw error;
      for(var i in data){
        data[i].date = data[i].time[2] + "-" + data[i].time[1] + "-" + data[i].time[0].toString().substring(2,data[i].time[0].length) + " " + data[i].time[3] + ":" + data[i].time[4] + ":" + data[i].time[5];
      }
      // format the data
      data.forEach(function(d) {
          d.date = parseTime(d.date);
          d.close = +d.message;
      });
      // Scale the range of the data
      x.domain(d3.extent(data, function(d) { return d.date; }));
      y.domain([0, d3.max(data, function(d) { return d.close; })]);

      // Add the valueline path.
      svg.append("path")
          .data([data])
          .attr("class", "line")
          .style("fill", "none")
          .style("stroke", "steelblue")
          .style("stoke-width", "2px")
          .attr("d", valueline);

      // Add the X Axis
      svg.append("g")
          .attr("transform", "translate(0," + height + ")")
          .call(d3.axisBottom(x));

      // Add the Y Axis
      svg.append("g")
          .call(d3.axisLeft(y));



	})


    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.line {
  fill: none;
  stroke: steelblue;
  stroke-width: 2px;
}
.main{
  display: flex;
  height: 100%;
  width: 100%;
  min-height: 98vh;
  background-color: lightgrey;
}
.graphs{
  display: flex;
  flex-direction: column;
  height: 100%;
  min-height: 98vh;
  width: 100%;
  background-color: lightgrey;
}
.box{
  background-color: white;
  margin: 20px;
  width: 50%;
  min-height: 450px;
  height: 100%;
  box-shadow:.5em .3em 1em;
}
.center-text{
  text-align: center;
  font-weight: bold;
  font-size: 25pt;
}
.status-text{
  text-align: center;
  font-weight: bold;
  font-size: 20pt;
  padding-top: 2px;
}
.LargeButton {
	-moz-box-shadow: 0px 10px 14px -7px #0C3C60;
	-webkit-box-shadow: 0px 10px 14px -7px #0C3C60;
	box-shadow: 0px 10px 14px -7px #0C3C60;
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #599bb3), color-stop(1, #408c99));
	background:-moz-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-webkit-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-o-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-ms-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:linear-gradient(to bottom, #0C3C60 5%, #0C3C60 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#0C3C60', endColorstr='#0C3C60',GradientType=0);
	background-color:#0C3C60;display: inline-block;
	-moz-border-radius:13px;
	-webkit-border-radius:13px;
	border-radius:13px;
	border:1px solid #0C3C60;
	display:inline-block;
	cursor:pointer;
	color:#fff;
	font-family:Arial;
	font-size:22px;
	font-weight:bold;
	padding:8px 16px;
	text-decoration:none;
	text-shadow:0px 1px 0px #0C3C60;
}
.LargeButton:hover {
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #408c99), color-stop(1, #599bb3));
	background:-moz-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-webkit-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-o-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-ms-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:linear-gradient(to bottom, #0C3C60 5%, #0C3C60 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#408c99', endColorstr='#599bb3',GradientType=0);
	background-color:#408c99;
}
.LargeButton:active {
	position:relative;
	top:1px;
}
.SmallButton {
	-moz-box-shadow: 0px 10px 14px -7px #0C3C60;
	-webkit-box-shadow: 0px 10px 14px -7px #0C3C60;
	box-shadow: 0px 10px 14px -7px #0C3C60;
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #599bb3), color-stop(1, #408c99));
	background:-moz-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-webkit-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-o-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-ms-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:linear-gradient(to bottom, #0C3C60 5%, #0C3C60 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#0C3C60', endColorstr='#0C3C60',GradientType=0);
	background-color:#0C3C60;
	-moz-border-radius:13px;
	-webkit-border-radius:13px;
	border-radius:5px;
  margin: 5px;
	border:1px solid #0C3C60;
	display:inline-block;
	cursor:pointer;
	color:#fff;
	font-family:Arial;
	font-size:10px;
	font-weight:bold;
	padding:10px 27px;
	text-decoration:none;
	text-shadow:0px 1px 0px #0C3C60;
  margin-right: 10px;
}
.SmallButton:hover {
	background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #408c99), color-stop(1, #599bb3));
	background:-moz-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-webkit-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-o-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:-ms-linear-gradient(top, #0C3C60 5%, #0C3C60 100%);
	background:linear-gradient(to bottom, #0C3C60 5%, #0C3C60 100%);
	filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#408c99', endColorstr='#599bb3',GradientType=0);
	background-color:#408c99;
}
.SmallButton:active {
	position:relative;
	top:1px;
}
.nav{
  display: flex;
  background-color: #0C3C60;
  text-align: center;
  align-items: center;
  width: 100%;
}
.topnav {
    display: flex;
    align-self: center;
    vertical-align: middle;
    background-color: #0C3C60;
    height: 100%;
    overflow: hidden;
    float: right;
    align-self:auto;
    width: 100%;
    justify-content: flex-end;
    margin-right: 50px;
}

/* Style the links inside the navigation bar */
.topnav a {
    float: left;
    color: #f2f2f2;
    text-align: center;
    padding: 24px 18px;
    text-decoration: none;
    font-size: 17pt;
    height: 100%;
}

/* Change the color of links on hover */
.topnav a:hover {
    background-color: #ddd;
    color: black;
}

/* Add a color to the active/current link */
.topnav a.active {
    background-color: #1e90ff;
    color: white;
}
.t-green{
  color: green;
}
.t-red{
  color: red;
}
</style>
