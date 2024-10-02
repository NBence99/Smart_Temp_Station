#define BLYNK_TEMPLATE_ID "Blynk Template ID"  // Blynk Template ID
#define BLYNK_TEMPLATE_NAME "Blynk template name"
#define BLYNK_AUTH_TOKEN "Blynk Auth Token"    // Blynk Auth Token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "Blynk token";  //Blynk alkalmazás token
char ssid[] = "Wi-Fi hálózat neve";       // A Wi-Fi hálózat neve
char pass[] = "Wi-Fi jelszo";   // A Wi-Fi hálózat jelszava

#define DHTPIN 15  // A DHT11 szenzor a 15-ös lábra van kötve
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void send_data() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Celsius érték
  Serial.println(h);
  Serial.println(t);

  if (isnan(h) || isnan(t)) {
    Serial.println("Nem sikerült olvasni a DHT szenzor adatait!");
    return;
  }

  Blynk.virtualWrite(V0, t);  // Küldés a Blynk V5 virtuális pinre
  Blynk.virtualWrite(V1, h);  // Küldés a Blynk V6 virtuális pinre
}

// Ellenőrzi a WiFi kapcsolatot
void check_wifi() {

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
  }

}

void blynk_connect(){
    Blynk.config(auth);
    Blynk.connect();
}

void setup() {
  Serial.begin(115200);
  check_wifi(); // WiFi kapcsolat felvétele
  blynk_connect(); //blynk kapcsolodás
  dht.begin();
  
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    Blynk.run();
    send_data();
    delay(2000);
    
  }else{

    check_wifi();
    delay(2000);
  }

}
