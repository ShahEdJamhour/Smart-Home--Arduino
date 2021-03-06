// ---------------------------------------------------------------- //
#include <Servo.h> //includes the Servo library
#define echoPin 6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D3 Arduino to pin Trig of HC-SR04
#define INTERVAL_MESSAGE1 3000
#define INTERVAL_MESSAGE2 60000
//-------------------------------------
//Time Vars
//-------------------------------------
unsigned long time_1 = 0;
unsigned long time_2 = 0;
//-------------------------------------
// Distance variables
//-------------------------------------
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

//------------------------------------------
// Servo motor 
Servo ServoP; 
//-----------------------------------------
//PhotoCell and LED photocellPin = 0
const int ldrPin = A0;
int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the sensor divider
int BPin = 12;
//---------------------------------------------
// PIR 
int pirPin = 2; 
int pirStat = 0;
//-------------------------------------------------

//------------------------------------------------
//Temp Sensor
//--------------------------------------------------
int sensePin = A1;  
int sensorInput;    //The variable we will use to store the sensor input
double temp;        //The variable we will use to store temperature in degrees. 
int tempMax = 250;
//--------------------------------
// Motor variables 
///----------------------------------

int fan = 9; // the pin where fan is connected
int fanSpeed = 0;



//---------------------------------
int period = 3000;
unsigned long time_now = 0;
 //----------------------------------

void setup() {
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(BPin, OUTPUT);
  pinMode(pirPin, INPUT);   
  ServoP.attach(13);
 // pinMode(motorPin, OUTPUT);
  pinMode(fan, OUTPUT);

  
}

void loop() {
   digitalWrite(trigPin, LOW);
            // Reads the echoPin, returns the sound wave travel time in microseconds
            duration = pulseIn(echoPin, HIGH);
            // Calculating the distance
            distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
            // Displays the distance on the Serial Monitor

          
            ServoP.write(0) ; 
            if (distance <=50){ 
             Serial.println('L'); // Distance Less than 50 
               

            } 
  
		 		   else {  
                     Serial.println('x');  // invalid distance          
 				             
  
  //--------------------------------------------------------
  
  
   photocellReading = analogRead(photocellPin);
             pirStat = digitalRead(pirPin);



            if (photocellReading < 100 && pirStat == HIGH ) {
              Serial.println('y'); //Bulb on 
               

            }
            else  { 
              Serial.println( 'z');  // Bulb off
             

            } 
  
  
  
  
  
         sensorInput = analogRead(A1); //read the analog sensor and store it
          temp = (double)sensorInput / 1024;       //find percentage of input reading
            temp = temp * 5;                 //multiply by 5V to get voltage
            temp = temp - 0.5;               //Subtract the offset 
            temp = temp * 100;               //Convert to degrees 


            if (temp>=30) 
            {   
     Serial.println ('T'); // Valid temp 
            } 

            else

            {
               Serial.println ('O'); // not valid temp


            }
 
 //---------------------------------------
  
 if (Serial.available() )
 {
   
   char data  = Serial.read(); // Read a character
   
  if ( data=='A')
  {
    
               //----------------------
             time_now = millis();
            //----------------------

            // Clears the trigPin condition
            digitalWrite(trigPin, LOW);

            //---------Delay--------------
            if(millis() >= time_1 + INTERVAL_MESSAGE1){
                  time_1 +=INTERVAL_MESSAGE1;
              }

            //----------------------------
            // Sets the trigPin HIGH (ACTIVE) 
            digitalWrite(trigPin, HIGH);


              //---------Delay For 3 sec --------------
           if(millis() >= time_1 + INTERVAL_MESSAGE1){
                  time_1 +=INTERVAL_MESSAGE1;
            //-----------------------------------------------
            //Get Distance 
            //--------------------------------------------------
              }
            digitalWrite(trigPin, LOW);
            // Reads the echoPin, returns the sound wave travel time in microseconds
            duration = pulseIn(echoPin, HIGH);
            // Calculating the distance
            distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
            // Displays the distance on the Serial Monitor

            //--------------------------------------------------
            // Door Opening part
            //---------------------------------------------------
            ServoP.write(0) ; 
            if (distance <=50){ 
              ServoP.write(120); // door opens 

            } 
            else { 
             //close door
              ServoP.write(0);

            } 
            //wait for 3 sec 
           if(millis() >= time_1 + INTERVAL_MESSAGE1){
                  time_1 +=INTERVAL_MESSAGE1;

              }



            //------------------------------------------------
            //LDR CHECKS IF THERE ISNT ENOUGH LIGHT 
            //--------------------------------------------

          photocellReading = analogRead(photocellPin);
             pirStat = digitalRead(pirPin);



            if (photocellReading < 100 && pirStat == HIGH ) {
               digitalWrite(BPin, HIGH);

            }
            else if (photocellReading < 600  ) {
              digitalWrite(BPin, LOW);

            } else {
                  digitalWrite(BPin, LOW);


            }

//1 min delay
             if(millis() >= time_2 + INTERVAL_MESSAGE2){
                  time_2 +=INTERVAL_MESSAGE2;

               
// Check temp 
              }

            sensorInput = analogRead(A1); //read the analog sensor and store it
          temp = (double)sensorInput / 1024;       //find percentage of input reading
            temp = temp * 5;                 //multiply by 5V to get voltage
            temp = temp - 0.5;               //Subtract the offset 
            temp = temp * 100;               //Convert to degrees 


            if (temp>=30) 
            {   
              fan = 1;         //Trun On Fan.
              //fan on

            fanSpeed = map(temp, 30, tempMax, 32, 255); // the actual speed of fan

          analogWrite(fan, fanSpeed); // spin the fan at the fanSpeed speed
            } 


            else

            {
              fanSpeed = 0; // fan is not spinning

          digitalWrite(fan, LOW);

            }
  } 
  //---------------------------------------------------------------------------

    else if ( data=='1') 
      
    { 
      if (digitalRead (BPin) == HIGH) 
					{
						digitalWrite(BPin, LOW);
					}
					else  
					{
						digitalWrite(BPin, HIGH);
					} 
      
    } 
    else if (data=='2' ) 
      
      
    {
      			if (ServoP.read() == 0 ) 
					{
						ServoP.write(180);
					}
					else  
					{
						ServoP.write(0); 
					}

      
      
      
      
    }
    
    else if ( data=='3') 
    { 
      
       		
       if (digitalRead (fan) == HIGH) 
					{
						digitalWrite(fan, LOW);
					}
					else  
					{
						digitalWrite(fan, HIGH);
					}
      
      
      
      
      
      
    } 
      					
      
    
    
    
    
    
    
  }
  
 } 
} 

/////////////////////////////////////////////////////////////////////////////

   
   
   
   
   
   
   
   
   
   

  
  

