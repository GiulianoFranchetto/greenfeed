"use strict";

/* Server creation */
var express    = require('express');
var app        = express();                 // define our app using express
var bodyParser = require('body-parser');

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
    Created_at: { type: Date, default: Date.now }
});

var AbriSchema = new mongoose.Schema({
    v_bat: Number,
    p_bat: Number,
    mppt_o: Number
});

var User = mongoose.model('user', UserSchema);
var Abri = mongoose.model('abri', AbriSchema, 'abri');

/* Get all entries for "Abri" */
app.get('/abri', function(req, res){
    Abri.find().limit(100).exec(function(err, values){
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

/* Our 404 */
app.use(function(err, req, res, next) {
    res.sendStatus(404);
});

app.listen(1201);