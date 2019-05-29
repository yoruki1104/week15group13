int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
const int buttonPin = 7;
int buttonState = 0;
byte colDataMatrix[8] = { B01111111,
   B10111111,
   B11011111,
   B11101111,
   B11110111,
   B11111011,
   B11111101,
   B11111110
  };
                      
byte rowDataMatrix[8] = { B01000100,
                          B10101010,
                          B00000000,
                          B00000000,
                          B01111100,
                          B00101000,
                          B00010000,
                          B00000000
  };
  byte rowDataMatrix1[8] = {
                          B11111111,
                          B01000000,
                          B00100100,
                          B00011000,
                          B00011000,
                          B00100100,
                          B00000010,
                          B11111111
  };
  // 定義顯示器顯示的時間 (延遲時間), 預設 1ms
int delay_time = 1;
       

void setup() {
  // put your setup code here, to run once:
pinMode(latchPin,OUTPUT);
pinMode(clockPin,OUTPUT);
pinMode(dataPin,OUTPUT);
pinMode(buttonPin,INPUT);
digitalWrite(buttonPin,HIGH);
}
void loop() {
buttonState = digitalRead(buttonPin);
if(buttonState == LOW){
 
for(int i = 0; i < 8 ; i++){

//byte colData = colDataMatrix[i];

digitalWrite(latchPin,LOW);

// pickDigit(i);

shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);

shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);

//shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);

digitalWrite(latchPin,HIGH);

delay(delay_time);

  }
}
else if(buttonState == HIGH){
  for(int i = 0; i < 8 ; i++){
digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, colDataMatrix[i]);  //mask(col)
  shiftOut(dataPin, clockPin, rowDataMatrix1[i]);  //row
  digitalWrite(latchPin, 1);
  }
 
}

}

void pickDigit(int x) {

byte rowByte = 1 << x;

shiftOut(dataPin, clockPin, MSBFIRST, rowByte);

}
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut&#239;&#191;&#189;
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {        
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}
