#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "ThingSpeak.h"
SoftwareSerial gprsSerial(2,15);
SoftwareSerial mySerial(2,15);
 
#include <String.h>

int buzer = 14;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//float latref = 0.328469;
//float lonref = 32.570221;

float latref = 0.33116;
float lonref = 32.57029;
float safedistance = 70;

const char* ssid = "Galaxy_S10fd5d";   // your network SSID (name) 
const char* password = "09876543210123";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1623384;
const char * myWriteAPIKey = "SHKBH03IXH52SA5I";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

// variables for GPS cordinates 
float field1;
float field2;

static const int RXPin = 33, TXPin = 25;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);



void setup()
{
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);
  delay(5000);
  WiFi.disconnect();
  
  Serial.begin(9600);
  ss.begin(GPSBaud);
gprsSerial.begin(9600);

  
pinMode(buzer, OUTPUT);
digitalWrite(buzer, 0);
display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
 




//   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//    Serial.println(F("SSD1306 allocation failed"));
//    for(;;); // Don't proceed, loop forever
//  }

}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
     

      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
//float distance(float x, float y)
//{
// float dx = x - latref;  
// float dy = y - lonref;
// float d2x = sq(dx);
// float d2y = sq(dy);
// float sum = (d2x + d2y);
// float d = sqrt(sum);
// d = d * 1000;
// return d;
//}

float distance(float lat2, float lon2)
{
  float lat1 = latref; 
  float lon1 = lonref;
  float ToRad = PI / 180.0;
  float R = 6378140;   // radius earth in Km is 6371
  
  float dLat = (lat2-lat1) * ToRad;
  float dLon = (lon2-lon1) * ToRad; 
  
  float a = sin(dLat/2) * sin(dLat/2) +
        cos(lat1 * ToRad) * cos(lat2 * ToRad) * 
        sin(dLon/2) * sin(dLon/2); 
        
  float c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  
  float d = R * c;
  return d;
}
void displayInfo()
{

  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {


    
     float m = distance(gps.location.lat(),gps.location.lng());
     Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);

Serial.print(m);

  
    
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(5,0);             // Start at top-left corner
  display.println("distance");


  display.setCursor(0,10);
  display.setTextSize(1);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(m);

  display.display();
  delay(500);

     if (m > 5){
                  if(m>safedistance) {
                 display.clearDisplay();
                 display.setTextSize(1);             // Normal 1:1 pixel scale
                  display.setTextColor(SSD1306_WHITE);        // Draw white text
                  display.setCursor(5,0);             // Start at top-left corner
                  display.println("iam lost");
                
                    display.setCursor(0,10);
                  display.setTextSize(1);             // Draw 2X-scale text
                  display.setTextColor(SSD1306_WHITE);
                  display.print("call 07073452");
                  
                  display.setCursor(0,20);
                  display.setTextSize(1);             // Draw 2X-scale text
                  display.setTextColor(SSD1306_WHITE);
                  display.print(m);
                
                  display.setCursor(0,25);
                  display.setTextSize(1);             // Draw 2X-scale text
                  display.setTextColor(SSD1306_WHITE);
                  display.print("m");
                  
                  display.display();
                digitalWrite(buzer, 1);
                delay(100);
                digitalWrite(buzer, 0);
                delay(100);
                digitalWrite(buzer, 1);
                delay(100);
                digitalWrite(buzer, 0);
                delay(100);
                digitalWrite(buzer, 1);
                delay(100);
                digitalWrite(buzer, 0);
                delay(100);
                digitalWrite(buzer, 1);
                delay(100);
                digitalWrite(buzer, 0);
                delay(100);
                digitalWrite(buzer, 1);
                delay(100);
                digitalWrite(buzer, 0);
                delay(100);
                digitalWrite(buzer, 1);
                delay(100);
                digitalWrite(buzer, 0);
                delay(100);
                digitalWrite(buzer, 1);
                delay(100);
                digitalWrite(buzer, 0);
                delay(1000);
                  }

//   if (gprsSerial.available())
//    Serial.write(gprsSerial.read());
// 
//  gprsSerial.println("AT");
//  delay(1000);
// 
//  gprsSerial.println("AT+CPIN?");
//  delay(1000);
// 
//  gprsSerial.println("AT+CREG?");
//  delay(1000);
// 
//  gprsSerial.println("AT+CGATT?");
//  delay(1000);
// 
//  gprsSerial.println("AT+CIPSHUT");
//  delay(1000);
// 
//  gprsSerial.println("AT+CIPSTATUS");
//  delay(2000);
// 
//  gprsSerial.println("AT+CIPMUX=0");
//  delay(2000);
// 
//  ShowSerialData();
// 
//  gprsSerial.println("AT+CSTT=\"internet\"");//start task and setting the APN,
//  delay(1000);
// 
//  ShowSerialData();
// 
//  gprsSerial.println("AT+CIICR");//bring up wireless connection
//  delay(3000);
// 
//  ShowSerialData();
// 
//  gprsSerial.println("AT+CIFSR");//get local IP adress
//  delay(2000);
// 
//  ShowSerialData();
// 
//  gprsSerial.println("AT+CIPSPRT=0");
//  delay(3000);
// 
//  ShowSerialData();
//  
//  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
//  delay(6000);
// 
//  ShowSerialData();
// 
//  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
//  delay(2000);
//  ShowSerialData();
//  
//  String str="GET https://api.thingspeak.com/update?api_key=SHKBH03IXH52SA5I&field1=" + String(gps.location.lat(),6) +"&field2="+String(gps.location.lng(),6);
//  //String str="GET https://api.thingspeak.com/update?api_key=SHKBH03IXH52SA5I&field1=" + String(latref) +"&field2="+String(lonref);
//  Serial.println(str);
//  gprsSerial.println(str);//begin send data to remote server
//  
//  delay(3000);
//  ShowSerialData();
// 
//  gprsSerial.println((char)26);//sending
//  delay(2000);//waitting for reply, important! the time is base on the condition of internet 
//  gprsSerial.println();
// 
//  ShowSerialData();
// 
//  gprsSerial.println("AT+CIPSHUT");//close the connection
//  delay(100);
//  ShowSerialData();
     // START OF SENDING GPS CORDINATES TO THINKSPEAK.........................................................
    // if ((millis() - lastTime) > timerDelay) {

    
    // Connect or reconnect to WiFi

    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        
        WiFi.begin(ssid, password); 
        WiFi.reconnect();
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // Get cordinates 
    field1 = gps.location.lat(),6;
    field2 = gps.location.lng(),6;

    
    ThingSpeak.setField(1, field1);
    ThingSpeak.setField(2, field2);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
       sendSMS(gps.location.lat(),gps.location.lng());
       delay(15000);
      
    }
   // lastTime = millis();
    WiFi.disconnect();
  //}
  //END OF SENDING GPS CORDINATES.........................................................
  //send SMS
     if(m>100){
      sendSMS(gps.location.lat(),gps.location.lng());
      
      }
      }
  }  
   
  else
  {
    Serial.print(F("INVALID"));
      display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("Searching for GPS connection...");
  display.display();
  }

 
  Serial.println();
  delay(100);
}

void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000); 
  
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void sendSMS(float lat, float lng){
   //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+256750199473\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Am lost, my current location cordinates are"+  String(lat)+","+String(lng)); //text content
  updateSerial();
  mySerial.write(26);
  
  }
