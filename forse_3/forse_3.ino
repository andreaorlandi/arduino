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

int indice = -1;
int direzione = 1; // 1 = avanti, 0 = indietro
int min_index = 5;
int max_index = 10;
int deltat = 1000;
int deltat_min = 10;
int deltat_max = 1000;
/*
 * Compito:
 * - introdurre le variabili deltat_min = 10, deltat_max = 1000
 * - alla fine di ogni giro, dimezzare deltat per velocizzare la scansione delle luni
 * - se pero' si scende troppo, tornare indietro
 * 
 * - hint: introdurre una variabile per ricordare la direzione del deltat
 */

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  // sostituire con un loop
  for (int i=min_index; i<=max_index; i++) {
    pinMode(i, OUTPUT);
  }

  // SAREBBE COME FARE:
  /*
  int i = min_index;
  while ( i <= max_index ) {
    pinMode(i, OUTPUT);
    i++;
  }
  */

  t0 = millis();
}


void esegui_elaborazione() {

    // inizializzazione ?
    if (indice < 0) {
      indice = min_index -1;
      direzione = 1;
      deltat = 1000;
    }
    else {
    // spengo il led corrente
        digitalWrite(indice, LOW);
    }

    if (direzione == 1) {
      // sposto indice avanti
      if (indice < max_index) {
        indice++;
        if (deltat < deltat_max) { 
          deltat *= 2;
        }

        else{
          deltat /= 2;
        }
      }
      else {
        indice--;
        direzione = 0;
      }
    }
    else {
      // sposto indice indietro
      if (indice > min_index) {
        indice--;
        if (deltat > deltat_min)
        {
          deltat /= 2;
        }
        else {
          deltat *= 2;
        }
      }
       
      else {
        indice++;
        direzione = 1;
        deltat /= 2;
      }
    }
    
    // accendo nuovo led
    digitalWrite(indice, HIGH);
}

void elabora_luci() {

    // Verifico se e' il momento di intervenire
    long t = millis();
    long dt = t - t0;
    if ( dt >= deltat ) {

      esegui_elaborazione();
    
      t0 = t;
    }
}


int contatore_principale = 0;

// the loop function runs over and over again forever
void loop() {


  elabora_luci();
  /*
  for (int i=2; i<11; i++) {
    digitalWrite(i, HIGH);
    //delay(250);
    digitalWrite(i, LOW);
  }
  */

    //Serial.print(contatore_principale);
    //debug_print("Contatore principale %3d \n", contatore_principale);
    //Serial.print(contatore_principale);
    //Serial.print("\n");
    contatore_principale++;

  //delay(200);

  //elabora_luci();
  
}
