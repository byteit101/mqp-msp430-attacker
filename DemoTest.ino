// Do not remove the include below
#include "mqp.h"

#define maxr(x) ((x) > 0xF? 0xF : (x))
Adafruit_MCP4725 dac;

uint8_t bufa[20] = { 
0x03,0x43,0x03,0x43,0x03,0x43,0x03,0x43,0x03,0x43, // nop
 0x5e, 0x43, // mov.b #1, r14
0x7f, 0x40, 0x2b, 0x00, // mov.b #43, r15
 0xb0, 0x12, 0x50, 0x47, // call 0x4750
//0, 1, 0, 2, 0, 2, 2, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1 
};//Arduino: 0, 0, 0, 0, 0, -1, 1, 0, 1, 0, 0, 0, 0, 0, -1, 1, -1, 1, 0, 0};

uint8_t bufb[20];
int8_t diff[20] = 
//  2  3   4   5  6  7  8   9  10
{0, 2, 0,  3,  0, 3, 0, 3,  0, 5, 
19, 5, 11, 11, 3, 0, 7, 4, 12, 16}; 
//{0, 2, 0, 2, 0, 2, 0, 2,  0, 5, 
//18, 6, 11, 9, 1, 0, 7, 4, 12, 16}; 


//ParallaxLCD lcd(2,2,16);
//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	  Serial.println("Hello!");
	  Serial.println(RED_LED);
	  dac.begin(0x62);

	  Serial.println("Generating a triangle wave");
	  pinMode(48, OUTPUT);

	//  dac.setVoltage(2048, false);
//	  delay(10000);

	  /*lcd.setup();
	delay(1000);
	lcd.backLightOn();
	lcd.empty();
	delay(1000);
	lcd.backLightOff();*/
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	   uint32_t counter;
	   int32_t in = 1;
	   int32_t tmp;
	   digitalWrite(48, HIGH);
	    // Run through the full 12-bit scale for a triangle wave
	    for (counter = 0; counter < 20; counter++)
	    {
	    	tmp = (int)bufa[counter];
	    	tmp = (((tmp << 4) | (tmp >> 4)) + (int)diff[counter] + 8);
	    //	Serial.print(tmp);
	   // 	Serial.print(" ");
	      dac.setVoltage(tmp, false);
	      delay(1);
	      bufb[counter] = (analogRead(A0) >> 4);
	      in = in && (bufa[counter] == bufb[counter]);
	    }
	    Serial.println("");
		   digitalWrite(48, LOW);
		   delay(3);
	    if (in)
	    {
	    	//Serial.println("Perfect Match!");
	    }
	    for (counter = 0; counter < 20; counter++)
	    {
	    	Serial.print((int)bufa[counter]-(int)bufb[counter]);
	    	Serial.print(" ");
	    }
	    /*Serial.println("");
	    for (counter = 0; counter < 20; counter++)
	    {
	    	Serial.print(bufb[counter], HEX);
	    	Serial.print(" ");
	    }*/
	    /*Serial.println("");
	    for (counter = 4095; counter > 0; counter--)
	    {
	      dac.setVoltage(counter, false);
	      //delay(20);
	    }*/

}
