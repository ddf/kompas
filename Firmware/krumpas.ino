/*
 * Alternate firmware for stziopa/bastl-instruments Kompas
 * licensed under CC-BY-SA by Stefano Manconi 02-09-2019
 * and Damien Quartz 17-10-2026.
 */

/*
 * KRUMPAS
 *
 *this tool is 
 *the outcome 
 *of wishing kompas
 *could be just
 *a little bit
 *more predictable
 *while retaining
 *the feeling
 *of navigating
 *a shifting
 *landscape
 *
 */

//NAVIGATION BEGINS:......
#include <EEPROM.h>
#include "hardware.h"
#include "definitions.h"
#include "variables.h"
#include "data.h"

void setup() 
{
  Serial.begin(9600);
  bootMode = false;
  //check for the first startup
  if(!isEEPROMvalid())
  {
    formatFactory();
    delay(100);
  }
   
  loadPreset();

  //set pins PB7, PB6, PB3 (longitude), PB2 (altitude), PB1 (latitude) as outputs, PB0 as input
  DDRB = B11001110;
  PORTB|B00000001;
  //PB0 internal pullup resistor
  PINB|=B00000001;
    
  //set pins PD7, PD6, PD5, PD4, PD3, PD2 as outputs, leaves PD1 and PD0 as default (ftdi)
  DDRD = DDRD | B11111100;
  PORTD|B00000000;
  //PD7 High
  PIND|=B10000000;
  
  pinMode(clock_led, OUTPUT);
  pinMode(reset_led, OUTPUT);
  
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  randomSeed(analogRead(A5));

  //BOOTMODE (close jumper in between PB0 and GND before startup)
  if(!bootPin) 
  {
    bootMode = true;
    loadPreset();
    
    pot0 = analogRead(A3);
    pot1 = analogRead(A4);
    pot2 = analogRead(A5);
    prevPot0 = pot0;
    prevPot1 = pot1;
    prevPot2 = pot2;
    
  } 
  else 
  {
    bootMode = false;
    loadPreset();
  }

  while(bootMode) 
  {
    pot0 = analogRead(A3);
    pot1 = analogRead(A4);
    pot2 = analogRead(A5);

    if(pot0 > (prevPot0 + 9) || pot0 < (prevPot0 - 9)) 
    {
      prevPot0 = pot0;
      EEPROM.update(addr, 0x0);
    }
    if(pot1 > (prevPot1 + 9) || pot1 < (prevPot1 - 9)) 
    {
      prevPot1 = pot1;
      EEPROM.update(addr, 0x1);
    }
    if(pot2 > (prevPot2 + 9) || pot2 < (prevPot2 - 9)) 
    {
      prevPot2 = pot2;
      EEPROM.update(addr, 0x2);
    }

    loadPreset();
    switch(trigPreset) 
    {
      case 0:
        PORTB=B00000001;
        PINB|=B00001000;
        break;
      case 1:
        PORTB=B00000001;
        PINB|=B00000100;
        break;
      case 2:
        PORTB=B00000001;
        PINB|=B00000010;
        break;
    } 
  //delay(100);
  //Serial.println(bootMode);  
  }
  Serial.println(trigLength); 
}

void loop() 
{  
  //enables clock and reset functions
  deClock();
  deReset();

  generateArray0();
  generateArray2();
  generateArray1();
  //comment out for CV
  //deReset0();
  //deReset1();
  //deReset2();

  //global & individual resets
  if(resetState) 
  {
    lastReset = millis();
    digitalWrite(reset_led, HIGH);
    step0 = (length0 - 1);
    step1 = (length1 - 1);
    step2 = (length2 - 1);
  }
  
  //un-comment for turning CV inputs into individual reset inputs!
  /*
  if(reset0State) {
    lastReset0 = millis();
    digitalWrite(led0, HIGH);
    step0 = (length0 - 1);
  }
  if(reset1State) {
    lastReset1 = millis();
    digitalWrite(led1, HIGH);
    step1 = (length1 - 1);
  }
  if(reset2State) {
    lastReset2 = millis();
    digitalWrite(led2, HIGH);
    step2 = (length2 - 1);
  }  */
  
//for each incoming clock detected:
  if(clockState)
  { 
    lastClock = millis();
    step0++;
    step1++;
    step2++;

    digitalWrite(clock_led, HIGH);

    if(step0 > (length0 - 1)) 
    {
      step0 = 0;
    }
    if(step1 > (length1 - 1))
    {
      step1 = 0;
    }
    if(step2 > (length2 - 1))
    {
      step2 = 0;
    }

    //current step number
    pos0 = step0;
    pos1 = step1;
    pos2 = step2;

    
    //read CV input Longitude, Altitude, Latitude
    cv0 = analogRead(A0);
    cv1 = analogRead(A1);
    cv2 = analogRead(A2);


    if(cv0 > 1011) 
    {
      stepValue0 = 0;
      stepValue0 = 1;
      digitalWrite(led0, HIGH);
    } 
    else 
    { 
      stepValue0 = 0;
      stepValue0 = patternArray0[pos0];
    }

    if(cv1 > 1011)
    {
      stepValue1 = 0;
      stepValue1 = 1;
      digitalWrite(led1, HIGH);
    }
    else
    { 
      stepValue1 = 0;
      stepValue1 = patternArray1[pos1];
    }

    if(cv2 > 1011)
    {
      stepValue2 = 0;
      stepValue2 = 1;
      digitalWrite(led2, HIGH);
    }
    else 
    { 
      stepValue2 = 0;
      stepValue2 = patternArray2[pos2];
    }


    if(stepValue0)
    {
      PINB|=B00001000;
    }

    if(stepValue1)
    {
      PINB|=B00000100;
    }

    if(stepValue2)
    {
      PINB|=B00000010;
    }

    //read values from pots Longitude, Altitude, Latitude
    pot0 = analogRead(A3);
    pot1 = analogRead(A4);
    pot2 = analogRead(A5);

    // TODO: clamp these? analogRead can't be negative, so CV can't lower a knob turned to max.
    //add CV to pot value (offset)
    prob0 = (pot0 + cv0);
    prob1 = (pot1 + cv1);
    prob2 = (pot2 + cv2);

    noSteps0 = map(prob0, 1, 1021, 1, 8);
    
  } // if (clockState)

  //sets the end of trigger signals and clock LED
  if(millis() >= lastClock + trigLength)
  {
    PORTB=B00000001;
    digitalWrite(clock_led, LOW);
  }

  // LONGITUDE - kick
  if(prob0 > (prevProb0 + 2) || prob0 < (prevProb0 - 2)) 
  {
    prevProb0 = prob0;   

    if(prob0 > 2)
    {        
      if(prob0 < 1011)
      {      
        generate0 = true;
        size_t c = kPatternLength;
        size_t d = kPatternCount - 1;
        size_t e = 1011;
        size_t p = (prob0*d/e)*c; 
        size_t f = (prob0*d)%e;
        int* dA = data0 + p;
        int* dB = data0 + p + c;
        // Serial.print("pattern0 {"); Serial.print(prob0); Serial.print(" "); Serial.print(p); Serial.print(" "); Serial.print(f); Serial.println("}:");
        for(int i = 0; i < length0; i++) 
        {
          size_t a = dA[i], b = dB[i];
          size_t x = ((e-f)*a)/e, y = (f*b)/e;
          // Serial.print("{"); Serial.print(a); Serial.print(","); Serial.print(b); Serial.print(","); Serial.print(x); Serial.print(","); Serial.print(y); Serial.print("} ");
          // Serial.print(x+y); Serial.print(":");
          patternArray0[i] = randomArray0[i] < (x+y);
          // Serial.print(patternArray0[i]);
          // Serial.print(" ");
        }
        // Serial.println("");
      }
    }
    else
    {
      for(int i=0; i < length0; i++)
      {
        patternArray0[i] = 0;   
      }         
    }

    if(pot0 > 1011)
    {
      for(int i = 0; i < length0; i++)
      {
        patternArray0[i] = 1;   
      }         
    }                  
  }    
 
  // LATITUDE - hat / perc
  if(prob2 > (prevProb2 + 2) || prob2 < (prevProb2 - 2)) 
  {
    prevProb2 = prob2;     

    if(prob2 > 2) 
    {
      if(prob2 < 1011) 
      {
        generate2 = true;
         
        size_t c = kPatternLength;
        size_t d = kPatternCount - 1;
        size_t e = 1011;
        size_t p = (prob2*d/e)*c; 
        size_t f = (prob2*d)%e;
        int* dA = data2 + p;
        int* dB = data2 + p + c;
        for(int i = 0; i < length2; i++) 
        {
          size_t a = dA[i], b = dB[i];
          size_t x = ((e-f)*a)/e, y = (f*b)/e;
          patternArray2[i] = randomArray2[i] < (x+y);
        }
      }
    } 
    else 
    {
      for(int i=0; i < length2; i++) 
      {
          patternArray2[i] = 0;   
      }
      prevProb2 = 0;
    }

    if(pot2 > 1011) 
    {
      for(int i=0; i < length2; i++)
      {
        patternArray2[i] = 1;   
      }         
    }
  }

  // ALTITUDE - snare
  if(prob1 > (prevProb1 + 2) || prob1 < (prevProb1 - 2)) 
  {
    prevProb1 = prob1;

    if(prob1 > 2) 
    {
      if(prob1 < 1011) 
      { 
        generate1 = true;
               
        size_t c = kPatternLength;
        size_t d = kPatternCount - 1;
        size_t e = 1011;
        size_t p = (prob1*d/e)*c; 
        size_t f = (prob1*d)%e;
        int* dA = data1 + p;
        int* dB = data1 + p + c;
        for(int i = 0; i < length1; i++) 
        {
          size_t a = dA[i], b = dB[i];
          size_t x = ((e-f)*a)/e, y = (f*b)/e;
          patternArray1[i] = randomArray1[i] < (x+y);
        } 
      } 

      if(pot1 > 1011) 
      {
        for(int i=0; i < length1; i++) 
        {
          patternArray1[i] = 1;   
        }         
      }
    }
    else 
    {
      for(int i=0; i < length1; i++) 
      {
        patternArray1[i] = 0;
      }
    }
  }

  //turn off reset LED 
  if(millis() >= lastReset + trigLength) 
  {
    digitalWrite(reset_led, LOW);
  }
  //turn off coordinate LEDs
  if(millis() >= lastGenerate0 + trigLength) 
  {
    digitalWrite(led0, LOW);
  }  
  if(millis() >= lastGenerate1 + trigLength) 
  {
    digitalWrite(led1, LOW);
  }
  if(millis() >= lastGenerate2 + trigLength) 
  {
    digitalWrite(led2, LOW);
  }
}
