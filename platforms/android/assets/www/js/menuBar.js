var app = angular.module("menuBar",[]);

app.directive('menuBar', function(){
	return {
		restricted:"E",
		templateUrl:"template/menuBar.html",
		controller:"menuBarController",
		controllerAs:"menuBarCtrl"
	};
});

app.controller("menuBarController", ["$scope",function ($scope){
	this.name="";
	this.surname = "";

	function toTitleCase(str){
	    return str.replace(/\w\S*/g, function(txt){return txt.charAt(0).toUpperCase() + txt.substr(1).toLowerCase();});
	}

	function setName(n,s){
		this.name = n;
		this.surname = s;
		var div = document.getElementById('placeNameHere');
		div.innerHTML = n.toUpperCase() + "<br>"+ toTitleCase(s);
	}

	$scope.$on('authOK', function(event,data){
		$scope.page=1;
		setName(data.lastname, data.firstname);
	});
}]);