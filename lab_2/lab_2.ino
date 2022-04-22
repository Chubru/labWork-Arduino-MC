#define COUNT_LED 5




volatile int halfPeriod = 1;
int currnetPhase = 0;
int  ledPin[]={8,9,10,11,12};
volatile int ledStatus = 0;

bool isPressed = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, buttonTickPlus, FALLING);
  attachInterrupt(0, buttonTickMinus, FALLING);

 // for(int i = 0;i < COUNT_LED;i++)
   // pinMode(ledPin[i], OUTPUT);

  // pinMode(13, OUTPUT);
 //  digitalWrite(13, LOW);
 
    asm volatile
    (
      "ldi r16, 0xFF" "\n" 
      "out 0x04, r16" "\n"
     );
   
     
}
void buttonTickPlus() {
  if(isPressed)
    return;
  halfPeriod*=2;
  if(halfPeriod > 512 )
    halfPeriod = 512;
  isPressed = true;
}

void buttonTickMinus() {
   if(isPressed)
    return;
  halfPeriod/=2;
  if(halfPeriod==0)
    halfPeriod = 1;
  isPressed = true;
}


void ledControl(){
 
   asm volatile
    (
      "mov r16, %0" "\n"
      //"mov r17, %1" "\n" 
      //"eor r17,r16" "\n"
      //"mov %0, r16" "\n" 
      "out 0x05, r16" "\n"
      :  "+r" (ledStatus)
     );
  return;
}



void loop() {
  isPressed = false;
  if(currnetPhase++ > halfPeriod){
    int id = random(0,COUNT_LED);
    currnetPhase = 0;
    ledStatus = ledStatus ^ (1<<id);
    Serial.println(ledStatus);
    ledControl();
 
  }
  delay(15);  
}
