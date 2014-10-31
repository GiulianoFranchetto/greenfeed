var app = angular.module("signinPage",["menuBar"]);

app.directive('signinPage', function(){
	return {
		restricted:"E",
		templateUrl:"template/signinPage.html",
		controller:"signPageController",
		controllerAs:"signPageCtrl"
	};
});

app.controller("signPageController", ["$scope", function ($scope){
	this.sign = function(u,p){
		var resultAuth = this.checkAuth(u,p);
		
		if(resultAuth.isOK === true)
			$scope.$emit('authOK',resultAuth);
	};

	this.checkAuth = function(u,p){
		return {isOK : true, firstname : "giuliano", lastname : "franchetto"};
	}

}]);