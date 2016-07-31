

long dt1 = 5000;
long t1 = 0;
int index1 = 3;

long dt2 = 500;
long t2 = 0;
int index2 = 4;

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
 pinMode(index1, OUTPUT);
 pinMode(index2, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your maincode here, to run repeatedly:

int  now = millis();
   if( now - t1 > dt1){
    t1 = now;
    toggleLed(index1);
   }
   
   if( now - t2 > dt2){
    t2 = now;
    toggleLed(index2);
   }
}
