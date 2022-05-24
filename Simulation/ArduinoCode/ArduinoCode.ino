

int sensorA = 12; // Initialize Pin 3 for IR sensor A
int sensorB = 11; // initialize pin 2 for IR sensor B
unsigned long t1 = 0; // Define Time1 Variable
unsigned long t2 = 0; // Define Time2 Variable
float speed;  // Define Speed variable
int i = 0;
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
String stringToPy = "";
SoftwareSerial virtualPort(9, 10);

#include <TinyGPS.h>


LiquidCrystal lcd(8, 7, 6, 5, 4, 3);


TinyGPS gps;


void setup()
{
  Serial.begin(9600);
  virtualPort.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("-Vehicle Routing-");
  lcd.setCursor(0, 1);
  lcd.print("-Monitor sys-");
  delay(500);
  pinMode(sensorA, INPUT); // Define IR SensorA pin as Input
  pinMode(sensorB, INPUT); // Define IR SensorB pin as Input
}

void loop()
{


  Serial.println("");
  Serial.println("SpeedMeter wait to be activated");
  while (digitalRead(sensorA)); // Read IR SensorA
  while (digitalRead(sensorA) == 0);
  t1 = millis(); // Record Time1
  while (digitalRead(sensorB)); // Read IR SensorA
  t2 = millis(); // Record Time2
  speed = t2 - t1;
  speed = speed / 1000; //convert millisecond to second
  speed = (5.0 / speed); //v=d/t
  speed = speed * 3600; //multiply by seconds per hr
  speed = speed / 1000; //division by meters per Km
  for (int i = 2; i > 0; i--)
  {
    Serial.print(speed);
    Serial.println(" Km/hr");
  }




  stringToPy.concat(speed);
  stringToPy = stringToPy + "xx";

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" ---Speed ---");
  lcd.setCursor(2, 1);
  lcd.print(speed);
  lcd.setCursor(8, 1);
  lcd.print(" Km/hr");

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    { char c = Serial.read();

      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    lcd.clear();
    lcd.setCursor(0, 0);
    stringToPy.concat(flat);
    stringToPy = stringToPy + "xx";
    lcd.print("LAT:");
    Serial.print("LAT:");
    Serial.println(flat);
    lcd.print(flat, 5);
    lcd.setCursor(0, 1);
    lcd.print("LON:");
    Serial.print("LON:");
    Serial.println(flon);
    stringToPy.concat(flon);
    stringToPy = stringToPy + "xx";
    lcd.print(flon, 5);


  }
  if (!newData)
  {
    float flat = 0;
    float flon = 0;
    stringToPy.concat(flat);
    stringToPy = stringToPy + "xx";
    stringToPy.concat(flon);
    stringToPy = stringToPy + "xx";
  }


  gps.stats(&chars, &sentences, &failed);
  delay(100);
  Serial.print("Str send to Python script: ");
  Serial.println(stringToPy);
  virtualPort.println(stringToPy);
  stringToPy = "";
}
