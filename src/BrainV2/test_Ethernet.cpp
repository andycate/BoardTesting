#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>

#include <Arduino.h>

#include <string>

using namespace std;

EthernetUDP Udp;
unsigned int port = 42069; // try to find something that can be the same on gs
IPAddress groundIP(10, 0, 0, 69);

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEA
};
IPAddress ip(10, 0, 0, 42); // depndent on local network

bool setupEthernetComms(byte * mac, IPAddress ip){
  Ethernet.begin(mac, ip);
  Serial.println("begun ethernet");
  Serial.flush();

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    Serial.flush();
    exit(1);
  } else if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    Serial.flush();
    exit(1);
  }

  Udp.begin(port);
  return true;
}

void sendEthPacket(string packet){
  Udp.beginPacket(groundIP, port);
  Udp.write(packet.c_str());
  Udp.endPacket();
}

void setup() {
  Serial.begin(57600);

  while(!Serial);

  Serial.println("starting ethernet");
  setupEthernetComms(mac, ip);
}

void loop() {
  sendEthPacket("test");
  delay(1000);
}
