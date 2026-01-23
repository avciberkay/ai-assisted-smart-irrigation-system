#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// --- AYARLAR (Kendi Bilgilerin) ---
const char* ssid = "Your_SSID";
const char* password = "Your_Password";
const char* mqtt_server = "Your_Domain";
const char* mqtt_user = "USER";
const char* mqtt_pass = "PASSWORD";

// --- PİN TANIMLARI ---
const int pumpPin = 26;
const int sensorPins[] = {36, 39, 34, 35, 32};
const int numSensors = 5;

// --- DEĞİŞKENLER ---
bool isWatering = false;
unsigned long lastPumpOffTime = 0;
const unsigned long stabilizationDelay = 10000; 

// --- SSL SERTİFİKASI ---
const char* root_ca = "Your_Certificate"
WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("\nConnecting to WiFi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

// --- KOMUT GELDIĞİNDE ÇALIŞAN KISIM ---
void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  
  // Gelen dakikayı float olarak alıyoruz
  float duration = msg.toFloat(); 
  
  if (duration > 0 && duration < 1440.0) { // Güvenlik sınırı: 24 saat
    isWatering = true;
    
    // Seri monitörde ondalıklı göstermek için %.2f kullanıyoruz
    Serial.printf("AI Decision: Watering for %.2f minutes...\n", duration);
    
    digitalWrite(pumpPin, HIGH);

    // TAŞMAYI ÖNLEYEN HESAPLAMA:
    // (Dakika * 60 saniye * 1000 milisaniye)
    // 60000.0 (noktalı) yazarak matematiksel taşmayı engelliyoruz.
    unsigned long waitTime = (unsigned long)(duration * 60000.0);
    
    delay(waitTime); 
    
    digitalWrite(pumpPin, LOW);
    isWatering = false;
    lastPumpOffTime = millis();
    Serial.println("Irrigation finished. Waiting for stabilization (10s)...");
    client.publish("irrigation/status", "completed");
  } else {
    Serial.printf("Invalid duration: %.2f\n", duration);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32_Irrigation_System", mqtt_user, mqtt_pass)) {
      Serial.println("Connected!");
      client.subscribe("irrigation/pump");
    } else {
      Serial.printf("Failed, rc=%d. Retrying in 5s...\n", client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);

  setup_wifi();
  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, 8883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  static unsigned long lastMsg = 0;
  unsigned long now = millis();

  // 60 saniyede bir veri gönder (Gemini kotasını korumak için idealdir)
  if (now - lastMsg > 60000) { 
    if (!isWatering && (now - lastPumpOffTime > stabilizationDelay)) {
      lastMsg = now;
      String jsonPayload = "{";
      for(int i=0; i<numSensors; i++) {
        jsonPayload += "\"s" + String(i+1) + "\":" + String(analogRead(sensorPins[i]));
        if(i < numSensors-1) jsonPayload += ",";
      }
      jsonPayload += "}";
      client.publish("irrigation/data", jsonPayload.c_str());
      Serial.println("Data Sent: " + jsonPayload);
    }
  }
}
