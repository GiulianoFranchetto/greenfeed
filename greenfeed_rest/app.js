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
    uid: String,
    created_at: { type: Date, default: Date.now }
});

var AbriSchema = new mongoose.Schema({
    v_bat: Number,
    p_bat: Number,
    mppt_o: Number,
    time: Number
});

var BookingSchema = new mongoose.Schema({
    starting_date: Number,
    ending_date: Number,
    user_id: String,
    bike_id: Number
});

var User = mongoose.model('user', UserSchema, 'user');
var Abri = mongoose.model('abri', AbriSchema, 'abri');
var Booking = mongoose.model('booking', BookingSchema, 'booking');

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
        console.log("Sending :");
        console.log(JSON.stringify(values[0]));
        return res.status(200).send(values[0]);
    });
});

app.post('/booking', function(req, res){
    // first we check that a bike is available at this time
    console.log("Checking if a new booking can be created:");
    console.log(JSON.stringify(req.body));
    Booking.find({"starting_date" : {"$lt": req.body.ending_date}, "ending_date": {"$gt": req.body.starting_date}})
        .exec(function(err, values){
        if (err) {
            res.sendStatus(500);
        }
        console.log("These booking have been found on the corresponding period" + JSON.stringify(values));

        var available_bikes = [1, 2, 3];
        values.forEach(function(line){
            var i = available_bikes.indexOf(line.bike_id);
            if(i !== -1) {
                available_bikes.splice(i, 1);
            }
        });
        console.log("The following bikes are available: " + JSON.stringify(available_bikes));
        if(available_bikes.length === 0){
            return res.status(500).send('{"status": "KO"}');
        }
        var chosen_bike = available_bikes[0];
        var new_book = new Booking({
            starting_date: req.body.starting_date,
            ending_date: req.body.ending_date,
            user_id: req.body.user_id,
            bike_id: chosen_bike
        });
        new_book.save(function (err, new_book) {
            if (err) {
                console.log(err);
                return res.status(500).send('{"status": "KO"}');
            } else {
                Booking.find({"starting_date" : {"$gte": new Date().getTime()}}).exec(function(err, values){
                    if (err) {
                        console.log(err);
                        res.sendStatus(500);
                    }
                    res.status(200).send(values);
                });
            }
        });
    });
});

app.get('/booking', function(req, res){
    Booking.find({"starting_date" : {"$gte": new Date().getTime()}}).exec(function(err, values){
        if (err) {
            res.sendStatus(500);
        }
        res.status(200).send(values);
    });
});

process.on('uncaughtException', function (error) {
    console.log(error.stack);
});

/* Our 404 */
app.use(function(err, req, res, next) {
    res.sendStatus(404);
});

app.listen(1201);