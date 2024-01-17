int ledRed = 13;
int ledYellow = 12;
int ledGreen = 11;
const int trigger = 7;
const int echo = 6;
int buzzer = 5;

void setup(){
  Serial.begin(9600);
  //ULRASONIC SENSOR
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  //LED
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  //BUTTONS
  pinMode(buzzer, OUTPUT);
}

long int Ping(){
  long int duration, cm;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);
  cm = duration/29/2;
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
  return cm;
}

void PedestrianMode(){
  //Reset Lights
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);

    //Blink the Yellow Led
    digitalWrite(ledYellow, HIGH);
    delay(100);
    digitalWrite(ledYellow, LOW);
    //Get Sound from the Buzzer
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    //To delay each time you run a loop
    delay(100);
}

void RegularMode(){
  //Reset Lights
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);
   //Regular Mode
   //Red light 2 secs
    digitalWrite(ledRed, HIGH);
    delay(2000);
    digitalWrite(ledRed, LOW);
    //Yellow light 1 sec
    digitalWrite(ledYellow, HIGH);
    delay(1000);
    digitalWrite(ledYellow, LOW);
    //Green light 2 sec
    digitalWrite(ledGreen, HIGH);
    delay(2000);
    digitalWrite(ledGreen, LOW);
    //Yellow light 1sec
    digitalWrite(ledYellow, HIGH);
    delay(1000);
    digitalWrite(ledYellow, LOW);
}

void NightMode(){
int ldr;  
for(;;){
    ldr = analogRead(A0);
    Serial.print(ldr);
    Serial.print(" LDR");
    Serial.println();
    //If LDR is lower than threshhold   
    if(ldr < 500){
	//keep red on
	digitalWrite(ledGreen, LOW);
	digitalWrite(ledYellow, LOW);
	digitalWrite(ledRed, HIGH);

	for(;;){
		ldr=analogRead(A0);
		if (ldr >500){
			//turn on green
			digitalWrite(ledRed, LOW);
			digitalWrite(ledGreen, HIGH);
			delay(1000);
			goto end;
		}
	}

      /*long int cm=11;
	for(;;){
	cm= Ping();
      if( cm < 10){
      //Keep the Green light on
        digitalWrite(ledRed, LOW);
        digitalWrite(ledGreen, HIGH);
	for(;;){
		cm=Ping();
		if(cm>10) goto end;
	}
      }
	}*/
    }
  }
end:
  //Go back to Regular Mode
    
      Serial.print("Initiating Regular Mode");
      Serial.println();
      //digitalWrite(ledRed, LOW);
      //digitalWrite(ledGreen, LOW);
      RegularMode();
    
  
}

void loop(){
  char choice = '0';
  if (Serial.available() > 0) {
    choice = Serial.read();
    Serial.println();
    
    //Mode 1
    if (choice == '1') {
      Serial.print("Regular Mode is ON.");
      Serial.println();
        RegularMode(); 
    }
    //Mode 2
    else if(choice == '2'){
      Serial.print("Pedestrian Mode is ON.");
      Serial.println();
      long int cm;
      for(;;){
        cm = Ping();
        if(cm < 10){
        for(int i=0; i<10; i++){
           PedestrianMode();
          }
          break;
        }
      }
      Serial.print("Initiating Regular Mode");
      RegularMode();
    }   
    //Mode 3
    else if (choice == '3'){
      Serial.print("Night Mode is ON.");
      Serial.println();
      NightMode();
    } 
    
    else {
      Serial.println("This is not an option.");
    }
   }
}

/* Author: put_your_name_here
   Date created: 2018/03/22
	This is an original work of and owned by your_name, and 	may not be distributed, published or uploaded as your own. 	For any queries regarding code or hardware, contact 	your_email_here.
	This is a modified Traffic signal control, with 3 modes: 	Regular, Pedestrian, Night mode.
	The authority to make changes in the code resides with 	your_name only.
*/