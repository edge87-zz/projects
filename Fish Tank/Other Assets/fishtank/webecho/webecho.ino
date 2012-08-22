#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x86, 0xFC }; //MAC of my shield 
IPAddress ip(172, 16, 10, 60); // Should be on same network as device accessing or accessable through NAT

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

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
	webserver();
}

void webserver(){
// Check for incomming connections
	EthernetClient client = server.available();
  
//Our webserv variables
	char current;
	boolean keepcutting = true;
	String htmlcmd, postCommand, postValue, getCommand;
  
	if (client) {
		while (client.connected()) {
			if (client.available()) {
				current = client.read();
		
				while(current != ' '){
					htmlcmd += current;
					current = client.read();
				};
		
				if(htmlcmd == "POST"){
					//bleed off the "extra" crap
					current = client.read();
			
					while(keepcutting){
						current = client.read();
						if (current == '\n'){
							current = client.read();
							if (current == '\n'){
								keepcutting = false;
							}
					
							else if (current == '\r'){	
								//eat last new line
								current = client.read();
								keepcutting = false;
							}
						}
					}
					
				//Read POST Command
				while(current != '='){
					current = client.read();
				
					if (current != '=' && current !='\n' && current !='\r'){
						postCommand += current;
					}
				}
			
				//Read Post Command Value
				for(int i = 0; i < 3; i++){
					current = client.read();
					int t = int(current);
				
					//See if it is a Upper Case Char
					if (t >= 65 && t <= 90){
						postValue += current;
					}
				
					//See if its a Lower Case Char
					else if (t >= 97 && t <= 122){
						postValue += current;
					}
				
					//Isn't printable we aren't printing it to the string
					else{
						break;
					}	
				}

				//Take action based on command and value
				if (postCommand == "heater"){
					Serial.write("Found Heater Command\n");
				
					if(postValue == "off"){
						Serial.write("Turning Heater Off\n");
						//Set Global Heater Varable
					}
				
					else if (postValue == "on"){
						Serial.write("Turning Heater On\n");
						//Set Global Heater Varable
					}
				
					else{
						Serial.write("Bad heater command\n");
					}
				}
			
				//Sent Browser back to page original page..
				client.println("HTTP/1.1 200 OK");
				client.println("Content-Type: text/html");
				client.println();
				client.println("<!doctype html><html><head><title>Redirect</title><body><script type='text/javascript'>history.back();</script></body></html>");
			}//End POST processing
		
				if(htmlcmd == "GET"){
					//Remove '/' from stream. We want filename. This also brings the first char of the filename into the current variable
					current = client.read();
					current = client.read();
			
					while(current != ' '){
						if(current != ' '){
							getCommand += current;
						}
						current = client.read();
					}
			
					if(getCommand == "something.js"){
						Serial.write("Got a GET request for something.js\n");
				
						//Repond with our something.js file
					}
				}
		
			break;
			}//End if web client is available
		}//End while connected
    
		// give the web browser time to receive the data
		delay(1);
    
		// close the connection:
		client.stop();
		Serial.write("Client Dead\n");
	
	}//End if client
}//End Function






