var app = angular.module("planning",[]);

app.directive('planning', function(){
	return {
		restricted:"E",
		templateUrl:"template/planning.html",
		controller:"planningController",
		controllerAs:"planningCtrl"
	};
});

app.controller("planningController", function(){


});