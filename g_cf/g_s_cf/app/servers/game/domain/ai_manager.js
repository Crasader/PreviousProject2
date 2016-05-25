'use strict';

function getTurrentLevel(room_id) {
  var random = parseInt(Math.random()*100);
  if(room_id === 1){
    if(random < 40) {
      return 1+parseInt(Math.random()*9);
    }else if(random < 90){
      return 10+parseInt(Math.random()*4)*5;
    }else {
      return 30+parseInt(Math.random()*7)*10;
    }
  }else if(room_id === 2){
    if(random < 50) {
      return 30+parseInt(Math.random()*7)*10;
    }else if(random < 90){
      return 100+parseInt(Math.random()*4)*50;
    }else {
      return 300+parseInt(Math.random()*4)*50;
    }
  }else if(room_id === 3){
    if(random < 50) {
      return 100+parseInt(Math.random()*4)*50;
    }else if(random < 90){
      return 300+parseInt(Math.random()*4)*50;
    }else {
      return 500+parseInt(Math.random()*5)*100;
    }
  }else if(room_id === 4){
    if(random < 50) {
      return 300+parseInt(Math.random()*4)*50;
    }else {
      return 500+parseInt(Math.random()*5)*100;
    }
  }
  return 1;
}

exports.getTurrentLevel = getTurrentLevel;


function getCoins(turrent_level){
  var random = parseInt(Math.random()*100);
  if(turrent_level <= 10) {
    if(random < 70) {
      return 1000+parseInt(Math.random()*50000);
    }else if(random < 90) {
      return 50000+parseInt(Math.random()*50000);
    }else {
      return 100000+parseInt(Math.random()*50000);
    }
  }else if(turrent_level <= 30) {
    if(random < 70) {
      return 1000+parseInt(Math.random()*50000);
    }else if(random < 90) {
      return 50000+parseInt(Math.random()*50000);
    }else {
      return 100000+parseInt(Math.random()*50000);
    }
  }else if(turrent_level <= 100) {
    if(random < 70) {
      return 3000+parseInt(Math.random()*50000);
    }else if(random < 90) {
      return 50000+parseInt(Math.random()*100000);
    }else {
      return 150000+parseInt(Math.random()*150000);
    }
  }else if(turrent_level <= 300) {
    if(random < 70) {
      return 3000+parseInt(Math.random()*150000);
    }else if(random < 90) {
      return 150000+parseInt(Math.random()*150000);
    }else {
      return 300000+parseInt(Math.random()*1000000);
    }
  }else if(turrent_level <= 500) {
    if(random < 70) {
      return 5000+parseInt(Math.random()*50000);
    }else if(random < 90) {
      return 250000+parseInt(Math.random()*150000);
    }else {
      return 100000+parseInt(Math.random()*5000000);
    }
  }else  {
    if(random < 70) {
      return 10000+parseInt(Math.random()*5000000);
    }else if(random < 90) {
      return 10000000+parseInt(Math.random()*40000000);
    }else {
      return 40000000+parseInt(Math.random()*50000000);
    }
  }
}

exports.getCoins = getCoins;

function getDiamonds(turrent_level){
  var random = parseInt(Math.random()*100);
  if(turrent_level <= 10) {
    if(random < 70) {
      return 0+parseInt(Math.random()*5);
    }else if(random < 90) {
      return 5+parseInt(Math.random()*5);
    }else {
      return 10+parseInt(Math.random()*20);
    }
  }else if(turrent_level <= 30) {
    if(random < 70) {
      return 0+parseInt(Math.random()*10);
    }else if(random < 90) {
      return 10+parseInt(Math.random()*20);
    }else {
      return 30+parseInt(Math.random()*20);
    }
  }else if(turrent_level <= 100) {
    if(random < 70) {
      return 5+parseInt(Math.random()*40);
    }else if(random < 90) {
      return 40+parseInt(Math.random()*100);
    }else {
      return 100+parseInt(Math.random()*400);
    }
  }else if(turrent_level <= 300) {
    if(random < 70) {
      return 10+parseInt(Math.random()*40);
    }else if(random < 90) {
      return 40+parseInt(Math.random()*800);
    }else {
      return 800+parseInt(Math.random()*2000);
    }
  }else if(turrent_level <= 500) {
    if(random < 70) {
      return 20+parseInt(Math.random()*80);
    }else if(random < 90) {
      return 100+parseInt(Math.random()*2000);
    }else {
      return 2000+parseInt(Math.random()*3000);
    }
  }else  {
    if(random < 70) {
      return 40+parseInt(Math.random()*800);
    }else if(random < 90) {
      return 1000+parseInt(Math.random()*4000);
    }else {
      return 5000+parseInt(Math.random()*100000);
    }
  }
}

exports.getDiamonds = getDiamonds;

function getExps(turrent_level){
  return parseInt(Math.random()*100)*turrent_level;
}

exports.getExps = getExps;

function getCheskLevel( turrent_level ) {
  var random = parseInt(Math.random()*100);
  if(turrent_level <= 10) {
    return 0;
  }else if(turrent_level <= 30) {
    if(random < 95) {
      return 0;
    }else {
      return 1;
    }
  }else if(turrent_level <= 100) {
    if(random < 92) {
      return 0;
    }else if(random < 97) {
      return 1;
    }else if(random < 99){
      return 2;
    }else {
      return 3;
    }
  }else if(turrent_level <= 300) {
    if(random < 80) {
      return 0;
    }else if(random < 90) {
      return 1;
    }else if(random < 95){
      return 2;
    }else {
      return 3;
    }
  }else if(turrent_level <= 500) {
    if(random < 80) {
      return 0;
    }else if(random < 90) {
      return 1;
    }else if(random < 95){
      return 2;
    }else {
      return 3;
    }
  }else  {
    if(random < 80) {
      return 0;
    }else if(random < 85) {
      return 1;
    }else if(random < 90){
      return 2;
    }else {
      return 3;
    }
  }
}

exports.getCheskLevel = getCheskLevel;
