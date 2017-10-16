int DataPin = 2;  // Data Pin is connected to Pin No. 2
int ClockPin = 3; // Data Pin is connected to Pin No. 3
int LatchPin = 4; // Data Pin is connected to Pin No. 4


int DataPin2 = 5;
int ClockPin2 = 6;
//int LatchPin2 = 7;


byte Data1 = 0;  // 8 Bit Data to be sent through DataPin
byte Data2 = 0;

void setup()
{
  pinMode(DataPin, OUTPUT);   // All 3 pins are output
  pinMode(ClockPin, OUTPUT);  
  pinMode(LatchPin, OUTPUT);
  pinMode(DataPin2, OUTPUT);
  pinMode(ClockPin2, OUTPUT);
  //pinMode(LatchPin2, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  increment(); // LEDs Increament start from 0 - 7   
  delay(500);  
  SOS();        // All LEDs ON and OFF 10 times
  OneByOne();   // LEDs Glow one by one from 0 to 7
  delay(500);
  //shiftWrite(15, HIGH);
  

}

// Function defined below-

void shiftWrite(int Pin, boolean State) // Function is similar to digitalWrite 
{                                       // State-0/1 | Pin - Pin No.
  if(Pin >= 8)
  {
    
    bitWrite(Data2, Pin - 8, State);
    shiftOut(DataPin2, ClockPin2, MSBFIRST, Data2);
    //delay(500);
  }
  else
  {
    bitWrite(Data1, Pin, State);             // Making Pin(Bit) 0 or 1
    shiftOut(DataPin, ClockPin, MSBFIRST, Data1); // Data out at DataPin
    
  }
  digitalWrite(LatchPin, HIGH);                // Latching Data
    digitalWrite(LatchPin, LOW);
}

void increment()   //LEDs increment start from 0 - 7 
{
  int PinNo = 0;
  int Delay = 100; 
  
  for(PinNo = 0; PinNo < 16; PinNo++)
  {
    shiftWrite(PinNo, HIGH);
    delay(Delay);                
  }
  for(PinNo = 15; PinNo >= 0; PinNo--)
  {
    shiftWrite(PinNo, LOW);
    delay(Delay);                
  }
}

void OneByOne()  // LEDs Glow one by one from 0 to 7
{
  int PinNo = 0;
  int Delay = 100; 
  
  for(PinNo = 0; PinNo < 16; PinNo++)
  {
    shiftWrite(PinNo, HIGH);
    delay(Delay); 
    shiftWrite(PinNo, LOW);    
  }
  for(PinNo = 15; PinNo >=0 ; PinNo--)
  {
    shiftWrite(PinNo, HIGH);
    delay(Delay); 
    shiftWrite(PinNo, LOW);    
  }

}

void AllHigh()   // sets all High
{
  int PinNo = 0;
  for(PinNo = 0; PinNo < 16; PinNo++)
  {
   shiftWrite(PinNo, HIGH);  
  }
}

void AllLow()   // Sets all low
{
  int PinNo = 0;
  for(PinNo = 0; PinNo < 16; PinNo++)
  {
   shiftWrite(PinNo, LOW);  
  }
}

void SOS(){                  // All LEDs ON and OFF 10 times
  for (int x=0; x<10; x++){    
  AllHigh();
  delay(100);
  AllLow();
  delay(100);
  }
}

