/*============================================
 * mqqt dimmer  
 * 
 * By: willem spoelstra
 * 
 ============================================*/
#include<SPI.h> 
#include<Ethernet.h>
#include <PubSubClient.h>
EthernetClient ethClient;
PubSubClient client(ethClient);
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED};
byte server[]= {192, 168, 2, 11}; //your mqqt broker ip

void callback(char* topic, byte* payload, unsigned int length){
  int i = 0;
  char message_buff[100];
  for(i=0; i<length; i++){
    message_buff[i] = payload[i];    
  }
  message_buff[i] = '\0';
  String msgString = String(message_buff);

  //incomming msg topics
  
}

// debug RGB led for status when booting
static int LEDred = 3;
static int LEDgreen = 5;
static int LEDblue = 6;

void setup() {
  pinMode(LEDred,OUTPUT);
  pinMode(LEDgreen,OUTPUT);
  pinMode(LEDblue,OUTPUT);
  //at start up writing the led blue;
  analogWrite(LEDred, 255);
  analogWrite(LEDgreen, 255);
  analogWrite(LEDblue, 0);
  
  if(Ethernet.begin(mac) == 0){
    analogWrite(LEDred, 0);
    analogWrite(LEDgreen, 255);
    analogWrite(LEDblue, 255);
    while (true);
  }else{
    analogWrite(LEDred,255);
    analogWrite(LEDgreen, 0);
    analogWrite(LEDblue, 255);
  }
}
  client.setServer(server, 1883);
  client.setCallback(callback);
void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
    client.connect("arduino_1");
    client.subscribe("openhab/#"); 
  }
  client.loop();
}
