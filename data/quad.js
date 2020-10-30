


class Quad
{
    constructor(height, width, q)
    {
        //grenze ob es eine eins oder null wird
        this.border = 0.6;
        //ob es eine eins oder null wird
        this.tmp = Math.random();

        // Gibt eine Zufallszahl zwischen min (inklusive) und max (inklusive) zurück 
        this.getRandomInt = function getRandomInt(min, max)
        {
            min = Math.ceil(min);
            max = Math.floor(max);
            return Math.floor(Math.random() * (max - min + 1)) + min;
        };
        //remapping eines Wertes auf einen anderen Wertebereich
        this.Map = function Map(value, low1, high1, low2, high2)
        {
            return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
        };
        // Gibt eine Zufallszahl zwischen min (inklusive) und max (exklusive) zurück
        this.getRandomArbitrary = function getRandomArbitrary(min, max)
        {
            return Math.random() * (max - min) + min;
        };

        this.x = this.getRandomInt(-width + (width / 1.5), width - (width / 1.5));
        this.y = this.getRandomInt(-height + (height / 1.5), height - (height / 1.5));
        this.z = this.getRandomArbitrary(0, width);

        this.r = this.Map(this.z, width, 0, 1, 0);

        this.height = height;
        this.width = width;

        //create a 0(ZERO)
        if (this.tmp > this.border)
        {
            this.h = 20;
            this.w = 10;

            this.fillColor = "green";
        }
        else if (this.tmp <= this.border && this.tmp > 0.3)
        {
            //CREATE A GAP BETWEEN THE NUMBERS
        }
        //create a 1(ONE)
        else
        {
            this.h = 20;
            this.w = 3;

            this.fillColor = "green";
        }



        //Die NULL oder EINS zeichnen
        this.Show = function Show(ctx) {

            //farbe des vierecks anpassen
            ctx.fillStyle = this.fillColor;

            this.sx = this.Map(this.x / this.z, 0, 1, 0, width);
            this.sy = this.Map(this.y / this.z, 0, 1, 0, height);

            //Nullen/Einsen zeichnen
            //0 --> ZERO
            if (this.tmp > this.border) {
                //rahmen der null
                ctx.fillRect(this.sx, this.sy,
                    this.w * this.r, this.h * this.r);
                //inneres der null
                ctx.fillStyle = "black";
                ctx.fillRect(this.sx + (3 * this.r), this.sy + (2 * this.r),
                            (this.w - 6) * this.r, (this.h - 4) * this.r);
                //outline
                ctx.strokeRect(this.sx, this.sy, (this.w) * this.r, (this.h) * this.r);
            }
            //1 --> ONE
            else {
                ctx.fillRect(this.sx, this.sy, (this.w) * this.r * 2, (this.h) * this.r);
                //outline
                ctx.strokeRect(this.sx, this.sy, (this.w) * this.r * 2, (this.h) * this.r);
            }


        };


        //Die Position des Quads Updaten
        this.Update = function Update(speed, BG)
        {
            //MATRIX EFFECT
            if (BG === 0)
            {
                this.z -= speed / 100;
                if (this.z < 1) {
                    //console.log('z', this.z, 'q = ', q);
                    this.x = this.getRandomInt(-width + (width / 1.5), width - (width / 1.5));
                    this.y = this.getRandomInt(-height + (height / 1.5), height - (height / 1.5));
                    this.z = this.getRandomArbitrary(0, width);
                }
            }
            //BINARY WARP
            if (BG === 1)
            {
                this.y += 1 * speed / 150;
                //wegen des verschiebens des Hintergrunds
                if(this.y > height){
                    this.y = this.getRandomArbitrary(-height * 1.5, -height);
                }
            }
        };


        this.strokeColor = 'white';      

    }
}