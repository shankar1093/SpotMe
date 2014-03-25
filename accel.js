simply.text({
	title:'Accel Demo',
	body:'Press up to stream',

},true);

var onAccelData = function(e){
	simply.body('data: ' + JSON.stringify(e.accel));
};

simply.on('singleClick', 'up', function(e){
	simply.on('accelData', onAccelData);
});

simply.on('singleClick', 'select', function(e){
	if(simply.accelConfig().subscribe){
	return;
	}
})