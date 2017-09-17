#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_RGBLCDShield.h>
#include <Wire.h>

//This Arduino sketch will control a Sous Vide cooker.  Once you have a desired set temperature, let the temperature
//stabalize and throw your vacuum sealed food into the Soud Vide cooker.  The heater will automatically shut off after
//2 hours so if you need to cook something longer you will need to adjust the code below.

//Button Legend:
//Up:         Add 1 degree F to set temperature.
//Down:       Subtract 1 degree F to set temperature.
//Right:      Add 10 degrees F to set temperature.
//Left:       Turn the heater relay off.
//Select:     Start cooking and heating to set temperature.

//Initialize the LCD screen.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

//Define color for LCD screen.

#define WHITE 0x7

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 12 // Lower resolution

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//Global variables
float setTemp = 75;
float tempPercent;
float tempF;
float cookTime;
//int startTime;

void setup(void)
{
  // start serial port
  Serial.begin(9600);

  //Start the LCD library.
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Sous Vide");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Press a button");

  // Start up the library for the temperature sensor.
  sensors.begin();

  //Initial relay pin and pull the resistor high.
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void getTemp()
{
  //Set the thermocouple resolution.
  sensors.setResolution(12);
  //Call sensors.requestTemperatures() to issue a global temperature.
  sensors.requestTemperatures(); 
  //Assign the sensor reading to a field.
  tempF = sensors.getTempFByIndex(0);
}

//Turns the heater on.
void relayOn()
{
  digitalWrite(13, LOW);
}

//Turns the heater off.
void relayOff()
{
  digitalWrite(13, HIGH);
}

//Creates a start time to monitor how long this has been running below.
int startTime()
{
  int startTime = millis();
  return startTime;
}

//Main loop.
void loop (void)
{
  //Grab the temperature.
  getTemp();
  
  //Buttons to control temperature.
  uint8_t buttons = lcd.readButtons();

  //Increase set temperature.
  if(buttons & BUTTON_UP)
  {
    //Turn the relay off.
    relayOff();

    //Increase temperature by 1 degree.
    setTemp ++;

    //Set the LCD screen.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set temp: ");
    lcd.print(setTemp);
    lcd.print("F");
    lcd.setCursor(0,1);
    lcd.print("Current:  ");
    lcd.print(tempF);
    lcd.print("F");

  }

  //Decrease set temperature.
  if(buttons & BUTTON_DOWN)
  {
    //Turn the relay off.
    relayOff();

    //Decrese the temperature by 1 degree.
    setTemp --;

    //Set the LCD screen.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set temp: ");
    lcd.print(setTemp);
    lcd.print("F");
    lcd.setCursor(0,1);
    lcd.print("Current:  ");
    lcd.print(tempF);
    lcd.print("F");
  }

  //Power off.
  if(buttons & BUTTON_LEFT)
  {
    //Turn the relay off.
    relayOff();

    //Set the LCD screen.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Heater off.");
    lcd.setCursor(0,1);
    lcd.print("Current:  ");
    lcd.print(tempF);
    lcd.print("F");
  }

  //Add 10 degrees to set temp.
  if(buttons & BUTTON_RIGHT)
  {
    //Turn the relay off.
    relayOff();

    //Increase the temperature by 10.
    setTemp = setTemp + 10;

    //Set the lcd screen.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set temp: ");
    lcd.print(setTemp);
    lcd.print("F");
    lcd.setCursor(0,1);
    lcd.print("Current:  ");
    lcd.print(tempF);
    lcd.print("F");
  }

  //Turns relay on and goes for selected cooking temp.  Shuts off after 2 hours run time.
  if(buttons & BUTTON_SELECT)
  {
    //Set the LCD screen.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Start Cooking");
    delay(3000);

    //Update LCD screen with temperatures.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cook @: ");
    lcd.print(setTemp);
    lcd.print("F");
    lcd.setCursor(0,1);
    lcd.print("Current:  ");
    lcd.print(tempF);
    lcd.print("F");

    //Fail safe to only have the heater on for 2 hours.
    while((startTime() - millis()) < 7200000)
    {
      //Turn the heater on.
      relayOn();

      //If temperature goes over set temp.
      if(tempF > setTemp)
      {
        //Turn the relay off.
        relayOff();
      }
    }
      //Turn the relay off if temp is on for over 2 hours.
      relayOff();
  }
}
