/**
 * 监听路径：'/map'
 */

var express = require('express');
var router = express.Router();

router.get( '/config', function(req, res) {
    res.render('map/config/config');
});

router.get( '/config/sign', function(req, res) {
    res.render('map/config/sign');
});

router.get( '/config/mo', function(req, res) {
    res.render('map/config/mo');
});

router.get( '/config/marquee', function(req, res) {
    res.render('map/config/marquee');
});

router.get( '/data', function(req, res) {
    res.render('map/data/data');
});

router.get( '/data/event', function(req, res) {
    res.render('map/data/data_event');
});

router.get( '/help', function(req, res) {
    res.render('map/help/help');
});

router.get( '/update', function(req, res) {
    res.render('map/update');
});

module.exports = router;
