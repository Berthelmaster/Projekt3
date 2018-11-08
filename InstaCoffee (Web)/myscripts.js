var wsUri = "ws://10.9.8.2:3000/";
var output;
var coffeeselect = 0;
var coffeeStrength = 2;
var cupSize = 2;
var brewTime;
var filter = 1;

var sliderCoffeeStrength = document.getElementById("myStrength");
var outputCoffeeStrength = document.getElementById("strengthslider");
outputCoffeeStrength.innerHTML = sliderCoffeeStrength.value;

sliderCoffeeStrength.oninput = function() {
  outputCoffeeStrength.innerHTML = this.value;
  coffeeStrength = this.value;
}

var sliderCupSize = document.getElementById("myCupSize");
var outputCupSize = document.getElementById("cupsizeslider");
outputCupSize.innerHTML = "Medium";

sliderCupSize.oninput = function() {
  cupSize = this.value;

switch(cupSize) {
    case '1':
        outputCupSize.innerHTML = "Small";
        break;
    case '2':
        outputCupSize.innerHTML = "Medium";
        break;
    case '3':
        outputCupSize.innerHTML = "Large";
        break;
    default:
        break;
}

  
  
}


function init()
{
  output = document.getElementById("output");
  testWebSocket();

  //Sættes et andet sted eller tilføj refresh
  setTime();
}

function testWebSocket()
{
  websocket = new WebSocket(wsUri);
  websocket.onopen = function(evt) { onOpen(evt) };
  websocket.onclose = function(evt) { onClose(evt) };
  websocket.onmessage = function(evt) { onMessage(evt) };
  websocket.onerror = function(evt) { onError(evt) };
}

function onOpen(evt)
{
  writeToScreen("CONNECTED");
  doSend("Connection open");
}

function onClose(evt)
{
  writeToScreen("DISCONNECTED");
}

function onMessage(evt)
{
  writeToScreen('<span style="color: blue;">RESPONSE: ' + evt.data+'</span>');
  //var filter = evt.data
}

function onError(evt)
{
  writeToScreen('<span style="color: red;">ERROR:</span> ' + evt.data);
}

function doSend(message)
{
  websocket.send(message);
}

function writeToScreen(message)
{
  var pre = document.createElement("p");
  pre.style.wordWrap = "break-word";
  pre.innerHTML = message;
  output.appendChild(pre);
}

window.addEventListener("load", init, false);

function clickOnCoffee1()
{
  coffeeselect = 1;
  document.getElementById("merrild").style.border = "3px solid green";
  document.getElementById("peterlarsen").style.border = "3px dotted black";
}

function clickOnCoffee2()
{
  coffeeselect = 2;
  document.getElementById("peterlarsen").style.border = "3px solid green";
  document.getElementById("merrild").style.border = "3px dotted black";
}

function clickOnOrderCoffee()
{
  if (filter<4){
  var message = "You ordered coffee #" + String(coffeeselect) + ", Strength: " + String(coffeeStrength) + ", Cup size: " + String(cupSize);
  writeToScreen(message);
  writeToScreen("%"+coffeeselect+", "+coffeeStrength+", "+cupSize);
  doSend("%"+coffeeselect+", "+coffeeStrength+", "+cupSize);
  } 
  else alert("No more clean filters");

if (filter>=4) {
  document.getElementById("status").innerHTML="Out of clean filters";
  document.getElementById("status").style.color="red";
  }

  filter++; //SKAL FJERNES KUN TIL TEST
}


function setBrewTime()
{
  brewTime = document.getElementById("brewHour").value;
  brewTime = brewTime + "-" + document.getElementById("brewDate").value;

  var message = "You ordered coffee #" + String(coffeeselect) + ", Strength: " + String(coffeeStrength) + ", Cup size: " + String(cupSize);
  writeToScreen(message);
  doSend("&"+coffeeselect+", "+coffeeStrength+", "+cupSize+", "+brewTime);
  writeToScreen("&"+coffeeselect+", "+coffeeStrength+", "+cupSize+", "+brewTime);
}

function setTime()
{
 var today = new Date();
 var dd = today.getDate(); //day
 var mm = today.getMonth()+1; //January is 0
 var yyyy = today.getFullYear(); 

 if (dd<10) {
  dd="0"+dd;
 }
 if (mm<10) {
  mm="0"+mm;
 }

 document.getElementById("brewDate").value=String(yyyy+"-"+mm+"-"+dd);
 

}