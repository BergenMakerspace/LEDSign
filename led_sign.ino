// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy  replace,
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8,3,2, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE+
  NEO_TILE_TOP+NEO_TILE_LEFT+NEO_TILE_COLUMNS+NEO_TILE_ZIGZAG,
  NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  matrix.setTextSize(2);
}

int x    = matrix.width(); //matrix dimensions
int y = matrix.height();//matrix dimensions
int pass = 0;
int i =0;   // counter for graphics
int j = 0 ; //internal graphics counter
int k = 0 ; //internal graphics counter
int l = 0; // internal graphics counter

void loop() {
  
   if (i <= y) {             //rectangle graphic display
  	matrix.drawRect(0,0,j+x-y,j, colors[pass]); 
		delay (100); 
  		matrix.show();
  		matrix.drawRect(0,0,i+x-y,i, 0);
  		j++;
  		i++;
		}

else if (i> y && i<=2*y+1){     
	
	matrix.drawRect(0,y-1,x-k,-y+1+k, colors[pass]); //rectangle graphic display
		delay (100); 
  		matrix.show();
  		matrix.drawRect(0,y-1,x-k,-y+1+k, 0);
  		k++;
  		i++;
}		

 
else if (i>2*y+1 && i<=2*y+4+x){       //circle graphic display
  matrix.fillCircle(0,y,i-2*y,colors[pass]);
	delay (100); 
  		matrix.show();
  		matrix.drawCircle(x/2,0,i-2*y, 0);
  		i++;	
		}
		
else if (i>2*y+4+x && i<=2*y+4+x+x/2){       //sweep clean graphic
		matrix.drawRect(x/2-l,0,2*l,y,0); 
		delay (100); 
  		matrix.show();
  		l++;
  		i++;	
		}

 else {
 	
  matrix.fillScreen(0);  // scroll text 
  matrix.setCursor(x, 0);
  matrix.print(F("Bergen Makerspace"));
	 if(--x < -204) {
    	x = matrix.width();
    	if(++pass >= 3) pass = 0;
    	i=0;
    	j=0;
    	k=0;
    	l=0;
    	
    	matrix.setTextColor(colors[pass]);
   		 }
  matrix.show();
  delay(100);

	}
}