var canvas = document.getElementById("canvas");
var i;
var countdown = 6;
var xPos = [];
var yPos = [];
var rad = [];

var start = document.getElementById("c");

var setup = function setup(e) {
    i = setInterval(background1,20);
};

var background1 = function background1(e) {
    while(canvas.childElementCount != 0){
	canvas.removeChild(canvas.children[0]);
    }
    var endtube = document.createElementNS("http://www.w3.org/2000/svg", "circle");
    endtube.setAttribute("cx", 400);
    endtube.setAttribute("cy", 400);
    endtube.setAttribute("r", 400);
    endtube.setAttribute("fill", "white");
    endtube.setAttribute("stroke", "black");
    canvas.appendChild(endtube);
    var statube = document.createElementNS("http://www.w3.org/2000/svg", "circle");
    statube.setAttribute("cx", 400);
    statube.setAttribute("cy", 400);
    statube.setAttribute("r", 10);
    statube.setAttribute("fill", "white");
    statube.setAttribute("stroke", "black");
    canvas.appendChild(statube);
    var count = document.createElementNS("http://www.w3.org/2000/svg", "text");
    count.setAttribute("x", 396);
    count.setAttribute("y", 500);
    count.setAttribute("fill", "black");
    count.textContent = countdown;
    canvas.appendChild(count);
    countdown--;
    console.log(countdown);
    if(countdown < 1){
	clearInterval(i);
	console.log("hi");
	i = setInterval(update,17);
    }
};

var update = function update(e){
    background2();
    drawObs();
    drawCharacter();
    checkDeath();
};

var background2 = function background2(e){
    while(canvas.childElementCount != 0){
	xPos.push(canvas.children[0].getAttribute("cx"));
	yPos.push(canvas.children[0].getAttribute("cy"));
	rad.push(canvas.children[0].getAttribute("cx"));
	canvas.removeChild(canvas.children[0]);
    }
    var endtube = document.createElementNS("http://www.w3.org/2000/svg", "circle");
    endtube.setAttribute("cx", 400);
    endtube.setAttribute("cy", 400);
    endtube.setAttribute("r", 400);
    endtube.setAttribute("fill", "white");
    endtube.setAttribute("stroke", "black");
    canvas.appendChild(endtube);
    var statube = document.createElementNS("http://www.w3.org/2000/svg", "circle");
    statube.setAttribute("cx", 400);
    statube.setAttribute("cy", 400);
    statube.setAttribute("r", 10);
    statube.setAttribute("fill", "white");
    statube.setAttribute("stroke", "black");
    canvas.appendChild(statube);
};
/*
var pulse = function pulse(e) {
    if(canvas.childElementCount != 0){
	canvas.removeChild(canvas.children[0]);
	clearInterval(i);
    }
    var diff = -1;
    var rad = 0;
    var col = "#ff0000";
    var cir = function (e) {
	if(canvas.childElementCount != 0){
	    canvas.removeChild(canvas.children[0]);
	}
	var c1 = document.createElementNS("http://www.w3.org/2000/svg", "circle");
	if(rad == 250 || rad == 0){
	    diff = diff * -1;
	    if(col == "#ff0000"){
		col = "#00ff00";
	    }else if(col == "#00ff00"){
		col = "#0000ff";
	    }else{
		col = "#ff0000";
	    }
	}
	rad = rad + diff;
	c1.setAttribute("cx", 250);
	c1.setAttribute("cy", 250);
	c1.setAttribute("r", rad);
	c1.setAttribute("fill", col);
	c1.setAttribute("stroke", "black");
	canvas.appendChild(c1);
    }
    i = setInterval(cir,25);
}

var bounce = function bounce(e) {
    if(canvas.childElementCount != 0){
	canvas.removeChild(canvas.children[0]);
	clearInterval(i);
    }
    var posx = Math.floor(Math.random() * 300) + 100;
    var posy = Math.floor(Math.random() * 300) + 100;
    var xdiff = 1;    
    var ydiff = 0;
    var mod = .05;
    var move = function (e) {
	if(canvas.childElementCount != 0){
	    canvas.removeChild(canvas.children[0]);
	}
	posx += xdiff;
	posy += ydiff;
	if(posx < 20 || posx > 480){
	    posx -= xdiff;
	    xdiff *= -1;
	}
	if(posy > 480){
	    posy -= ydiff;
	    ydiff *= -1;
	}
	ydiff += mod;
	var c2 = document.createElementNS("http://www.w3.org/2000/svg", "circle");
	c2.setAttribute("cx", posx);
	c2.setAttribute("cy", posy);
	c2.setAttribute("r", 20);
	c2.setAttribute("fill", "#ff0000");
	c2.setAttribute("stroke", "black");
	canvas.appendChild(c2);
    };
    i = setInterval(move,25);
};

var cease = function cease(e) {
    clearInterval(i);
};
*/
start.addEventListener("click",setup);
