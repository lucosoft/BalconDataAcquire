/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define USONIC_DIV 58.0
#define MEASURE_SAMPLE_DELAY 5
#define MEASURE_SAMPLES 25
#define MEASURE_DELAY 1000

// defines pins numbers
//const int trigPin = 9;
//const int echoPin = 10;
// defines variables
long duration;
int distance;
int distanceAverage[10] = {0};
void setup() {
//pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//Serial.begin(9600); // Starts the serial communication

   // Serial monitoring
   Serial.begin(9600);

   // Initializing Trigger Output and Echo Input
   pinMode(TRIGGER_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);

   // Reset the trigger pin and wait a half a second
   digitalWrite(TRIGGER_PIN, LOW);
   delayMicroseconds(500);

   // Populate array for average calculator
   for(int i=0;i<10;i++){
      delay(MEASURE_DELAY);
      distanceAverage[i] = measure();
   }

   Serial.println("StandAloneSr04Hc06!");

}
void loop() {
/*
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(1000);                       // wait for a second
*/
  delay(MEASURE_DELAY);
  long distance = measure();
  //averageCalc(distance);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(averageCalc(distance));
  Serial.println(" mm");
}

long measure()
{
  long measureSum = 0;
  for (int i = 0; i < MEASURE_SAMPLES; i++)
  {
    delay(MEASURE_SAMPLE_DELAY);
    measureSum += singleMeasurement();
  }
  return measureSum / MEASURE_SAMPLES;
}

long singleMeasurement()
{
  long duration = 0;
  // Measure: Put up Trigger...
  digitalWrite(TRIGGER_PIN, HIGH);
  // ... wait for 11 µs ...
  delayMicroseconds(11);
  // ... put the trigger down ...
  digitalWrite(TRIGGER_PIN, LOW);
  // ... and wait for the echo ...
  duration = pulseIn(ECHO_PIN, HIGH);
  return (long) (((float) duration / USONIC_DIV) * 10.0);
}

long averageCalc(long distance){
   long distanceAverageAcum = 0;
   int distanceAverageAux[10] = {0};
   for(int j=0;j<9;j++){
      distanceAverageAux[j+1] = distanceAverage[j];
   }
   distanceAverageAux[0]= distance;
   for(int k=0;k<10;k++){
      distanceAverageAcum += distanceAverageAux[k];
   }

   for(int l=0;l<10;l++){
      distanceAverage[l] = distanceAverageAux[l];
      Serial.print("distanceAverageAux");
      Serial.print(l);
      Serial.print(": ");
      Serial.print(distanceAverageAux[l]);
      Serial.println(" ");
   }

//  Serial.print("distanceAverage: "); 
//  Serial.println((distanceAverageAcum/10)); 
  
  //distanceAverage[i] -> shift average
  distanceAverageAcum = distanceAverageAcum/10;
  return distanceAverageAcum;
}
