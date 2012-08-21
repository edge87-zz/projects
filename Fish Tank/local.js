var refreshing = true;						//Boolean Value. Is the tank currently refreshing water
var refresh_progress = 20;			    	//IF it is refreshing this value is a % that it is complete
var heater = true;							//Boolean Value value. Is the heater on or off.
var min_temp = 50;							//Lowest the temperature in F has been since last reset.
var max_temp = 100;							//Highest the temperature in F has been since last reset.
var current_temp = 73;	
var water_level = 10;

var last_feed_time = new Array(22,2,2012,17,54,39);
var last_water_refresh = new Array(21,8,2012,8,30,44);


//USE history.back(); to take them back!
