/*
Fish Tank Monitor
Author: Andrew R. Edgerton

Description: This Arduino application monitors a connected fish tank. It reports back temperate, water height, last feed time, and other metrics. 

Last Updated: 20Aug12

Other Author Credits

#Web Server - Code Portion#
 Created (18 Dec 2009)
 By: David A. Mellis
 
 Modified (4 Sep 2010)
 By: Tom Igoe
 */
 
 /*
	Circuit:
		* Ethernet shield attached to pins: 10, 11, 12, 13
		* Ping))) Attached to pin: 2
		* Temperature Probe: Attached to Pin: 4
		* PH Probe:
		* Lights:
		* Pump Out:
		* Pump In:
		* Feeder:
		
	Author: Andrew R. Edgerton
	
	Description: Code has a web server setup to relay JS back to a browser as directed to by a web server's page. The return should
		be well formed java script vars. 
 */

#include <SPI.h>
#include <Ethernet.h>
#include "OneWire.h"

//Tank Configurations
const int tankHeight = 14;

//Constants
const int pingPin = 2;		//Ping))) Sensor Pin
const int DS18S20_Pin = 4;	//DS18S20 Signal pin on digital 2

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x86, 0xFC }; //MAC of my shield 
IPAddress ip(172,16,8, 177); // Should be on same network as device accessing or accessable through NAT

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

// Initialize The Temp Probe
OneWire ds(DS18S20_Pin);

//Tank Variables being sent to website
boolean heater = false;
boolean lights = false;
boolean refreshing = false;
int refresh_progress = 35; // In percent complete 0 = just started, 100 = done
float min_temp = 100.00f;
float max_temp = 20.00f;
float current_temp = 75.00f; 
float water_level = 0.00f; //in inches water level                
int last_feed[] = {22,2,2012,17,54,39}; //Day,Month,Year,Hour military,Minute,Second
int last_water_refresh[] = {22,2,2012,8,30,44}; //Day,Month,Year,Hour military,Minute,Second
int check_inv = 0;

void setup(){
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  
  Serial.begin(9600);
}

void loop(){
  // listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
			// send a standard http response header
			client.println("HTTP/1.1 200 OK");
			client.println("Content-Type: text/javascript");
			client.println();

			// Output our Javascript
			client.print("var refreshing = ");
			client.print(refreshing);
			client.println(";");
			
			client.print("var refresh_progress =");
			client.print(refresh_progress);
			client.println(";");
			
			client.print("var heater = ");
			client.print(heater);
			client.println(";");
			
			client.print("var min_temp = ");
			client.print(min_temp);
			client.println(";");
			
			client.print("var max_temp = ");
			client.print(max_temp);
			client.println(";");
			
			client.print("var current_temp = ");
			client.print(current_temp);
			client.println(";");
			
			client.print("var water_level = ");
			client.print(water_level);
			client.println(";");
			
			//Build two arrays to hold our time
			client.println("var last_feed_time = new Array();");
			client.println("var last_water_refresh = new Array();");
			
			client.print("last_feed_time[0] = ");
			client.print(last_feed[0]);
			client.println(";");
			
			client.print("last_feed_time[1] = ");
			client.print(last_feed[1]);
			client.println(";");
				
			client.print("last_feed_time[2] = ");
			client.print(last_feed[2]);
			client.println(";");
				
			client.print("last_feed_time[3] = ");
			client.print(last_feed[3]);
			client.println(";");
				
			client.print("last_feed_time[4] = ");
			client.print(last_feed[4]);
			client.println(";");
			
			client.print("last_feed_time[5] = ");
			client.print(last_feed[5]);
			client.println(";");
			
			client.print("last_water_refresh[0] = ");
			client.print(last_water_refresh[0]);
			client.println(";");
			
			client.print("last_water_refresh[1] = ");
			client.print(last_water_refresh[1]);
			client.println(";");
		
			client.print("last_water_refresh[2] = ");
			client.print(last_water_refresh[2]);
			client.println(";");
			
			client.print("last_water_refresh[3] = ");
			client.print(last_water_refresh[3]);
			client.println(";");
			
			client.print("last_water_refresh[4] = ");
			client.print(last_water_refresh[4]);
			client.println(";");
			
			client.print("last_water_refresh[5] = ");
			client.print(last_water_refresh[5]);
			client.println(";");

			break; // We're done with the webserver lets close it.
        }
		
        if (c == '\n'){
          // you're starting a new line
          currentLineIsBlank = true;
		  Serial.write(c);
        } 
        
        else if (c != '\r'){
          // you've gotten a character on the current line
          currentLineIsBlank = false;
		  Serial.write(c);
        }
      }//End if web client is available
    }//End while connected
    
    // give the web browser time to receive the data
    delay(1);
    
    // close the connection:
    client.stop();
	
  }//End if client
  
	if (check_inv < 1000){
		check_inv = check_inv + 1;
	}
	
	else{
	check_water_level();
	current_temp = getTemp();
	if (current_temp > max_temp){
		max_temp = current_temp;
	}
	
	if (current_temp < min_temp){
		min_temp = current_temp;
	}
	
	check_inv = 0;
	}
}

void check_water_level(){
	// establish variables for duration of the ping, 
	// and the distance result in inches and centimeters:
	long duration;

	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	pinMode(pingPin, OUTPUT);
	digitalWrite(pingPin, LOW);
	delayMicroseconds(2);
	digitalWrite(pingPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pingPin, LOW);

	// The same pin is used to read the signal from the PING))): a HIGH
	// pulse whose duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	pinMode(pingPin, INPUT);
	duration = pulseIn(pingPin, HIGH);

	// convert the time into a distance and correct for height left not height missing
	water_level = microsecondsToInches(duration);
 }

long microsecondsToInches(long microseconds){
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  
  // Tank our tank height and subtract the distance missing to know how much isn't missing (AKA the water height)
  
  return tankHeight - (microseconds / 74 / 2);
}

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Fehrenheit

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  TemperatureSum = (TemperatureSum * 1.8) + 32; //TemperatureSum is Celsius. Coverting to Fahrenheit.
  
  return TemperatureSum;
  
}
