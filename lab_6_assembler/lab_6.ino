void setup() {
  for(int i = 5;i<12;i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);
}


volatile void DigitalWrite_(int pin,byte state){
asm volatile
    (
      "push R16" "\n"
      "push R17" "\n"
      "push R18" "\n"
      "push R19" "\n"
      "push R20" "\n"
      "push R21" "\n"
      "push R22" "\n"
      "push R23" "\n"
      "push R24" "\n"



      "LDI R17, 1" "\n"
      "LDI R20, 0" "\n"

      "setMask:CP R20, %[pin]" "\n"
      "BREQ END2" "\n"
      "LSL R17" "\n"
      "INC R20" "\n"
      "RJMP setMask" "\n"
      "END2:" "\n"
    
      "LDI R20, 0" "\n"

      "MOV R23,R17" "\n"
      "COM R23" "\n"

      "IN R21,0x05" "\n"
      "AND R21, R23" "\n"


      "MOV R22, %[state]" "\n"
      "setMask1:CP R20, %[pin]" "\n"
      "BREQ END1" "\n"
      "LSL R22" "\n"
      "INC R20" "\n"
      "RJMP setMask1" "\n"
      "END1:" "\n"



      "OR R21,R22" "\n"
      
      
      "OUT 0x05, R21" "\n"

      
      "pop R24" "\n"
      "pop R23" "\n"
      "pop R22" "\n"
      "pop R21" "\n"
      "pop R20" "\n"
      "pop R19" "\n"
      "pop R18" "\n"
      "pop R17" "\n"
      "pop R16" "\n"

      : [pin]"+d" (pin) 
      : [state] "l" (state)
     );
  
}

void loop() {
  Serial.println("loop");
  for(int i=0;;i++){
    DigitalWrite_(i%4,i&4?1:0);
    delay(200);    
  }
}
