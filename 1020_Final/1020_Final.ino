#include "config.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define LEDPin 13

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

AdafruitIO_Feed *rfeed = io.feed("colorrfeed");
AdafruitIO_Feed *gfeed = io.feed("colorgfeed");
AdafruitIO_Feed *bfeed = io.feed("colorbfeed");
AdafruitIO_Feed *counter = io.feed("accelx_feed", "Zhengyu325Jane");
//AdafruitIO_Feed *counter1 = io.feed("accely_feed", "Zhengyu325Jane");
//AdafruitIO_Feed *counter2 = io.feed("accelz_feed", "Zhengyu325Jane");
//int newR = 0;
float xaccel;

void setup() {
  Serial.begin(115200);
  pinMode(LEDPin, OUTPUT);
  
  while(!Serial);
  Serial.print("Please connect to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    
  }

  Serial.println();
  Serial.println(io.statusText());

  counter->onMessage(handleMessage);
//  counter1->onMessage(handleMessage1);
//  counter2->onMessage(handleMessage2);
if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
//  if (!TCS.begin()) {
//    Serial.println("No TCS34725 found ... check your connections");
//    while (1);
//  } else {
//    Serial.println("Found sensor");
//  }
}

void loop(void) {
  io.run();
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
//  uint16_t clear, red, green, blue;
//  TCS.getRawData(&red, &green, &blue, &clear);
//
// uint16_t r, g, b, c;
//

//  tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_50MS);
//  delay(154); // Delay for one old integ. time period (to finish old reading)
//  delay(615); // Delay for one new integ. time period (to allow new reading)
//  tcs.getRawData(&r, &g, &b, &c);
//  Serial.print("Integ. time: 50ms ");
//  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
//  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
//  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
//  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
//  Serial.println(" ");

//  float value = analogRead(xaccel);

  // Convert XYZ data to RGB
//  float X = (float)red / clear;
//  float Y = (float)green / clear;
//  float Z = (float)blue / clear;

//  float R = 3.2406 * X - 1.5372 * Y - 0.4986 * Z;
//  float G = -0.9689 * X + 1.8758 * Y + 0.0415 * Z;
//  float B = 0.0557 * X - 0.2040 * Y + 1.0570 * Z;

//  R = (R > 1.0) ? 1.0 : ((R < 0.0) ? 0.0 : R);
//  G = (G > 1.0) ? 1.0 : ((G < 0.0) ? 0.0 : G);
//  B = (B > 1.0) ? 1.0 : ((B < 0.0) ? 0.0 : B);

//  int r = R * 255;
//  int g = G * 255;
//  int b = B * 255;
//
//  Serial.print(" R: ");
//  Serial.print(r);
//  Serial.print(" G: ");
//  Serial.print(g);
//  Serial.print(" B: ");
//  Serial.println(b);
  
  float xnum = map(abs(xaccel), 0, 10, 0, 255);
  

  rfeed->save(r);
  gfeed->save(g);
  bfeed->save(b);

  Serial.println(xnum);
  if (xnum > 50) {
    // Turn on the LED
    digitalWrite(LEDPin, HIGH);
  } else {
    // Turn off the LED
    digitalWrite(LEDPin, LOW);
  }

  delay(3000);
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("Received:");
  xaccel = data->toFloat();
  Serial.println(data->value());
  

//  otherValueForLED = data->toFloat();

}

//void handleMessage1(AdafruitIO_Data *data) {
//  Serial.print("Received:");
//  Serial.println(data->value());
//}
//
//void handleMessage2(AdafruitIO_Data *data) {
//  Serial.print("Received:");
//  Serial.println(data->value());
//}
