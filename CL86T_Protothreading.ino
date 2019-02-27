const int enaneg = 22;
const int dirneg = 24;
const int pulneg = 26;

const int encoderA = 18;
const int encoderB = 19;

int counter = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long runMillis = 0;
int stepInterval = 500;
boolean stepPosition = false;
volatile byte stateA = LOW;
volatile byte stateB = LOW;
int noStep = 200;
double encoderTimeA[200];
double encoderTimeB[200];
int count = 0;
double lastTime = 0;
double totalTime = 0;
int encoderCount = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(enaneg,OUTPUT);
  pinMode(dirneg,OUTPUT);
  pinMode(pulneg,OUTPUT);

  pinMode(encoderA,INPUT);
  pinMode(encoderB,INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderA), senseEncoderA, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderB), senseEncoderB, RISING);
  Serial.begin(9600);
}

void senseEncoderA(){
  encoderTimeA[counter] = currentMillis - runMillis;
  counter++; 
}

void senseEncoderB(){
  encoderTimeB[counter] = currentMillis - runMillis;
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = 0;
  counter = 0;
  runMillis = micros();
  while(x < noStep){
    currentMillis = micros();
//    encoderAPos = digitalRead(encoderA);
//    encoderBPos = digitalRead(encoderB);
    if(currentMillis - previousMillis >= stepInterval && !stepPosition){
      digitalWrite(pulneg,HIGH);
      stepPosition = true;
      previousMillis = currentMillis;
    }
    if(currentMillis - previousMillis >= stepInterval && stepPosition){
      digitalWrite(pulneg,LOW);
      stepPosition = false;
      previousMillis = currentMillis;
      x++;
    }
//    if(lastEncoderA != encoderAPos){
//      if(encoderAPos == 0)
//        Serial.println("A is HIGH");
//    } else {
//        Serial.println("A is LOW");
//        Serial.println(digitalRead(encoderA));
//    }
//    if(lastEncoderB != encoderBPos){
//      if(encoderBPos == 0)
//        Serial.println("B is HIGH");
//    } else {
//        Serial.println("B is LOW");
//    }    
//    lastEncoderA = encoderAPos;
//    lastEncoderB = encoderBPos;
   }
  count = 0;
  lastTime = 0;
  totalTime = 0;
  encoderCount = 0;
  Serial.print("\n Array start \n");
  while (count < counter){
      if (encoderTimeA[count] != 0){
        totalTime += encoderTimeA[count] - lastTime;
        lastTime = encoderTimeA[count];
        encoderCount++;
      }
    Serial.print(encoderTimeA[count]);
    Serial.print(" ");
    encoderTimeA[count] = 0;
    encoderTimeB[count] = 0;
    count++;
  }
//  double avgTime = totalTime/encoderCount;
//  double avgVelocity = (encoderCount/1000) * 360/(avgTime * 0.000001);
//  Serial.print(avgVelocity);
  Serial.print("\n");
  Serial.print(counter);
  Serial.print("\n Array over");
//  delay(1000);
}
