#include <Arduino.h>
#include <NeoPixelBus.h>
 
#define NUM_LEDS 1
#define LedPin 2
#define RGBLed 3

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(NUM_LEDS, RGBLed);  

String logo = " /$$       /$$ /$$          \n| $$      |__/| $$          \n| $$       /$$| $$ /$$   /$$\n| $$      | $$| $$| $$  | $$\n| $$      | $$| $$| $$  | $$\n| $$      | $$| $$| $$  | $$\n| $$$$$$$$| $$| $$|  $$$$$$$\n|________/|__/|__/ \\____  $$\n                   /$$  | $$\n                  |  $$$$$$/\n                   \\______/ \n";///*The open source copyright belongs to Lily-rabot*/


void rtprint(String str){
  Serial.print("["+String(millis()/1000)+"."+String(millis()%1000)+"]");
  Serial.print(str);
}

void SerialRGB () 
{
  String color = Serial.readString();  
  unsigned long rgb = strtol(color.c_str(), NULL, 16);

  byte red = rgb >> 16;  
  byte green = (rgb & 0x00ff00) >> 8;  
  byte blue = (rgb & 0x0000ff);  

  RgbColor rgbColor(red, green, blue);  
  strip.SetPixelColor(0, rgbColor);  
  strip.Show();
}


/*@@.....print some info....@@*/
void info(){
  
  Serial.println();
  Serial.println(logo+"\n");
   
  Serial.println("ESP32 information:");  
     
  rtprint("MAC address: ");  
   
  uint64_t mac = ESP.getEfuseMac();
  for (int i = 0; i < 6; i++) 
  {
    if (i > 0) Serial.print(".");
    Serial.printf("%02X",(mac >> (40 - i * 8)) & 0xFF);
  }
  Serial.println();
  rtprint("Chip model: ");  
  Serial.println(ESP.getChipModel());

  rtprint("Chip revision: ");  
  Serial.println(ESP.getChipRevision());
   
  rtprint("CPU frequency: ");  
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");

  rtprint("Flash size: ");  
  Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
  Serial.println(" M");

  rtprint("Flash speed: ");  
  Serial.print(ESP.getFlashChipSpeed() / (1000 * 1000));
  Serial.println(" MHz");

  rtprint("Flash mode: ");  
  switch (ESP.getFlashChipMode()) {
    case FM_QIO:
      Serial.println("QIO");
      break;
    case FM_QOUT:
      Serial.println("QOUT");
      break;
    case FM_DIO:
      Serial.println("DIO");
      break;
    case FM_DOUT:
      Serial.println("DOUT");
      break;
    default:
      Serial.println("Unknown");
      break;
  }
  
  rtprint("PSRAM size: "+String(ESP.getPsramSize()/100000)+"MB\n");

  rtprint("Sketch size: ");  
  Serial.print(ESP.getSketchSize() / (1024 * 1024));
  Serial.println(" M");
   
  rtprint("Free sketch space: ");  
  Serial.print(ESP.getFreeSketchSpace() / (1024 * 1024));
  Serial.println(" M");
   
  rtprint("Sketch MD5: ");  
  Serial.println(ESP.getSketchMD5());
   
  rtprint("Free heap: ");  
  Serial.print(ESP.getFreeHeap() / (1024 * 1024));
  Serial.println(" M");
   
  rtprint("Heap size: ");  
  Serial.print(ESP.getHeapSize() / (1024 * 1024));
  Serial.println(" M");
  // this metol is enable.
  // rtprint("Heap fragmentation: null");  
  // Serial.println("%");
}


/*
@@.....the program init......@@
*/
void setup() {
  Serial.begin(115200);
  strip.Begin();  
  delay(100);
  info();
  delay(100);
}

void loop() {
  if (Serial.available () > 0) {
    rtprint("get Serial text\n");
    SerialRGB();
  }else{
   
  }
}
