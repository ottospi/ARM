/* gb 21/02, 22/2020
 * v 1.0
 * 21/02 - transfert Méga Pro sur la platine Robotarm, 22/2 - câblage Mega + prog.
*/

#include <Servo.h>
#include <SPI.h>
#include "U8glib.h"
U8GLIB_SSD1309_128X64 u8g(52, 51, 53, 49, 48);         // SW SPI Com: SCK = 52, MOSI = 51, CS = 53, DC = 49, RES = 48

#define LEDRb 37                      //leds rouges boîtier
#define LEDGb 39                      //leds vertes boîtier
#define ouvre 33                      //poussoir ouverture
#define ferme 35                      //poussoir fermeture
#define sw1 30                        //switchs pince
int STEPbase = 28;
int DIRbase = 29;
int STEPtour = 26;
int DIRtour = 27;
int STEPmotR = 24;
int DIRmotR = 25;
int STEPmotL = 22;
int DIRmotL = 23;
int duree_pas;                        // durée d'un pas en us
int deplbase;                         // position du slider cde base
int deplmotL;                         // position du slider cde moteur L
int deplmotR;                         // position du slider cde moteur R
int depltour;                         // position du potar cde moteur tournant

Servo se1;                            //création objet servo pour contrôler le servo - se1
int pos_se1 = 26;


void setup() {
  Serial.begin(9600);  

// TIMSK0=0;                              //turn off the T/C 0 interrupt (stops servo jitter)
  
  se1.attach(31);                       // attribution pin 31 pour servo
  pinMode(ouvre, INPUT_PULLUP); pinMode(ferme, INPUT_PULLUP); pinMode(sw1, INPUT_PULLUP);
  pinMode(LEDRb, OUTPUT); pinMode(LEDGb, OUTPUT);

  se1.write(pos_se1);
 
    u8g.setFont(u8g_font_6x12);
       u8g.setColorIndex(1);
       u8g.firstPage();  
       do {
        u8g.setPrintPos(40, 11);
        u8g.print("ROBOT-ARM");
        u8g.drawLine(10, 14, 118, 14);
        u8g.setPrintPos(8, 23);
        u8g.print("Test G. Bohdanowicz");
        u8g.drawLine(10, 25, 118, 25);
        u8g.setPrintPos(30, 42);
        u8g.print("FEVRIER/2020");
       }
       while( u8g.nextPage() );
}

void loop() {
    deplbase = analogRead(A9);
    int pos_s1 = map(deplbase, 0, 1023, 40, 140);   // lecture entrée A9 pour déterminer la position du cde de la base
    if (deplbase < 450) {
  digitalWrite(DIRbase, 1);
  duree_pas = map(deplbase, 450, 0, 6000, 3000);
    digitalWrite(STEPbase, 1);
    delayMicroseconds(duree_pas / 2);
    digitalWrite(STEPbase, 0);
    delayMicroseconds(duree_pas / 2);
  }
  else if (deplbase > 570) {
  digitalWrite(DIRbase, 0);
  duree_pas = map(deplbase, 570, 1023, 6000, 3000);
    digitalWrite(STEPbase, 1);
    delayMicroseconds(duree_pas / 2);
    digitalWrite(STEPbase, 0);
    delayMicroseconds(duree_pas / 2);
  }

  deplmotL = analogRead(A11);
    int pos_s2 = map(deplmotL, 0, 1023, 160, 40);
    if (deplmotL < 450) {
  digitalWrite(DIRmotL, 0);
  duree_pas = map(deplmotL, 450, 0, 6000, 3000);
    digitalWrite(STEPmotL, 1);
    delayMicroseconds(duree_pas / 2);
    digitalWrite(STEPmotL, 0);
    delayMicroseconds(duree_pas / 2);
  }
  else if (deplmotL > 570) {
  digitalWrite(DIRmotL, 1);
  duree_pas = map(deplmotL, 570, 1023, 6000, 3000);
    digitalWrite(STEPmotL, 1);
    delayMicroseconds(duree_pas / 2);
    digitalWrite(STEPmotL, 0);
    delayMicroseconds(duree_pas / 2);
  }
  
  deplmotR = analogRead(A13);
    int pos_s3 = map(deplmotR, 0, 1023, 150, 40);
    if (deplmotR < 450) {
  digitalWrite(DIRmotR, 0);
  duree_pas = map(deplmotR, 450, 0, 6000, 3000);
    digitalWrite(STEPmotR, 1);
    delayMicroseconds(duree_pas / 2);
    digitalWrite(STEPmotR, 0);
    delayMicroseconds(duree_pas / 2);
  }
  else if (deplmotR > 570) {
  digitalWrite(DIRmotR, 1);
  duree_pas = map(deplmotR, 570, 1023, 6000, 3000);
    digitalWrite(STEPmotR, 1);
    delayMicroseconds(duree_pas / 2);
    digitalWrite(STEPmotR, 0);
    delayMicroseconds(duree_pas / 2);
  }

  depltour = analogRead(A15);
    int pos_s4 = map(depltour, 0, 1023, 40, 160);
    if (depltour < 450) {
  digitalWrite(DIRtour, 1);
  duree_pas = map(depltour, 450, 0, 6000, 3000);
    digitalWrite(STEPtour, 1);
    delayMicroseconds(duree_pas / 2);
    digitalWrite(STEPtour, 0);
    delayMicroseconds(duree_pas / 2);
  }
  else if (depltour > 570) {
  digitalWrite(DIRtour, 0);
  duree_pas = map(depltour, 570, 1023, 6000, 3000);
    digitalWrite(STEPtour, 1);
    delayMicroseconds(duree_pas / 2);
    digitalWrite(STEPtour, 0);
    delayMicroseconds(duree_pas / 2);
  }
    if (digitalRead(sw1) == 1) {
      digitalWrite(LEDRb, HIGH); digitalWrite(LEDGb, LOW); }
    else  {
      digitalWrite(LEDRb, LOW); digitalWrite(LEDGb, HIGH);  } 

    if (digitalRead(ouvre) == 0 || digitalRead(ferme) == 0)
    servo_se1();           

}

void servo_se1() {
    if (digitalRead(ouvre) == 1 && digitalRead(ferme) == 0) {
      if (digitalRead(sw1) == 1) {
      pos_se1 += 1;  delay(50);
}
      if (pos_se1 > 145)   pos_se1 = 145;
      se1.write(pos_se1); }
    
    if (digitalRead(ouvre) == 0 && digitalRead(ferme) == 1) {     
      pos_se1 -= 1;  delay(50); 
      if (pos_se1 < 26)   pos_se1 = 26;  
      se1.write(pos_se1); }
}
