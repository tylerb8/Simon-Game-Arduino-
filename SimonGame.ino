//Setting the variables
int button[] = {2, 6};     //Digital Outputs for LED (Red = [0] and Green = [1])
int led[] = {3, 7};        //Digital Inputs for LED (Red = [0] and Green = [1])
int tones[] = {262, 392};   //tones to play with each button 

int roundsToWin = 10;         //10 rounds to win 
int buttonSequence[15];       //15 array of combinations

int buzzerPin = 10;           //Digital Outout for speaker

int pressedButton = 2;        
int roundCounter = 1;         //keeps track of what round the player is on


long startTime = 0;           //Initalize timer
long timeLimit = 5000;        //time limit to hit a button

boolean gameStarted = false;      //bool to start game

void setup(){

  pinMode(button[0], INPUT_PULLUP);       //Using built in resistors 
  pinMode(button[1], INPUT_PULLUP);       //Using built in resistors 

  pinMode(led[0], OUTPUT);      //set all of the LED pins to output
  pinMode(led[1], OUTPUT);      //set all of the LED pins to output

  pinMode(buzzerPin, OUTPUT);     //set the buzzer pin to output
}

void loop(){

if (gameStarted == false){    //if the game hasn't started yet
  startSequence();            //flash the start sequence
  roundCounter = 0;           //reset the round counter
  delay(1500);                //wait a second and a half
  gameStarted = true;         //set gameStarted to true to stop loop
}

//each round, start by flashing out the sequence to be repeated
for(int i=0; i <= roundCounter; i++){   //go through array
  flashLED(buttonSequence[i]);          //turn on the LED for that array position and play the sound
  delay(200);                           //wait
  allLEDoff();                          //turn all of the LEDs off
  delay(200);
}

//go through sequence again, track user input
for(int i=0; i <= roundCounter; i++){   //for each button to be pressed in the sequence

  startTime = millis();                 //record the start time

  while(true){  //loop until the player presses a button or the time limit is up

    pressedButton = buttonCheck();      //every loop check to see which button is pressed

    if (pressedButton < 2){             //if a button is pressed...

      flashLED(pressedButton);          //flash the LED for the button that was pressed

      if(pressedButton == buttonSequence[i]){   //if the button matches the button in the sequence
          delay(250);                   //leave the LED light on for a moment
          allLEDoff();                  //then turn off all of the lights and
          break;                        //end the while loop 

      } else{                           //if the button doesn't match the button in the sequence
          loseSequence();               //play the lose sequence 
          break;                        //when the program gets back from the lose sequence, break the while loop so that the game can start over
      }

    } else {                            //if no button is pressed
      allLEDoff();                      //turn all the LEDs off
    }

    if(millis() - startTime > timeLimit){   //if the time limit is up
      loseSequence();                       //play the lose sequence
      break;                                //when the program gets back from the lose sequence, break the while loop so that the game can start over
    }
  }    
}

  roundCounter = roundCounter + 1;      //increase the round number by 1

  if (roundCounter >= roundsToWin){               //if the player has gotten to the 10th round
    winSequence();                      //play the winning song
  }

  delay(500);                           //wait for half a second between rounds


}

//Flash LED
void flashLED (int ledNumber){
  digitalWrite(led[ledNumber], HIGH);
  tone(buzzerPin, tones[ledNumber]);
}

//Turn all LEDS off
void allLEDoff (){
  //turn all the LEDs off
  digitalWrite(led[0],LOW);
  digitalWrite(led[1],LOW);
  noTone(buzzerPin);
}

//Check which button is pressed
int buttonCheck(){
  //check if any buttons are being pressed
  if(digitalRead(button[0]) == LOW){
    return 0;
  }
  else if(digitalRead(button[1]) == LOW){
    return 1;
  }
  else{
    return 2; // No button pressed
  }
}

//Start sequence
void startSequence(){

  randomSeed(analogRead(A0));   // random number

  for (int i=0;i<=roundsToWin;i++){         // populate array with random numbers from 0-1
    buttonSequence[i] = round(random(0,2));
  }

  //flash all of the LEDs when the game starts
  for(int i=0; i<=1; i++){

    tone(buzzerPin, tones[i], 200); //play one of the 2 tones

    //turn all of the leds on
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);

    delay(100);         //wait for a moment

    //turn all of the leds off
    digitalWrite(led[0],LOW);
    digitalWrite(led[1],LOW);

    delay(100);   //wait for a moment

  } //this will repeat 4 times
}

//Win sequence
void winSequence(){

  //turn all the LEDs on
  for(int j=0; j<=1; j++){
    digitalWrite(led[j], HIGH);
  }

  //play the 1Up noise
  tone(buzzerPin, 1318, 150);   //E6
  delay(175);
  tone(buzzerPin, 1567, 150);   //G6
  delay(175);
  tone(buzzerPin, 2637, 150);   //E7
  delay(175);
  tone(buzzerPin, 2093, 150);   //C7
  delay(175);
  tone(buzzerPin, 2349, 150);   //D7
  delay(175);
  tone(buzzerPin, 3135, 500);   //G7
  delay(500);  

  //wait until a button is pressed
  do {         
    pressedButton = buttonCheck();
  } while(pressedButton > 3);
  delay(100);

  gameStarted = false;   //reset the game so that the start sequence will play again.

}

//Lose sequence
void loseSequence(){

  //turn all the LEDs on
  for(int j=0; j<=1; j++){
    digitalWrite(led[j], HIGH);
  }

  //play the 1Up noise
  tone(buzzerPin, 130, 250);   //E6
  delay(275);
  tone(buzzerPin, 73, 250);   //G6
  delay(275);
  tone(buzzerPin, 65, 150);   //E7
  delay(175);
  tone(buzzerPin, 98, 500);   //C7
  delay(500);

  //wait until a button is pressed
  do {         
    pressedButton = buttonCheck();
  } while(pressedButton > 2);
  delay(200);

  gameStarted = false;   //reset the game so that the start sequence will play again.
}
