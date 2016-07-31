

long dt = 500;
int index = 3;
long t = 0;

void toggleLed(int ledIndex) {
  if (digitalRead(ledIndex) == LOW) {
        digitalWrite(ledIndex, HIGH);
    }
    else {
        digitalWrite(ledIndex, LOW);
    }
  Serial.print(ledIndex);
  Serial.print("\n");
}


void setup() {
  // put your setup code here, to run once:
 pinMode(index, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your maincode here, to run repeatedly:

int  now = millis();
   if( now - t > dt){
    t = now;
    toggleLed(index); 
   }
}
