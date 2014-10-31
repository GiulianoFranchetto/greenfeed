var app = angular.module("map",[]);

app.directive('map', function(){
	return {
		restricted:"E",
		templateUrl:"template/map.html",
		controller:"mapController",
		controllerAs:"mapCtrl"
	};
});

app.controller("mapController", function(){


});