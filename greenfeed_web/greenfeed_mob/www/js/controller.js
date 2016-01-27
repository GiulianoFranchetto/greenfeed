/* global angular, document, window */
'use strict';

angular.module('greenfeed.controllers', [])

.factory('profile', function(){
 	var profile = {};
    return {
		getProfile: function() {
			return profile;
		},
        setProfile: function(s) { 
			profile = s; 
		}
    };
})

.controller('LoginCtrl', function($scope, $timeout, $stateParams, ionicMaterialInk, profile) {
    ionicMaterialInk.displayEffect();

    var self = this;
	this.p = {};
	this.auth = function() {
		profile.setProfile(self.p);
		console.log(profile.getProfile().username);
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
