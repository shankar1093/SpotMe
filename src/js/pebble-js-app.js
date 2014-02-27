
var direction = localStorage.getItem("data");

// if(!direction){
// 	direction = "up";
// }

// function senddirection(direction) {
//  // var response;
//   var req = new XMLHttpRequest();
//   console.log("Starting http get -- 33");
//   //console.log(direction);
//   req.open("GET", "http://10.232.112.77:8080/"+ direction, true);

//   req.send();
// }

console.log("MAIN READY");

Pebble.addEventListener("ready",
                        function(e) {
                          console.log("ready!" + e.ready);
						  console.log(JSON.stringify(e.data));
						  console.log("preparing location"); 
						  console.log("I am gonna log data today bitch");
                       });

Pebble.addEventListener("appmessage",
	function(e) {
		console.log(e);
		accel_data = e.payload.value1;
        console.log(accel_data);
	
		//senddirection(direction);


		}
	);


















   