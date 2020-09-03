//Setting variables
int button[] = {2, 6};       //Digital pin Outputs for LED (Red = [0] and Green = [1])
int led[] = {3, 7};          //Digital pin Inputs for LED (Red = [0] and Green = [1])
int tones[] = {262, 392};    //tones corresponding to each LED

int ToWin = 10;              //10 rounds to win 
int buttonSequence[15];      //15 array of combinations

int buzzerPin = 10;          //Digital pin Outout for speaker

int pressedButton = 2;        
int roundCounter = 1;        //round tracker

long startTime = 0;          //Initalize timer
long timeLimit = 5000;       //time limit to push button

boolean gameStart = false;   //bool to check if game started




void setup() 
{
  pinMode(button[0], INPUT_PULLUP);       //Using built in arduino pullup resistors 
  pinMode(button[1], INPUT_PULLUP);       //Using built in arduino pullup resistors 

  pinMode(led[0], OUTPUT);      //set RED LED pin to output
  pinMode(led[1], OUTPUT);      //set GREEN LED pin to output

  pinMode(buzzerPin, OUTPUT);     //set the buzzer pin to output
}




void loop()
{
  if (gameStart == false)       //if the game didn't start
  {    
    StartCycle();               //Go through start cycle function
    roundCounter = 0;           //reset the round counter
    delay(1500);                //delay 
    gameStart = true;           //game has started (break loop)
  }

  //each round, start by flashing out the sequence to be repeated
  for(int i = 0; i <= roundCounter; i++)  //go through array
  {   
    flashLED(buttonSequence[i]);          //turn on the LED for that array position
    delay(200);                           //delay
    allLEDoff();                          //turn all of the LEDs off
    delay(200);                           //delay
  }

  //go through sequence again, track user input
  for(int i = 0; i <= roundCounter; i++)    //go through array
  {   
    startTime = millis();                   //track time in miliseconds

    while(true)                            //loop till button or time limit has been reached
    {                         
      pressedButton = buttonCheck();      //every loop check to see which button is pressed

      if (pressedButton < 2)      //if a button is pressed...
      {             
        flashLED(pressedButton);          //flash the LED for the button that was pressed

        if(pressedButton == buttonSequence[i])    //if the button matches the button in the sequence
        {  
          delay(250);                   //delay
          allLEDoff();                  //turn off all LEDS
          break;                        //break
        } 

        else                            //if wrong button pressed
        {                           
          loseSequence();               //play the lose sequence 
          break;                        //break 
        }
      } 
      
      else 
      {                                 //if no button is pressed
        allLEDoff();                    //turn all the LEDs off
      }

      if(millis() - startTime > timeLimit) //if the time limit is up
      {  
        loseSequence();                       //play the lose sequence
        break;                                //break program
      } 
    }    
  } 

  roundCounter = roundCounter + 1;      //round counter increase by 1

  if (roundCounter >= ToWin)            //if the player has gotten to the 10th round
  {
    winSequence();                      //play the winning song
  }

  delay(500);                           //delay
}

//Flash LED
void flashLED (int ledNumber)
{   
  digitalWrite(led[ledNumber], HIGH);     //Turn on LED
  tone(buzzerPin, tones[ledNumber]);      //play tone 
}

//Turn all LEDS off
void allLEDoff ()
{
  //turn all the LEDs off
  digitalWrite(led[0],LOW);  
  digitalWrite(led[1],LOW);
  noTone(buzzerPin);
}

//Check which button is pressed
int buttonCheck()
{
  //check if any buttons are being pressed
  if(digitalRead(button[0]) == LOW)
  {
    return 0;
  }
  else if(digitalRead(button[1]) == LOW)
  {
    return 1;
  }
  else
  {
    return 2; // No button pressed
  }
}

//Start sequence
void StartCycle()
{

  randomSeed(analogRead(A0));   // random number

  for (int i=0;i<=ToWin;i++)         // populate array with random numbers from 0-1 (RED and GREEN)
  {
    buttonSequence[i] = round(random(0,2));
  }

  for(int i=0; i<=1; i++)       //flash all of the LEDs when the game starts and tones
  {
    tone(buzzerPin, tones[i], 200); //play tones (2x Red and Green)

    //turn all of the leds on
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);

    delay(100);         //delay

    //turn all of the leds off
    digitalWrite(led[0],LOW);
    digitalWrite(led[1],LOW);

    delay(100);   //delay
  }
}

//Win sequence
void winSequence()
{
  //turn all the LEDs on
  for(int j=0; j<=1; j++)
  {
    digitalWrite(led[j], HIGH);
  }

  //win song
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
  do 
  {         
    pressedButton = buttonCheck();
  } 
  
  while(pressedButton > 2);

  delay(100);

  gameStart = false;   //reset the game
}

//Lose sequence
void loseSequence()
{
  //turn all the LEDs on
  for(int j=0; j<=1; j++)
  {
    digitalWrite(led[j], HIGH);
  }

  //lose song
  tone(buzzerPin, 130, 250);   //E6
  delay(275);
  tone(buzzerPin, 73, 250);   //G6
  delay(275);
  tone(buzzerPin, 65, 150);   //E7
  delay(175);
  tone(buzzerPin, 98, 500);   //C7
  delay(500);

  //wait until a button is pressed
  do
  {         
    pressedButton = buttonCheck();
  } 

  while(pressedButton > 2);

  delay(200);
  
  gameStart = false;   //reset the game
}
