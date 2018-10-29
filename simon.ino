//here we initialize the variables for each pin to be able to access them easily
int boto1 = 2;
int boto2 = 3;
int boto3 = 4;
int boto4 = 5;
int boto5 = 6;

int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int led5 = 12;

//here we initialize an array with 100 empty cells, where the sequence will be contained, a variable called tamany to know the size of the array and a variable called actual which we'll use later.

int sequence[100];
int tamany = 0;
int actual;
bool released;

void setup() {
  //here we set every pin to its required mode
  pinMode(boto1, INPUT);
  pinMode(boto2, INPUT);
  pinMode(boto3, INPUT);
  pinMode(boto4, INPUT);
  pinMode(boto5, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  //here we initialize serial connections
  Serial.begin(9600);

  //randomSeed is used to make the random() function give a different sequence every time
  randomSeed(analogRead(5));

  //we fill the first index of the array with a random number to start the game
  sequence[0] = random(1, 6);
}

void loop() {
  //demonstration phase. the user is shown the full sequence. the following loop goes through every item until it reaches tamany, which is the length of the array.
  for (int i = 0; i <= tamany; i++) {
    switch (sequence[i]) {
      case 1:
        digitalWrite(led1, HIGH);
        break;
      case 2:
        digitalWrite(led2, HIGH);
        break;
      case 3:
        digitalWrite(led3, HIGH);
        break;
      case 4:
        digitalWrite(led4, HIGH);
        break;
      case 5:
        digitalWrite(led5, HIGH);
        break;
    }
    delay(700);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    delay(500);
  }
  //test phase. the user is tested for the sequence. the following loop is similarly repeated until it reaches tamany.
  for (int i = 0; i <= tamany; i++) {
    actual = 0;
    //this loop repeats until a button is pressed, its led is turned on, and its value is assigned to actual.
    while (actual == 0) {
      if (digitalRead(boto1) == LOW) {
        actual = 1;
        digitalWrite(led1, HIGH);
        break;
      }
      if (digitalRead(boto2) == LOW) {
        actual = 2;
        digitalWrite(led2, HIGH);
        break;
      }
      if (digitalRead(boto3) == LOW) {
        actual = 3;
        digitalWrite(led3, HIGH);
        break;
      }
      if (digitalRead(boto4) == LOW) {
        actual = 4;
        digitalWrite(led4, HIGH);
        break;
      }
      if (digitalRead(boto5) == LOW) {
        actual = 5;
        digitalWrite(led5, HIGH);
        break;
      }
    }

    //the following loop repeats until a button is released, to allow for longer and shorter presses. the switch..case    function is used to avoid non-pressed buttons from triggering it.
    released = false;
    while (!released) {
      switch (actual) {
        case 1:
          if (digitalRead(boto1) == HIGH) {
            released = true;
          }
        case 2:
          if (digitalRead(boto2) == HIGH) {
            released = true;
          }
        case 3:
          if (digitalRead(boto3) == HIGH) {
            released = true;
          }
        case 4:
          if (digitalRead(boto4) == HIGH) {
            released = true;
          }
        case 5:
          if (digitalRead(boto5) == HIGH) {
            released = true;
          }
      }
    }

    //debounce and turn off leds.
    delay(250);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);

//check if button pressed is equal to current index in sequence array
    if (actual == sequence[i] && i == tamany) {
      randomSeed(analogRead(5));

      //add new number at the end of array
      sequence[i + 1] = random(1, 6);
      tamany = tamany + 1;
      Serial.print("NIVELL ");
      Serial.println(tamany);
      
      //blink all leds.
      for (int i = 0; i < 3; i++) {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        digitalWrite(led5, HIGH);
        delay(150);
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
        delay(150);
      }

      //binary counter
      for (int i = 0; i < 4; i++) {
        if ((tamany % 2) > 0) {
          digitalWrite(led1, HIGH);
        } else {
          digitalWrite(led1, LOW);
        }

        if ((tamany % 4) > 1) {
          digitalWrite(led2, HIGH);
        } else {
          digitalWrite(led2, LOW);
        }

        if ((tamany % 8) > 3) {
          digitalWrite(led3, HIGH);
        } else {
          digitalWrite(led3, LOW);
        }

        if ((tamany % 16) > 7) {
          digitalWrite(led4, HIGH);
        } else {
          digitalWrite(led4, LOW);
        }

        if ((tamany % 32) > 15) {
          digitalWrite(led5, HIGH);
        } else {
          digitalWrite(led5, LOW);
        }
        delay(100);
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
        delay(100);
      }
      delay(300);
      break;
    }

    //if wrong, blink until infinity
    else if (actual != sequence[i]) {
      while (1) {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
        delay(250);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        digitalWrite(led5, HIGH);
        delay(250);
      }
    }
  }
}
