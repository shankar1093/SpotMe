
var value2 = localStorage.getItem("L");
console.log(value2);

var arr =[];
function populate_array(X, Y, Z){
	console.log("inside this function");
	arr.push(X);
	arr.push(Y);
	arr.push(Z);

	var req = new XMLHttpRequest();
	console.log("GET", )

}


function write_file(){
	console.log("eric is gay")
	var fs = require('fs');

	fs.writeFile("/tmp/test", "Hey there!", function(err) {
	    if(err) {
	        console.log(err);
	    } else {
	        console.log("The file was saved!");
	    }
	}); 

}
Pebble.addEventListener("ready",
                        function(e) {
                          console.log("ready!" + e.ready);
						  

						  // console.log(JSON.stringify(e.data));
						  console.log("getting ready to recieve data from the pebble");
                       });

Pebble.addEventListener("appmessage",
						function(e) {
						  console.log("message recieved");
						  var X = e.payload.x_axis;

						  // if(X=="select"){
						  // 	console.log("something");
						  // }
						  var Y = e.payload.y_axis;
						  var Z = e.payload.z_axis;
						  //populate_array(X,Y,Z);
						  console.log(arr.length);
						  // if(arr.length == 30){
						  // 	write_file();
						  // }

						  


						  //use this to display accel values. 
						  console.log(X);
						  console.log(Y);
						  console.log(Z);
							
						});


















   