



var canvas, ctx;


//randomly set a BG pattern
var min = 0;//INCLUSIVE
var max = 2;//EXCLUSIVE
var BG = 0;//Math.floor(Math.random() * (max - min) + min);
console.log('RandomSeed = ', BG);


var fillColor = 'white';
//hoehe und breite des browser fensters
var height;
var width;
//console.log("height = " + height + "   ||   " + "width = " + width);
var blackToGreen;
//transparenter hintergrund
var color = "#ffffff";
//alle nullen und einsen
var quads = [];
//die Geschwindigkeit der 1/0im Hintergrund(Die Mausposition(horizontal))
var speed = 0;





//initialisiert die Seite und setzt die groesse des Canvas
function init() 
{
    canvas = document.getElementById("HeaderBackGround");

    height = window.outerHeight;
    width = window.outerWidth;

    
    canvas.width = width;
    canvas.height = height;


    ctx = canvas.getContext('2d');
    

    quads = [];


    //die Quads spawnen
    createQuads();
    //den Canvas zeichnen
    drawCanvas();
    
}

//die nullen und einsen spawnen
//alle Nullen/Einsen in diese x-Reihe
function createQuads()
{
    var quad, y;

    if (width > height)
    {
        for (y = 0; y < width; y++)
        {
            quad = new Quad(height, width);
            quads.push(quad);
        }
    }

    else
    {
        for (y = 0; y < height; y++)
        {

            quad = new Quad(height, width);
            quads.push(quad);
        }
    }
}


//zeichnet den canvas neu
function drawCanvas() {
    
    //canvas refresh
    //DEN HINTERGRUND ZEICHNEN
    //den background mit einer color transition(Circle) zeichnen
    if (BG === 0) {
        blackToGreen = ctx.createRadialGradient(width / 2, height / 2, 5,
                                                width / 2, height / 2, width / 2);
        blackToGreen.addColorStop(0, 'green');
        blackToGreen.addColorStop(1, 'black');
    }
    else if (BG === 1) {
        blackToGreen = ctx.createLinearGradient(canvas.width, 0, canvas.width, canvas.height)
        blackToGreen.addColorStop(0, "darkgreen");
        blackToGreen.addColorStop(1, "black");
    }

    ctx.fillStyle = blackToGreen;
    
    ctx.fillRect(0, 0, width, height);
    
    //Die Geschwindigkeit mit der horizontalen-mausposition  bestimmen
    
    
    //zeichnet die nullen und einsen die aus dem Kreis 'fliegen'
    ctx.translate(width / 2, height / 2);
    for (var q = 0; q < quads.length; q++) {
        //die Position des Quads bestimmen
        quads[q].Update(speed, BG);
        //das Quad zeichnen
        quads[q].Show(ctx);     
    } ctx.translate(-width / 2, -height / 2);
   
    setTimeout(drawCanvas, 1000 / 60);
}

//wenn das Fenster geladen wurde
window.onload = init();


//wenn die groesse des fensters sich aendert den canvas neu initialisieren
window.onresize = function (event) { init(); };

//Die Mausposition bestimmen UND damit die Geschwindigkeit der 0/1 setzen//////////////////////////////
document.onmousemove = getMouseXY;

var tempX = 0;
var tempY = 0;

function getMouseXY(e)
{
    speed = e.pageX;
    speed = speed - width / 2;
    if (speed < 0)
    {
        speed *= -1;
    }

    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
