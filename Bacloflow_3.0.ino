#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <ESPAsyncTCP.h>
#include <SPI.h>
#include <Wire.h>


// Replace with your network credentials
const char* ssid = "4703 Unit B wifi";
const char* password = "goinlivingb123";

//#define DHTPIN 4 // Digital pin 2 (GPIO 4) connected to the DHT sensor

// Uncomment the type of sensor in use:
//#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
const int Charge = 5;
const int Discharge = A0;
DHT dht(DHTPIN, DHTTYPE);

// current temperature & humi dity, this will be updated in loop function
float t = 0.0;
float tf = 0.0;
float h = 0.0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

unsigned long previousMillis = 0; //stoe last time DHT was updated
const long interval = 1000; // Updates DHT readings every 1 seconds

//web page
const char index_html[] PROGMEM = R"webpage(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://code.highcharts.com/8.0/highcharts.js"></script>
  <style>
  body {
    min-width: 300px;
    max-width: 800px; 
    height: 400px;
    margin: 0 auto;
    }
h2 {
  font-family: Arial;
  font-size: 2.5rem;
  text-align: center;
}
</style>
</head>
<body>
<h2>Bacloflow Flow chart</h2>
  <div id="temperature-chart" class="container"></div>
    <div id="fahrenheit-chart" class="container"></div>
    <div id="humidity-chart" class="container"></div>
</body>
<script>
var chartT = new Highcharts.Chart({
chart:{ renderTo : 'temperature-chart' },
title: { text: 'Flow Data' },
series: [{
showInLegend: false,
data: []
}],
plotOptions: {
line: { animation: false,
dataLabels: { enabled: true }
},
series: { color: '#059e8a' }
},
xAxis: { type: 'datetime',
dateTimeLabelFormats: { second: '%H:%M:%S' }
},
yAxis: {
title: { text: 'Observed Flow' }
},
credits: { enabled: false }
});
setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
var x = (new Date()).getTime(),
y = parseFloat(this.responseText);
if(chartT.series[0].data.length > 50) {
chartT.series[0].addPoint([x, y], true, true, true);
} else {
chartT.series[0].addPoint([x, y], true, false, true);
}
}
};
xhttp.open("GET", "/temperature", true);
xhttp.send();
}, 1000 ) ;
</script>
</html>)webpage";

void setup(){
// Serial port for debugging purposes
Serial.begin(9600);


// Connect to Wi-Fi
WiFi.begin(ssid, password);
Serial.println("Connecting to WiFi");
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println(".");
}

// Print ESP32 Local IP Address
Serial.println(WiFi.localIP());

// Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/html", index_html);
});
server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(t).c_str());
});
server.on("/fahrenheit", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(tf).c_str());
});
server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(h).c_str());
});

// Start server
server.begin();
dht.begin();
}

void loop(){ 
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
// save the last time you updated the DHT values
previousMillis = currentMillis;
// Read temperature as Celsius (the default)
float currentT = dht.readTemperature();

// if temperature read failed, we don't want to change t value
if (isnan(currentT)) {
Serial.println("Failed to read from DHT sensor!");
Serial.println(currentT);
}
else {
t = currentT;
Serial.println(t);
}
// Read temperature as Fahrenheit 
float currentTf = dht.readTemperature(true);
// if temperature read failed, we don't want to change tf value
if (isnan(currentTf)) {
Serial.println("Failed to read from DHT sensor!");
}
else {
tf = currentTf;
Serial.println(tf);
}


// Read Humidity
float currentH = dht.readHumidity();
// if humidity read failed, we don't want to change h value 
if (isnan(currentH)) {
Serial.println("Failed to read from DHT sensor!");
}
else {
h = currentH;
Serial.println(h);
}
}
}
