var app = angular.module("screen",/*["screenAlert","screenMap","screenHistory"]*/[]);

app.directive('screen', function(){
	return {
		restricted:"E",
		templateUrl:"template/screen.html",
		controller:"screenController",
		controllerAs:"screenCtrl"
	};
});

app.controller("screenController", function(){


});