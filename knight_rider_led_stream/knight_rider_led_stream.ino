#include <stdarg.h>

void debug_print(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}


class KnightRiderLedStream {

  public:
      int _start_index;
      int _end_index;
      int _deltat_min;
      int _deltat_max;

      int _dt;
      long _t;
      int _index;      // current led
      int _direction;  // 1 = forward, 0 = backward
      int _deltat_direction = 1;  // 1 = faster, 0 = slower
      float _deltat_factor = 0.75;

      KnightRiderLedStream() {
        _start_index = 0;
        _end_index = 0;
        _dt = 0;
        _deltat_min = 0;
        _deltat_max = 0;
        _t = 0;
        _index = 0;
      }

      void initialize(int start_index, int end_index, int deltat_min, int deltat_max) {
        _start_index = start_index;
        _end_index = end_index;
        _deltat_min = deltat_min;
        _deltat_max = deltat_max;

        _dt = _deltat_max;
        for (int i=start_index; i <= end_index; i++) {
          pinMode(i, OUTPUT);
        }
        _index = start_index;
        _direction = 1;
      }

      /*
      void toggleLed(int index) {
        if (digitalRead(index) == HIGH) {
          digitalWrite(index, LOW);
        }
        else {
          digitalWrite(index, HIGH);
        }
      }
      */

      void update_current_index() {

          if (_direction == 1) {
            // move index forward
            if (_index < _end_index) {
              _index++;
            }
            else {
              _index--;
              _direction = 0;
            }
          }
          else {
            // move index backward
            if (_index > _start_index) {
              _index--;
            }
            else {
              _index++;
              _direction = 1;
            }
          }

          return;
      }

      void update_deltat() {

        if (_deltat_direction == 1) {
            _dt = _dt * _deltat_factor;
        }
        else {
            _dt = _dt / _deltat_factor;
        }

        if (_dt < _deltat_min) {
          _dt = _deltat_min;
          _deltat_direction = 0;
        }
        else if (_dt > _deltat_max) {
          _dt = _deltat_max;
          _deltat_direction = 1;
        }

      }

      void tick(long t) {
        // verifichiamo se e' passato abbastanza tempo
        // da dover aggiornare lo stato del led
        if (t - _t > _dt) {
           _t = t;

          update_current_index();

          // Test index change
          /*
          for (int i=_start_index; i<=_end_index; i++) {
             digitalWrite(i, (i == _index) ? HIGH : LOW);
          }
          */

          // scansione dei led per assegnare la luminosita' opportuna
          for (int i=_start_index; i<=_end_index; i++ ) {
            int intensity = LOW;
            int displacement = (i - _index);
            if (displacement == 0) {
              intensity = HIGH;
            }

            // TODO: ricalcolare le soglie in funzione di deltat_min/max
            if (_dt < 65 && displacement == 1) {
              intensity = HIGH;
            }
            if (_dt < 40 && abs(displacement) == 1) {
              intensity = HIGH;
            }
            digitalWrite(i, intensity);
          }

          // If starting to scan the led stream once again,
          // also update deltat
          if (_index == _start_index) {
            update_deltat();
          }

        }
      }
};


KnightRiderLedStream stream1 = KnightRiderLedStream();
KnightRiderLedStream stream2 = KnightRiderLedStream();

void setup() {
  Serial.begin(9600);
  stream1.initialize(2, 10, 30, 120);
}

void loop() {

  long now = millis();
  Serial.print(now);
  Serial.print("\n");

  stream1.tick(now);
  stream2.tick(now);

  delay(10);
}
