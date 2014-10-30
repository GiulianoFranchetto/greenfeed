var app = angular.module("signinPage",[]);

app.directive('signinPage', function(){
	return {
		restricted:"E",
		templateUrl:"template/signinPage.html",
		controller:"signPageController",
		controllerAs:"signPageCtrl"
	};
});

app.controller("signPageController", ["$scope", function ($scope){
	this.sign = function(){
		$scope.page=1;
	};

}]);