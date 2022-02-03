// Bluetooth
#include <SoftwareSerial.h>  //Librairie Software Serial Port  
#define RX 10                //Pin 10 pour RX 
#define TX 11                //Pin 11 pour TX

// Creation objet serie pour le hc06
SoftwareSerial PhmHC06Serie(RX,TX);  

String cmd=""; 

// Bande LED
#include <Adafruit_NeoPixel.h>
int X = 12;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 6, NEO_GRB + NEO_KHZ800);

void setup()  {  
  // Bluetooth
  Serial.begin(9600);    
  Serial.println("Pret ...");  
  PhmHC06Serie.begin(9600);  //Valeur par défaut pour le HC06

  // Bande LED
  strip.begin();
  strip.show();
}  
void loop()  
{  
 //Lecture des données HC06
  while(PhmHC06Serie.available()>0){
    cmd+=(char)PhmHC06Serie.read();
    delayMicroseconds(500);
    Serial.println(cmd);
  }

  //Traitement de la commande recue
  if(cmd!=""){
    Serial.print("Une commande a ete recue ....");
    Serial.println(cmd);
    // Commande LEDON pour allumage LED
    if(cmd=="LEDON"){
        Serial.println("Allumage LED");
        for(int i = 0; i < X; i++ ) {strip.setPixelColor(i, 245, 128, 0);}
        strip.show();
        Serial.println("Lumière jaune"); 
        delay(1000);  
    }
    // Commande LEDOFF pour extinction LED
    if(cmd=="LEDOFF"){
        Serial.println("Extinction LED");
        for(int i = 0; i < X; i++ ) {strip.setPixelColor(i, 0, 0, 0);}
        strip.show();
        Serial.println("Lumière jaune"); 
        delay(1000); 
    }
    cmd=""; //Reset variable commande envoyée par Bluetooth
  }
}
