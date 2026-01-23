#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// --- AYARLAR (Kendi Bilgilerin) ---
const char* ssid = "Berkay";
const char* password = "Hard4273";
const char* mqtt_server = "mqtt.avciberkay.cloud";
const char* mqtt_user = "irrigationuser";
const char* mqtt_pass = "B9N#16nA2.";

// --- PİN TANIMLARI ---
const int pumpPin = 26;
const int sensorPins[] = {36, 39, 34, 35, 32};
const int numSensors = 5;

// --- DEĞİŞKENLER ---
bool isWatering = false;
unsigned long lastPumpOffTime = 0;
const unsigned long stabilizationDelay = 10000; 

// --- SSL SERTİFİKASI ---
const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFBTCCAu2gAwIBAgIQWgDyEtjUtIDzkkFX6imDBTANBgkqhkiG9w0BAQsFADBP\n" \
"MQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJuZXQgU2VjdXJpdHkgUmVzZWFy\n" \
"Y2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBYMTAeFw0yNDAzMTMwMDAwMDBa\n" \
"Fw0yNzAzMTIyMzU5NTlaMDMxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBF\n" \
"bmNyeXB0MQwwCgYDVQQDEwNSMTMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n" \
"AoIBAQClZ3CN0FaBZBUXYc25BtStGZCMJlA3mBZjklTb2cyEBZPs0+wIG6BgUUNI\n" \
"fSvHSJaetC3ancgnO1ehn6vw1g7UDjDKb5ux0daknTI+WE41b0VYaHEX/D7YXYKg\n" \
"L7JRbLAaXbhZzjVlyIuhrxA3/+OcXcJJFzT/jCuLjfC8cSyTDB0FxLrHzarJXnzR\n" \
"yQH3nAP2/Apd9Np75tt2QnDr9E0i2gB3b9bJXxf92nUupVcM9upctuBzpWjPoXTi\n" \
"dYJ+EJ/B9aLrAek4sQpEzNPCifVJNYIKNLMc6YjCR06CDgo28EdPivEpBHXazeGa\n" \
"XP9enZiVuppD0EqiFwUBBDDTMrOPAgMBAAGjgfgwgfUwDgYDVR0PAQH/BAQDAgGG\n" \
"MB0GA1UdJQQWMBQGCCsGAQUFBwMCBggrBgEFBQcDATASBgNVHRMBAf8ECDAGAQH/\n" \
"AgEAMB0GA1UdDgQWBBTnq58PLDOgU9NeT3jIsoQOO9aSMzAfBgNVHSMEGDAWgBR5\n" \
"tFnme7bl5AFzgAiIyBpY9umbbjAyBggrBgEFBQcBAQQmMCQwIgYIKwYBBQUHMAKG\n" \
"Fmh0dHA6Ly94MS5pLmxlbmNyLm9yZy8wEwYDVR0gBAwwCjAIBgZngQwBAgEwJwYD\n" \
"VR0fBCAwHjAcoBqgGIYWaHR0cDovL3gxLmMubGVuY3Iub3JnLzANBgkqhkiG9w0B\n" \
"AQsFAAOCAgEAUTdYUqEimzW7TbrOypLqCfL7VOwYf/Q79OH5cHLCZeggfQhDconl\n" \
"k7Kgh8b0vi+/XuWu7CN8n/UPeg1vo3G+taXirrytthQinAHGwc/UdbOygJa9zuBc\n" \
"VyqoH3CXTXDInT+8a+c3aEVMJ2St+pSn4ed+WkDp8ijsijvEyFwE47hulW0Ltzjg\n" \
"9fOV5Pmrg/zxWbRuL+k0DBDHEJennCsAen7c35Pmx7jpmJ/HtgRhcnz0yjSBvyIw\n" \
"6L1QIupkCv2SBODT/xDD3gfQQyKv6roV4G2EhfEyAsWpmojxjCUCGiyg97FvDtm/\n" \
"NK2LSc9lybKxB73I2+P2G3CaWpvvpAiHCVu30jW8GCxKdfhsXtnIy2imskQqVZ2m\n" \
"0Pmxobb28Tucr7xBK7CtwvPrb79os7u2XP3O5f9b/H66GNyRrglRXlrYjI1oGYL/\n" \
"f4I1n/Sgusda6WvA6C190kxjU15Y12mHU4+BxyR9cx2hhGS9fAjMZKJss28qxvz6\n" \
"Axu4CaDmRNZpK/pQrXF17yXCXkmEWgvSOEZy6Z9pcbLIVEGckV/iVeq0AOo2pkg9\n" \
"p4QRIy0tK2diRENLSF2KysFwbY6B26BFeFs3v1sYVRhFW9nLkOrQVporCS0KyZmf\n" \
"wVD89qSTlnctLcZnIavjKsKUu1nA1iU0yYMdYepKR7lWbnwhdx3ewok=\n" \
"-----END CERTIFICATE-----";

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