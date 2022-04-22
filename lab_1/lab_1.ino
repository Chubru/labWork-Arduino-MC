#define DOT_TIME 250
int led = 8;

void setup() {
 pinMode(led, OUTPUT);
 Serial.begin (9600); 
}

void dot(){
 digitalWrite(led, HIGH); 
 delay(250);
 digitalWrite(led, LOW); 
 delay(250);
}

void dash(){
 digitalWrite(led, HIGH); 
 delay(750);
 digitalWrite(led, LOW); 
 delay(250);
}


void pause(){
 delay(250);
}


void show(const String& morsze){
 for(int i = 0;i < morsze.length();i++){
  if(morsze[i]=='.')
   dash();
   
   if(morsze[i]=='-')
   dot();

   if(morsze[i]==' ')
   pause();
 }

 
}

String encode(const String& str){
 String morsze;
 
 for(int i = 0;i < str.length();i++){
   if(str[i] == 'A')
    morsze+=".- ";

   if(str[i] == 'B')
    morsze+="-... ";

   if(str[i] == 'C')
     morsze+="-.-. ";

   if(str[i] == 'D')
     morsze+="-.. ";
   
   if(str[i] == 'E')
    morsze+=". ";
   
   if(str[i] == 'F')
    morsze+="..-. ";
   
   if(str[i] == 'G')
    morsze+="--. ";
  
   if(str[i] == 'H')
    morsze+=".... ";
   
   if(str[i] == 'I')
    morsze+=".. ";

   if(str[i] == 'J')
    morsze+=".--- ";

   if(str[i] == 'K')
    morsze+=".-. ";
    
   if(str[i] == 'L')
    morsze+=".-.. ";

   if(str[i] == 'M')
    morsze+="-- ";

   if(str[i] == 'N')
    morsze+="-. ";

   if(str[i] == 'O')
    morsze+="--- ";
    
   if(str[i] == 'P')
    morsze+=".--. ";

   if(str[i] == 'Q')
    morsze+=" --.- ";
    
   if(str[i] == 'R')
    morsze+=".-. ";
    
   if(str[i] == 'S')
    morsze+="... ";

   if(str[i] == 'T')
    morsze+="- ";

   if(str[i] == 'U')
    morsze+="..- ";

   if(str[i] == 'V')
    morsze+="...- ";

   if(str[i] == 'W')
    morsze+=".-- ";
   
   if(str[i] == 'X')
    morsze+="-..- ";

   if(str[i] == 'Y')
    morsze+="-.-- ";

   if(str[i] == 'Z')
    morsze+="--.. ";
    
   if(str[i] == ' ')
    morsze+="       ";
 }
 return morsze;
}

void loop() {
 String str("IVAN IVAN");
 Serial.println(encode(str).c_str());
 show(encode(str));
 delay(10000);
}
