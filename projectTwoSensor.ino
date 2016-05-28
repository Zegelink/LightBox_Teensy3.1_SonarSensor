//We have 2x3 LEDs
#define ROW 2
#define COLUMN 3
#define PINR 3
#define PINC 0
#define triggerpin 14
#define echopin 15
#define triggerpin2 16
#define echopin2 17

void setArray(int array[][COLUMN], int distance, int distance2);

void setArray(int array[][COLUMN], int distance, int distance2){
  float unit = 17;
  float unit2 = 17;
  int num = 0;
  int num2 = 0;
  for (float i = 0; i < distance; i+=unit){
    //number of 1s.
    num++;
  }
  for (float i = 0; i < distance2; i+=unit2){
    //number of 1s.
    num2++;
  }
  for (int x = 0; x<num; x++){
    for (int y = 0; y < num2; y++){
      array[x][y] = 1;
    }
  }
}

void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
  //set pin 1~5 to OUTPUT
  for (int i = 0; i <= 15; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(triggerpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(triggerpin2, OUTPUT);
  pinMode(echopin2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    float duration, distance;
    float duration2, distance2;
    int array[ROW][COLUMN];
    //initialize array
    for (int i = 0; i < ROW; i++){
      for (int j = 0; j < COLUMN; j++){
        array[i][j] = 0;
      }
    }
    //send the signal to triggerpin
  digitalWrite(triggerpin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerpin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerpin, LOW);
  duration = pulseIn(echopin, HIGH);
  //This equation converts the distance sonar sensor sensed into centimeters.
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");

  digitalWrite(triggerpin2, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerpin2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerpin2, LOW);
  duration2 = pulseIn(echopin2, HIGH);
  distance2 = (duration2/2) / 29.1;
  Serial.print(distance2);
  Serial.println(" cm");

  if ((distance2 < 40) && (distance < 40)){
      setArray(array, distance, distance2);
  }
  //make light changes slower
  for (int timer = 0; timer < 30; timer++){
  for (int i = 0; i < ROW; i++){
    //first row is pin 4
    digitalWrite(i+PINR, HIGH);
    for (int j = 0; j < COLUMN; j++){
      //if the value in the array == 1; set the column switch to low
      if (array[i][j] == 1){
        digitalWrite(j+PINC, LOW);
        //a small delay 
        delay(1);
        //turn it off
        digitalWrite(j+PINC, HIGH);
      }
      else{
        digitalWrite(j+PINC, HIGH);
      }
    }
    digitalWrite(i+PINR, LOW);
  }
  }
}


