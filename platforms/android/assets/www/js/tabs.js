var app = angular.module("tabs",["history","alert","map"]);

app.directive('tabs', function(){
	return {
		restricted:"E",
		templateUrl:"template/tabs.html",
		controller:"tabsController",
		controllerAs:"tabsCtrl"
	};
});

app.controller("tabsController", function(){


});