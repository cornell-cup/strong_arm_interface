/* Variable Initializations*/

//Does nothing
const int enaneg = 22;

//Goes to DIR- and PUL- on CL86T Stepper Driver
const int dirneg = 24;
const int pulneg = 26;

//Goes to EA+ and EB+ on CL86T Stepper Driver
const int encoderA = 18;
const int encoderB = 19;

//Counts the number of times the encoder pulses for a 200 step rotation
int counter = 0;

//
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long runMillis = 0;

int stepInterval = 500;
boolean stepPosition = false;
volatile byte stateA = LOW;
volatile byte stateB = LOW;
int numStep = 200;
double encoderTimeA[200];
double encoderTimeB[200];
int count = 0;
double lastTime = 0;
double totalTime = 0;
int encoderCount = 0;

void setup() {
  //Set "Control Signal" variables as output
  pinMode(enaneg,OUTPUT);
  pinMode(dirneg,OUTPUT);
  pinMode(pulneg,OUTPUT);

  //Set "Encoder" signals as input
  pinMode(encoderA,INPUT);
  pinMode(encoderB,INPUT);
  
  //Set up interrupts on both "Encoder" signals to detect rising edge changes
  attachInterrupt(digitalPinToInterrupt(encoderA), senseEncoderA, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderB), senseEncoderB, RISING);
  
  //Start the serial port
  Serial.begin(9600);
}

//ISR for Encoder A that records time of rising edge from start of program and increases pulse count (for 200 step rotation)
void senseEncoderA(){
  encoderTimeA[counter] = currentMillis - runMillis;
  counter++; 
}

//ISR for Encoder B that records time of rising edge from start of program (pulse count increased by senseEncoderA -- both in line, just phase shifted)
void senseEncoderB(){
  encoderTimeB[counter] = currentMillis - runMillis;
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = 0;
  counter = 0;
  runMillis = micros();
  while(x < numStep){
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
