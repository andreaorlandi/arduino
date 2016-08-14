#include <stdarg.h>

void debug_print(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}


class Led {

  public:
      int _index;
      long _dt;
      long _t;
      
      Led() {
        _index = 0;
        _dt = 0;
        _t = 0;
      }
      
      void initialize(int index, long dt) {
        _index = index;
        _dt = dt;
        pinMode(_index, OUTPUT);
      }

      void on() {
        digitalWrite(_index, HIGH);
      }

      void off() {
        digitalWrite(_index, LOW);
      }

      bool isOn() {
        bool value = false;
        if (digitalRead(_index) == HIGH) {
          value = true;
        }
        return value;
      }

      void toggle() {
        if (isOn()) {
          off();
        }
        else {
          on();
        }
      }

      void tick(long t) {
        // verifichiamo se e' passato abbastanza tempo 
        // da dover aggiornare lo stato del led
        if (t - _t > _dt) {
           _t = t;
          toggle();
        }
      }
};


Led ledA = Led();
Led ledB = Led();
Led ledC = Led();

void setup() {
  Serial.begin(9600);
  ledA.initialize(3, 1000);
  ledB.initialize(5, 100);
  ledC.initialize(4, 500);
}

void loop() {

  long now = millis();
  Serial.print(now);
  Serial.print("\n");
  ledA.tick(now);
  ledB.tick(now);
  ledC.tick(now);

  //debug_print("led %d: %s\n", ledA._index, ledA.isOn() ? "ON" : "OFF");
  //debug_print("led %d: %s\n", ledB._index, ledB.isOn() ? "ON" : "OFF");
  //debug_print("led %d: %s\n", ledC._index, ledC.isOn() ? "ON" : "OFF");

  delay(500);
}
