/* global angular, document, window */
'use strict';
var base_url = 'http://195.83.139.38:1201';

var module = angular.module('greenfeed.controllers', ['ngResource'])

.factory('profile', ['$resource', function($resource){
 	var profile = {};
    return {
		getResource: function() {
			return $resource( base_url + '/user/:id/:pwd', 
							{ id : '@id', pwd : '@pwd' }, 
							{ 'auth' : { method:'GET' } }
			);
		},
		getProfile: function() {
			return profile;
		},
        setProfile: function(s) { 
			profile = s; 
		}
    };
}])

.controller('LoginCtrl', function($scope, $timeout, $stateParams, ionicMaterialInk, profile) {
    ionicMaterialInk.displayEffect();

    var self = this;
	this.p = {};
	this.auth = function() {
		profile.getResource().auth(self.p.email, self.p.pwd)
			.$promise.then(function(data) {
				profile.setProfile(self.p);
				console.log(profile.getProfile().username);
			}, function(error){
				/*Error treatment*/
			});
	}
})

.controller('ActivityCtrl', function($scope, $stateParams, $timeout, ionicMaterialMotion, ionicMaterialInk) {
    $scope.$parent.showHeader();
    $scope.$parent.clearFabs();
    $scope.isExpanded = true;
    $scope.$parent.setExpanded(true);
    $scope.$parent.setHeaderFab('right');

    $timeout(function() {
        ionicMaterialMotion.fadeSlideIn({
            selector: '.animate-fade-slide-in .item'
        });
    }, 200);

    // Activate ink for controller
    ionicMaterialInk.displayEffect();
})
