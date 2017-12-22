#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

// Color Recognition Program カラー認識　LED表示
// TSCC230 Sensor and LED

#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define Out 7

#define LED_red 10
#define LED_green 11
#define LED_blue 12

int frequency = 0;
int color_red = 0;
int color_green = 0;
int color_blue = 0;

int whiteR = 255;
int whiteG = 255;
int whiteB = 255;
int blackR = 0;
int blackG = 0;
int blackB = 0;

int outByte0, outByte1, outByte2;

void setup() {
  // Color Sensor output
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(Out, INPUT);

  // LED output
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(LED_blue, OUTPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  frequency = pulseIn(Out, LOW);
  // Remapingthe value of the frequency to the RGB Model of 0 to 255
  // map(value, fromLow, fromHigh, toLow, toHigh)は、バラメータの下限、上限を収めるコマンド、ここでは、取得した数値を0-255に収める
  frequency = map(frequency, whiteR, blackR, 255, 0);
  color_red = constrain(frequency, 0, 255);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(Out, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, whiteG, blackG, 255, 0);
  color_green = constrain(frequency, 0, 255);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(Out, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, whiteB, blackB, 255, 0);
  color_blue = constrain(frequency, 0, 255);

  // Printing the value on the serial monitor
  // Arduino IDEの「シリアルモニタ」に、color_redの値を表示
  //Serial.print("R= ");
  Serial.print(color_red);
  Serial.print(",");
  //delay(100);
  // Printing the value on the serial monitor
  // Arduino IDEの「シリアルモニタ」に、color_greenの値を表示
  //Serial.print("G= ");
  Serial.print(color_green);
  Serial.print(",");
  //delay(100);
  // Printing the value on the serial monitor and output to LED
  // Arduino IDEの「シリアルモニタ」に、color_blueの値を表示
  //Serial.print("B= ");//printing name
  Serial.println(color_blue);//printing Blue color frequency
  //Serial.println(" ");

  outByte0 = 255 - color_red;
  outByte1 = 255 - color_green;
  outByte2 = 255 - color_blue;


  delay(1000);
}
