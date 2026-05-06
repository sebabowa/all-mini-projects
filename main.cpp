
#include <Arduino.h> //include the Arduino

// include the Libraries for the OLED
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// include the libraries for the DHT sensor
#include <DHT.h>
// all the needed libraries

//-------------DEFINE THE PINS ---------//
#define RELAY_PIN 7 // relay pin
#define BUZZER_PIN 8 // buzzer pin
#define DHT_SENSOR_PIN 9 // DHT sensor pin

// fix oled
#define WIDTH 128
#define LENGTH 64
Adafruit_SSD1306 display(WIDTH, LENGTH , &Wire, -1);

//define the dht
#define DHTTYPE DHT11
#define DHTPIN DHT_SENSOR_PIN
DHT dht (DHT_SENSOR_PIN,DHTTYPE);


// the states for each state
enum States { 
    IDLE,
    HOT ,
    FINE ,
    COLD
    ///TODO i need to add more states
};

//start at the  idle state and search for it
States currentState = IDLE;


void setup (){
    Serial.begin (9600);
    // pinModes 
pinMode (RELAY_PIN,OUTPUT);
pinMode (BUZZER_PIN,OUTPUT);
pinMode (DHT_SENSOR_PIN,INPUT);

// initialize the needed sensors

// start the oled
display.begin ();
display.clearDisplay();
display.setCursor (0,0);
// star the DHT
dht.begin();
}

void loop (){
    // At the idle state//

    // read the tempture and humidity from the DHT sensor
  int Temperature =  dht.readTemperature ();
  int Humidity = dht.readHumidity ();

  // print the values to oled

  //temp
  display.clearDisplay();
  display.setCursor  (0,0);
  display.setTextSize (1);
  display.print ("Temp : ");
    display.print (Temperature);
    display.print (" C");
    display.display ();

    // humidity
display.setTextSize (1);
display.setCursor (0,16);
display.print (" H = ");
display.print (Humidity);
dislay.print (" %");
display.display ();
    
  if (Temperature >32){
    switch (currentState) {

        case FINE:
         //temp
    display.clearDisplay();
    display.setCursor  (0,0);
    display.setTextSize (1);
    display.print ("Temp : ");
    display.print (Temperature);
    display.print (" C");
    display.display ();

    // humidity
display.setTextSize (1);
display.setCursor (0,16);
display.print (" H = ");
display.print (Humidity);
dislay.print (" %");
display.display ();
        // set the relay to off (cuz normal temp )
         digitalWrite (RELAY_PIN,HIGH); // always put on low for the relay when you want it to run
      

      if (Temperature > 35){
            currentState = HOT;
         } 
            break;
            
        case HOT:
         display.clearDisplay();
         display.setCursor  (0,0);
         display.setTextSize (1);
         display.print ("Temp : ");
         display.print (Temperature);
         display.print (" C");
         display.display ();

    // humidity
display.setTextSize (1);
display.setCursor (0,16);
display.print (" H = ");
display.print (Humidity);
display.print (" %");
display.display ();

//trigger the relay and the buzzer
digitalWrite (RELAY_PIN,LOW);
tone (BUZZER_PIN,1000);

if (Temperature < 27){
    currentState = COLD;
}
break;
case COLD:
        display.clearDisplay();
        display.setCursor  (0,0);
        display.setTextSize (1);
        display.print ("Temp : ");
        display.print (Temperature);
        display.print (" C");
        display.display ();

    // humidity
display.setTextSize (1);
display.setCursor (0,16);
display.print (" H = ");
display.print (Humidity);
dislay.print (" %");
display.display ();

digitalWrite (RELAY_PIN,HIGH);
noTone (BUZZER_PIN);


         }

        

        

  
  }


}