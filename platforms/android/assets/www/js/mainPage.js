var app = angular.module("mainPage",["booking","tabs","screen"]);

app.directive('mainPage', function(){
	return {
		restricted:"E",
		templateUrl:"template/mainPage.html",
		controller:"mainPageController",
		controllerAs:"mainPageCtrl"
	};
});

app.controller("mainPageController", function(){


});