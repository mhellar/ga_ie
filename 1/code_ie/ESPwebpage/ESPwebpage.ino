#include <ESP8266WiFi.h> 
const char* ssid = "extreme"; //wifi ssid / wifi name
const char* password = "extreme!!!"; //wifi password
int ledPin = LED_BUILTIN; 


WiFiServer server(80); 
void setup() { 
 
 myservo.attach(5);
 Serial.begin(115200); 
 delay(10); 
 pinMode(ledPin, OUTPUT); 
 digitalWrite(ledPin, LOW); 
 // Connect to WiFi network 
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
 WiFi.begin(ssid, password); 
 while (WiFi.status() != WL_CONNECTED) { 
   delay(500); 
   Serial.print("."); 
 } 
 Serial.println(""); 
 Serial.println("WiFi connected"); 
 // Start the server 
 server.begin(); 
 Serial.println("Server started"); 
 // Print the IP address 
 Serial.print("Use this URL to connect: "); 
 Serial.print("http://"); 
 Serial.print(WiFi.localIP()); 
 Serial.println("/"); 
} 
void loop() { 
 // Check if a client has connected 
 WiFiClient client = server.available(); 
 if (!client) { 
   return; 
 } 
 // Wait until the client sends some data 
 Serial.println("new client"); 
 while(!client.available()){ 
   delay(1); 
 } 
 // Read the first line of the request 
 String request = client.readStringUntil('\r'); 
 Serial.println(request); 
 client.flush(); 
 // Match the request 
 int value = LOW; 
 if (request.indexOf("/LED=ON") != -1)  { 
   digitalWrite(ledPin, HIGH); 
   value = HIGH; 
   myservo.write(90);              // tell servo to go to position in variable 'pos' 
   delay(15);                       // waits 15ms for the servo to reach the position 
 } 
 if (request.indexOf("/LED=OFF") != -1)  { 
   digitalWrite(ledPin, LOW); 
   value = LOW; 
   myservo.write(180);              // tell servo to go to position in variable 'pos' 
   delay(15);                       // waits 15ms for the servo to reach the position 
 } 
unsigned long time= millis();
// Set ledPin according to the request 
//digitalWrite(ledPin, value); 
 // Return the response 
 client.println("HTTP/1.1 200 OK"); 
 client.println("Content-Type: text/html"); 
 client.println(""); //  do not forget this one 
 client.println("<!DOCTYPE HTML>"); 
 client.println("<html>"); 
 client.print("<body style='background: #00979C'>"); 
 client.println("<h1 align ='center'>"); 
 client.println("<font-color='red'>"); 
 client.println("Interactive Environments"); 
 client.println("</font>"); 
 client.println("</h1>"); 
 client.println("<bg color ='#00ff00'>"); 
 client.println("</bg>"); 
 client.println("<p align ='center'>"); 
 client.print("Led is Now: "); 
 client.println("</p>"); 
 if(value == HIGH) { 
   client.println("<p align ='center'>"); 
   client.print("On"); 
   client.println("</p>"); 
 } else { 
   client.println("<p align ='center'>"); 
   client.print("Off"); 
   client.println("</p>"); 
 } 
 client.println("<br><br>"); 
 client.println("<p align ='center'>"); 
 client.println("<a  href=\"/1\"\"><button>Turn On </button></a>"); 
 client.println("<a  href=\"/2\"\"><button>Turn Off </button></a><br />");   
 client.println("</p>"); 
 client.println("<p>"); 
 client.println("<marquee direction='right'>"); 
 client.println("<img src=\"http://img1.wikia.nocookie.net/__cb20140924210814/trollpasta/images/1/1c/Squidward-Head-Funny.png\">"); 
 client.println("</marquee>"); 
 client.println("</p>"); 
 client.println("</body>"); 
 client.println("</html>"); 
 delay(1); 
 Serial.println("Client disonnected"); 
 Serial.println(""); 
} 

//neopixel functions
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
