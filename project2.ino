#include <IRremote.h>

int redLed = 11;
int yellowLed = 12;
int greenLed = 10;
int Buzzer = 9;
int RECV_PIN = 7;
int SwitchP= 13;

//IR Library
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  //Set Led Pins
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
    pinMode(SwitchP, INPUT);
  
  
  //Enable serial usage and IR signal 
  Serial.begin(9600);
  irrecv.enableIRIn(); 

}

void loop()
{
  int State = digitalRead(SwitchP);
  if ( State==LOW) // IF THE SWITCH IS 0 (LOW) IT WILL WORK ON AUTOMATIC MODE
  { 
    //Automatic mode
    
    Serial.println("A"); 
    
  } 
  else 
  { 
    
  // MANUAL MODE 
    
  if (irrecv.decode(&results)) { 
    unsigned int value = results.value;
    
   // PROGRAMMING THE REOMTE  
    
    switch (value) {
      case 2295: 
      
          Serial.println("1"); // controls Bulb 
 	delay(130);
 
      	break;
      
      case 34935:
      	
      	delay(130);
      	
       Serial.println("2"); //controls  Servo ( door)
      	break;
      
      case 18615:
      
      	delay(100);
      	
       Serial.println("3"); // controls DC motor aka fan
      	break;

    }
    
    
    
    irrecv.resume(); // Receive the next value
  }
  }
  
  if (Serial.available()) {
    
   	 char data  = Serial.read(); // Read a character 
    
  	   if ( data=='L' )  // turn yellow led if distance is less than 50 
       { 
     digitalWrite(yellowLed, HIGH);	
		
         
       }
    else if ( data=='x') 
    { 
         digitalWrite(yellowLed, LOW);	
      
    } 
    
    else if ( data=='y') // turn on bulb when there is enogh light 
    { 
         digitalWrite(greenLed, HIGH);	
      
    } 
     else if ( data=='z') // turn off bulb when there isnt enogh light 
    { 
         digitalWrite(greenLed, LOW);	
      
    } 
    else if ( data=='T')  //Turn red led  on when temp is valid
    { 
       digitalWrite(redLed, HIGH);	
      
    } 
      else if ( data=='o')  //  //Turn red led off when temp isnt valid
    { 
       digitalWrite(redLed, LOW);	
      
    }   
  
  }
}
  