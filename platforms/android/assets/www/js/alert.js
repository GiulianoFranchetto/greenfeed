var app = angular.module("alert",[]);

app.directive('alert', function(){
	return {
		restricted:"E",
		templateUrl:"template/alert.html",
		controller:"alertController",
		controllerAs:"alertCtrl"
	};
});

app.controller("alertController", function(){


});