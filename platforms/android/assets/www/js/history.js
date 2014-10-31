var app = angular.module("history",[]);

app.directive('history', function(){
	return {
		restricted:"E",
		templateUrl:"template/history.html",
		controller:"historyController",
		controllerAs:"historyCtrl"
	};
});

app.controller("historyController", function(){


});