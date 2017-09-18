void setup() 
{
    //Start the serial port at 9600 baud rate.
    Serial.begin(9600);
    //Set pin 13 for output.
    pinMode(13, OUTPUT);
}

void loop() 
{
  //Assing the input value to a variable.
  char input;

  //Read in the characters being sent from Java.
  input = Serial.read();

  //Turn on the LED.
  if(input == '1')
  {
    digitalWrite(13, HIGH);
  }
  
  //Have the LED blink 10 times.
  if(input == '2')
  {
     for(int i = 0; i < 10; i++)
     {
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(100);
     }
  }

  //Turn off the LED.
  if(input == '3')
  {
    digitalWrite(13, LOW);
  }
}


