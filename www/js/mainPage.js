var app = angular.module("mainPage",["menuBar","booking"]);

app.directive('mainPage', ["$scope", function(){
	return {
		restricted:"E",
		templateUrl:"template/mainPage.html",
		controller:"mainPageController",
		controllerAs:"mainPageCtrl"
	};
}]);

app.controller("mainPageController", function(){


});