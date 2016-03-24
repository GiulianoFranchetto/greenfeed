"use strict";

/* Server creation */
var express    = require('express');
var app        = express();                 // define our app using express
var bodyParser = require('body-parser');
var authorization = require('basic-auth');

// configure app to use bodyParser()
// this will let us get the data from a POST
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

/* Database connection */
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/greenfeed',function(err) {
    if (err){
      console.log("Couldn't connect to the database.");
      console.log(err);
      process.exit();
    }
});

/* Model creation */
var UserSchema = new mongoose.Schema({
    lastname: String,
    firstname: String,
    email: String,
    password: String,
    created_at: { type: Date, default: Date.now }
});

var AbriSchema = new mongoose.Schema({
    v_bat: Number,
    p_bat: Number,
    mppt_o: Number,
    time: Number
});

var User = mongoose.model('user', UserSchema, 'user');
var Abri = mongoose.model('abri', AbriSchema, 'abri');

/* Get all entries for "Abri" */
app.get('/abri', function(req, res){
    Abri.find().sort({$natural: -1}).limit(100).exec(function(err, values){
        if (err) {
            res.sendStatus(500);
        }
        res.status(200).send(values);
    });
});

app.get('/abri/last', function(req, res){
	Abri.find().sort({$natural: -1}).limit(1).exec(function(err, values){
        if (err) {
            res.sendStatus(500);
        }
        res.status(200).send(values[0]);
    });
});

app.get('/user', function(req, res){
    var user = authorization(req);
    console.log("Connection of " + user.name + " (" + user.pass + ")");
    User.find({'email': user.name, 'password': user.pass }, function(err, values){
        if(err){
            return res.status(500).send('{"status": "KO"}');
        }
        if(!values.length) {
            return res.status(403).send('{"status": "KO"}');
        }
        return res.status(200).send('{"status": "OK"}');
    });
});

/* Our 404 */
app.use(function(err, req, res, next) {
    res.sendStatus(404);
});

app.listen(1201);
