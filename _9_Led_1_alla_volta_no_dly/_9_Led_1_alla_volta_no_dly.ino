/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#include <stdarg.h>

void debug_print(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}


long t0 = 0;
int acceso = 0;
int indice = -1;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  t0 = millis();
}


void esegui_elaborazione() {

    Serial.print(dt);
    Serial.print("\n");

    // spengo il led corrente
    if (indice >= 0) {
        digitalWrite(indice, LOW);
    }

    // incremento indice
    indice++;
    if ( indice > 10 ) {
      indice = 2;
    }

    // accendo nuovo led
    digitalWrite(indice, HIGH);

}


void elabora_luci() {

    // Verifico se e' il momento di intervenire
    long t = millis();
    long dt = t - t0;
    if ( dt >= 250 ) {

      esegui_elaborazione();
    
      t0 = t;
    }
}


int contatore_principale = 0;

// the loop function runs over and over again forever
void loop() {

  /*
  for (int i=2; i<11; i++) {
    digitalWrite(i, HIGH);
    //delay(250);
    digitalWrite(i, LOW);
  }
  */

    //Serial.print(contatore_principale);
    debug_print("Contatore principale %3d \n", contatore_principale);
    Serial.print(contatore_principale);
    Serial.print("\n");
    contatore_principale++;

  //delay(200);

  elabora_luci();
}
