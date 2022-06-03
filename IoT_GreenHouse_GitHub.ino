////////////////////////////////  Library  ////////////////////////////////

//////  MQTT SERVER  //////
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YourOwnSSID";
const char* password = "YourOwnPASSWORD";
const char* mqttServer = "YourOwnIP";
const int mqttPort = 1883;
const char* mqttUser = "YourOwnUSERNAME";
const char* mqttPassword = "YourOwnPASSWORD";
const char* clientID = "client_livingroom";

const char* temperature_topic_Ground = "GreenHouse/ESP32/temperatureGround";
const char* moisture_topic_Ground = "GreenHouse/ESP32/moistureGround";
const char* temperature_topic_Surrounding = "GreenHouse/ESP32/temperatureSurrounding";
const char* humidity_topic_Surrounding = "GreenHouse/ESP32/humiditySurrounding";

WiFiClient espClient;
PubSubClient client(espClient);

////// LCD //////

#include <Wire.h>                                                    // Library voor het LCD scherm.
#include <LiquidCrystal_I2C.h>                                       // Library voor het LCD scherm.
LiquidCrystal_I2C lcd(0x27, 16, 2);                                  // Library voor het LCD scherm.

/// RFID Reader ///

#include <MFRC522.h>                                                 // Library voor de RFID - Reader.
#define SS_PIN 5                                                     // Aansluiting RFID SDA      Mosi -> pin D23.
#define RST_PIN 22                                                   // Aansluiting RFID RST      Miso -> pin D19.
MFRC522 mfrc522(SS_PIN, RST_PIN);                                    // Create MFRC522 instance.

////// Ground sensor DS18B20 //////

#include <OneWire.h>                                                 // Library voor de grondsensor DS18B20
#include <DallasTemperature.h>                                       // Library voor de grondsensor DS18B20
#define SENSOR_PIN  4                                                // ESP32 pin GIOP4 connected to DS18B20 sensor's DQ pin
OneWire oneWire(SENSOR_PIN);                                         // Library voor de grondsensor DS18B20
DallasTemperature DS18B20(&oneWire);                                 // Library voor de grondsensor DS18B20
float tempground;                                                    // Memory voor de grondsensor DS18B20
float tempGround;                                                    // Memory voor de grondsensor DS18B20

////// DHT22 Sensor //////

#include <Arduino.h>                                                 // Library voor sensor DHT22                     
#include <DHT.h>                                                     // Library voor sensor DHT22 
DHT my_sensor(33, DHT22);                                            // DHT22 sensor op pin 33
float temperature, humidity;                                         // Memory voor de temperatuur en humidity van de DHT22 sensor.

////// Soil Moisture Sensor //////

#define soilPin 35                                                   // Moisture sensor op pin 35
//int soilThresholdValue = 350;                                      // you can adjust the threshold value, 0 - 4095 (12 bits), lower value is wetter.

////// Task //////

#include <TaskScheduler.h>

void turnonledStrip();
void turnoffledStrip();

Task onTask( TASK_SECOND * 20, TASK_FOREVER, &turnonledStrip);

int wachtTijd = 0;
int ledStrip = 0;

Scheduler runner;

////// PINS AND EXTRA'S //////

#define Waterpump 14                                                 // Waterpump op pin 14
#define Heatplate 13                                                 // Heatplate op pin 13
#define Light 12                                                     // Light op pin 12

#define Led_Waterpump 27                                             // Red led op pin 27
#define Led_Heatplate 26                                             // Yellow led op pin 26
#define Led_Window 32                                                // Green led op pin 32

int Basilicum = 0;                                                   // Memory voor de settings van Basilicum
int GreenMint = 0;                                                   // Memory voor de settings van GreenMint


////////////////////////////////   Setup   ////////////////////////////////
void setup()
{
  Serial.begin(115200);                                              // Serial print opstarten
  WiFi.begin(ssid, password);                                        // Wifi starten

  while (WiFi.status() != WL_CONNECTED)                              // Wifi connecteren
  {
    delay(500);                                                      // Wifi connecteren
    Serial.println("Connecting to WiFi..");                          // Wifi connecteren
  }
  Serial.println("Connected to the WiFi network!");                  // Wifi connecteren

  client.setServer(mqttServer, mqttPort);                            // MQTT connectie starten

  delay(1000);
  Stippelijn();                                                      // Toont een stippenlijn op de lcd door de fuctie "stippelijn"
  Serial.println("    End project: Iot Greenhouse");                 // Weergeeft op de serial print: "End project: Iot Greenhouse"
  Stippelijn();                                                      // Toont een stippenlijn op de lcd door de fuctie "stippelijn"
  delay(1000);                                                       // Delay tussen de regels
  Serial.println("*Sensors are warming up, wait a second please*");  // Weergeeft op de serial print: "*Sensors are warming up, wait a second please*"
  Serial.println(" ");
  delay(1000);                                                       // Delay tussen de regels

  lcd.begin();                                                       // Lcd display start scherm
  lcd.backlight();                                                   // Lcd display start scherm

  lcd.begin();                                                       // Lcd display start scherm
  lcd.backlight();                                                   // Lcd display start scherm
  lcd.setCursor(1, 0);                                               // Lcd display start scherm
  lcd.print("IoT GreenHouse");                                       // Lcd display start scherm
  lcd.setCursor(4, 1);                                               // Lcd display start scherm
  lcd.print("By Senne ");                                            // Lcd display start scherm
  delay(10000);                                                      // Lcd display start scherm
  lcd.clear();                                                       // Lcd display start scherm
  lcd.setCursor(0, 0);                                               // Lcd display start scherm
  lcd.print("...Prepairing...");                                     // Lcd display start scherm
  lcd.setCursor(2, 1);                                               // Lcd display start scherm
  lcd.print("Wait please");                                          // Lcd display start scherm
  delay(5000);                                                       // Lcd display start scherm
  lcd.clear();                                                       // Lcd display start scherm

  SPI.begin();                                                       // Initiate  SPI bus
  mfrc522.PCD_Init();                                                // Initiate MFRC522

  DS18B20.begin();                                                   // initialize the DS18B20 sensor

  my_sensor.begin();                                                 // initialize the DHT22 sensor

  runner.init();
  Serial.println("Initialized scheduler");

  runner.addTask(onTask);
  Serial.println("added onTask");

  onTask.enable();

  pinMode(soilPin, INPUT);                                           // initialize the Moisture sensor

  pinMode(Waterpump, OUTPUT);                                        // Waterpump tot een output maken
  pinMode(Heatplate, OUTPUT);                                        // Heatplate tot een output maken
  pinMode(Light, OUTPUT);                                            // Light tot een output maken

  pinMode(Led_Waterpump, OUTPUT);                                    // Led_Waterpump tot een output maken
  pinMode(Led_Heatplate, OUTPUT);                                    // Led_Heatplate tot een output maken
  pinMode(Led_Window, OUTPUT);                                       // Led_Window tot een output maken
}


void loop() {

  client.loop();
  turnonledStrip();

  while (!client.connected()) {
    Serial.println ("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword ))
    {
      Serial.println("connected ");
      Serial.println(" ");
    } else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  DS18B20.requestTemperatures();                                      // send the command to get temperatures
  tempground = DS18B20.getTempCByIndex(0);                            // read temperature in °C
  String tempGround = String ((float)tempground);

  int soilVal = analogRead(soilPin);                                  // read the input on analog pin 35 (ADC 1 Channel 7):
  soilVal = map(soilVal, 10, 550, 0, 100);
  String moisture = String (float(soilVal));

  float Humidity = my_sensor.readHumidity();
  String luchtvochtigheid = String(Humidity);

  float Temperature = my_sensor.readTemperature();
  String graden = String(Temperature);

  turnonledStrip();
  RFID_Reader();
  if (Basilicum == 1 && GreenMint == 0)
  {
    MoisterSensor_Basilicum();
  }

  if (GreenMint == 1 && Basilicum == 0)
  {
    MoisterSensor_GreenMint();
  }

  turnonledStrip();
  TempGround();
  TemperatureAndHumidity();

  lcd.clear();
  lcd.setCursor(0, 0);                                                // Lcd display
  lcd.print("Temp out: ");                                            // Lcd display
  lcd.setCursor(10, 0);                                               // Lcd display
  lcd.print(graden);                                                  // Lcd display
  lcd.setCursor(0, 1);                                                // Lcd display
  lcd.print("Humi out: ");                                            // Lcd display
  lcd.setCursor(10, 1);                                               // Lcd display
  lcd.print(luchtvochtigheid);                                        // Lcd display
  delay(2000);                                                        // Lcd display
  lcd.clear();                                                        // Lcd display

  RFID_Reader();
  if (Basilicum == 1 && GreenMint == 0)
  {
    MoisterSensor_Basilicum();
  }

  if (GreenMint == 1 && Basilicum == 0)
  {
    MoisterSensor_GreenMint();
  }

  turnonledStrip();
  TempGround();
  TemperatureAndHumidity();

  lcd.setCursor(0, 0);                                                // Lcd display start scherm
  lcd.print("Temp Gnd:");                                             // Lcd display start scherm
  lcd.setCursor(10, 0);                                               // Lcd display start scherm
  lcd.print(tempGround);                                              // Lcd display start scherm
  lcd.setCursor(3, 1);                                                // Lcd display start scherm
  lcd.print("Moist:");                                                // Lcd display start scherm
  lcd.setCursor(10, 1);                                               // Lcd display start scherm
  lcd.print(soilVal);                                                 // Lcd display start scherm
  delay(2000);                                                        // Lcd display start scherm
  lcd.clear();                                                        // Lcd display start scherm

  RFID_Reader();
  if (Basilicum == 1 && GreenMint == 0)
  {
    MoisterSensor_Basilicum();
  }

  if (GreenMint == 1 && Basilicum == 0)
  {
    MoisterSensor_GreenMint();
  }
  
  Serial.println(" ");
  Serial.println(" -<><><>- Gemeten waardes -<><><>- ");
  Serial.println(" ");
  
  client.publish(temperature_topic_Ground, tempGround.c_str());  
  Serial.print(" - Grond temperatuur: ");
  Serial.println(tempGround);
  Serial.println(" ");

  client.publish(moisture_topic_Ground, moisture.c_str());
  Serial.print(" - Grond vochtigheid: ");
  Serial.println(soilVal);
  Serial.println(" ");

  if (soilVal > 350) {
    Serial.println("!!!   Time to water your plant   !!!");
    Serial.println(" ");
  }

  client.publish(temperature_topic_Surrounding, graden.c_str());
  Serial.print(" - Temperatuur omgeving: ");
  Serial.println(temperature);
  Serial.println(" ");

  client.publish(humidity_topic_Surrounding, luchtvochtigheid.c_str());
  Serial.print(" - Humidity omgeving: ");
  Serial.println(humidity);
  Serial.println(" ");

  delay(100);
}


////////////////////////////////  Functie  ////////////////////////////////

void Stippelijn()                                                     // Fuctie stippelijn
{
  Serial.println("<><><><><><><><><><><><><><><><><><>");             // Fuctie stippelijn
}

void RFID_Reader() {

  if ( ! mfrc522.PICC_IsNewCardPresent())                             // Look for new cards
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial())                               // Select one of the cards
  {
    return;
  }

  Serial.print("UID tag :");                                          // Show UID on serial monitor
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.println("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "97 30 5E C6")                          //change here the UID of the card/cards that you want to give access
  {
    Basilicum = 1;
    GreenMint = 0;
    Serial.println(" ");
    Serial.println("-- Settings for Basilicum --");
    Serial.println(" ");
    Serial.println("- Moister sensor under 400         --->  Waterpump on!!");
    Serial.println("- Temperature ground under 18°C    --->  Heatplate on!!");
    Serial.println("- DHT22 Temp higher than 25°C      --->  Window Opens!!");
    Serial.println("- DHT22 Humidity higher than 50%   --->  Window Opens!!");
    Serial.println(" ");

    lcd.setCursor(1, 0);                                                 // Lcd display RFID alert Basilicum
    lcd.print("- RFID ALERT -");                                         // Lcd display RFID alert Basilicum
    lcd.setCursor(3, 1);                                                 // Lcd display RFID alert Basilicum
    lcd.print("Basilicum");                                              // Lcd display RFID alert Basilicum
    delay(1000);                                                         // Lcd display RFID alert Basilicum
    lcd.clear();                                                         // Lcd display RFID alert Basilicum
  }

  if (content.substring(1) == "D9 FA 5D E4")
  {
    Basilicum = 0;
    GreenMint = 1;

    Serial.println(" ");
    Serial.println("-- Settings for Green Mint --");
    Serial.println(" ");
    Serial.println("- Moister sensor under 350         --->  Waterpump on!!");
    Serial.println("- Temperature ground under 18°C    --->  Heatplate on!!");
    Serial.println("- DHT22 Temp higher than 25°C      --->  Window Opens!!");
    Serial.println("- DHT22 Humidity higher than 50%   --->  Window Opens!!");
    Serial.println(" ");

    lcd.setCursor(1, 0);                                              // Lcd display start scherm
    lcd.print("- RFID ALERT -");                                      // Lcd display start scherm
    lcd.setCursor(3, 1);                                              // Lcd display start scherm
    lcd.print("Green Mint");                                          // Lcd display start scherm
    delay(1000);                                                      // Lcd display start scherm
    lcd.clear();                                                      // Lcd display start scherm
  }
}

void MoisterSensor_Basilicum() {

  int soilVal = analogRead(soilPin);
  soilVal = map(soilVal, 10, 550, 0, 100);

  if (soilVal > 400) {
    digitalWrite(Waterpump, HIGH);
    digitalWrite(Led_Waterpump, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("!Sensor warning!");
    lcd.setCursor(2, 1);                                               // Lcd display start scherm
    lcd.print("Ground to dry");                                        // Lcd display start scherm
    delay(2500);                                                       // Lcd display start scherm
    lcd.clear();                                                       // Lcd display start scherm

    delay(500);
  } else
  {
    digitalWrite(Waterpump, LOW);
    digitalWrite(Led_Waterpump, LOW);
    delay(500);
  }
}

void MoisterSensor_GreenMint() {

  int soilVal = analogRead(soilPin);                                  // read the input on analog pin 35 (ADC 1 Channel 7):
  soilVal = map(soilVal, 10, 550, 0, 100);

  if (soilVal > 100) {
    //digitalWrite(Waterpump, HIGH);
    digitalWrite(Led_Waterpump, HIGH);
    digitalWrite(Led_Heatplate, HIGH);
    digitalWrite(Led_Window, HIGH);
    
    lcd.setCursor(0, 0);
    lcd.print("!Sensor warning!");
    lcd.setCursor(2, 1);                                               // Lcd display start scherm
    lcd.print("Ground to dry");                                        // Lcd display start scherm
    delay(2500);                                                       // Lcd display start scherm
    lcd.clear();                                                       // Lcd display start scherm

    delay(500);
  } else
  {
    digitalWrite(Waterpump, LOW);
    digitalWrite(Led_Waterpump, LOW);
    delay(500);
  }
}
void TempGround() {

  if (tempground <= 18)
  {
    digitalWrite(Heatplate, HIGH);
    digitalWrite(Led_Heatplate, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("!Sensor warning!");
    lcd.setCursor(1, 1);                                                // Lcd display start scherm
    lcd.print("Ground to cold");                                        // Lcd display start scherm
    delay(2500);                                                        // Lcd display start scherm
    lcd.clear();                                                        // Lcd display start scherm

  } else
  {
    digitalWrite(Heatplate, LOW);
    digitalWrite(Led_Heatplate, LOW);
  }
}

void TemperatureAndHumidity() {

  if (humidity >= 70 || temperature >= 25 )
  {
    lcd.setCursor(0, 0);
    lcd.print("!Sensor warning!");
    lcd.setCursor(1, 1);                                                // Lcd display start scherm
    lcd.print("To cold or wet");                                        // Lcd display start scherm
    delay(2500);                                                        // Lcd display start scherm
    lcd.clear();                                                        // Lcd display start scherm

    digitalWrite(Led_Window, HIGH);
  } else
  {
    digitalWrite(Led_Window, LOW);
  }
}

void turnonledStrip()
{
  if (ledStrip == 0 & (millis() - wachtTijd) > 20000)
  {
    Serial.println("Task1: ledStrip is AAN!!");
    digitalWrite(Light, HIGH);
    wachtTijd = millis();
    ledStrip = 1;
  }

  if (ledStrip == 1 & (millis() - wachtTijd) > 20000)
  {
    Serial.println("Task2: ledStrip is UIT!!");
    digitalWrite(Light, LOW);
    wachtTijd = millis();
    ledStrip = 0;
  }
}
