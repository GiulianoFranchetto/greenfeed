"use strict";

/* Server creation */
var express = require('express');
var app        = express();                 // define our app using express
var bodyParser = require('body-parser');

// configure app to use bodyParser()
// this will let us get the data from a POST
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

/* Our 404 */
app.use(function(req, res, next) {
    res.sendStatus(404);
});

/* Database connection */
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/greenfeed');

/* Model creation */
var UserSchema = new mongoose.Schema({
    lastname: String,
    firstname: String,
    email: String,
    password: String,
    Created_at: { type: Date, default: Date.now }
});

var AbriSchema = new mongoose.Schema({
    v_bat: Number,
    p_bat: Number,
    mppt_o: Number
});

var User = mongoose.model('User', UserSchema);
var Abri = mongoose.model('Abri', AbriSchema);

/* Get all entries for "Abri" */
app.get('/abri', function(req, res){
    Abri.find(function (err, values) {
        if (err) {
            return res.sendStatus(500);
        }
        console.log(values);
        res.status(200).send(values);
    });
});

app.get('/user', function(req, res){
    User.find({email: req.get.email, password: req.get.password }, function(err, values){
        if(err){
            return res.sendStatus(500);
        }
        if(values.length === 0) {
            return res.sendStatus(403);
        }
        return res.sendStatus(200);
    });
});

app.listen(1201);

