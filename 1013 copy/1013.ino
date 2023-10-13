#include"config.h"

#define PPT A2

AdafruitIO_Feed *Potfeed = io.feed("potfeed");
AdafruitIO_Feed *counter = io.feed("accelx_feed", "Zhengyu325Jane");
AdafruitIO_Feed *counter1 = io.feed("accely_feed", "Zhengyu325Jane");
AdafruitIO_Feed *counter2 = io.feed("accelz_feed", "Zhengyu325Jane");


void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 while(! Serial);
 Serial.print("Please connect to Adafruit IO");
  io.connect();
  
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
    }
    
    Serial.println();
    Serial.println(io.statusText());

    counter->onMessage(handleMessage);
    counter1->onMessage(handleMessage1);
    counter2->onMessage(handleMessage2);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  io.run();

  float value = analogRead(PPT);
  
  Serial.print("Sending this:");
  Serial.println(value);
  Potfeed->save(value);

  delay(3000);
}

void handleMessage(AdafruitIO_Data *data){
  Serial.print("recieved:");
  Serial.println(data->value());
  
}

void handleMessage1(AdafruitIO_Data *data){
  Serial.print("recieved:");
  Serial.println(data->value());
  
}

void handleMessage2(AdafruitIO_Data *data){
  Serial.print("recieved:");
  Serial.println(data->value());
  
}
