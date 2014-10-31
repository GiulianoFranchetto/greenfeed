var app = angular.module("booking",[]);

app.directive('booking', function(){
	return {
		restricted:"E",
		templateUrl:"template/booking.html",
		controller:"bookingController",
		controllerAs:"bookingCtrl"
	};
});

app.controller("bookingController", function(){


});