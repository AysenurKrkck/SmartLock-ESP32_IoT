// Buraya Blynk konsolundan aldığınız özel bilgileri ekleyin.
// Fill in your specific details from the Blynk console here.
#define BLYNK_TEMPLATE_NAME "" 
#define BLYNK_AUTH_TOKEN ""
#define BLYNK_TEMPLATE_ID ""

// LIBRARIES / KÜTÜPHANELER
#include <BlynkSimpleEsp32.h>
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32Servo.h>

// WiFi & Blynk Bilgileri / WiFi & Blynk Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";      // WiFi Adı / WiFi SSID
char pass[] = "";      // WiFi Şifre / WiFi Password

// Pin Tanımlamaları / Pin Definitions
#define SS_PIN    5    // RFID SDA Pini
#define RST_PIN   22   // RFID Reset Pini
#define YESIL_LED 12   // Yeşil LED / Green LED
#define KIRMIZI_LED 14 // Kırmızı LED / Red LED
#define BUZZER    27   // Buzzer
#define SERVO_PIN 13   // Servo Motor Pini

MFRC522 rfid(SS_PIN, RST_PIN);
Servo kapiServosu;

// Yetkili Kart UID / Authorized Card UID
byte dogruKartUID[] = {0x57, 0x97, 0xD1, 0x06}; 

// Servo Açıları / Servo Angles
const int kapiKapaliAci = 0;   // Kapalı / Locked
const int kapiAcikAci = 90;    // Açık / Unlocked

void setup() {
  Serial.begin(115200);
  SPI.begin();           // SPI veriyolunu başlat / Start SPI bus
  rfid.PCD_Init();       // RFID okuyucuyu başlat / Initialize RFID reader
  
  pinMode(YESIL_LED, OUTPUT);
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  kapiServosu.attach(SERVO_PIN);
  kapiServosu.write(kapiKapaliAci); // Başlangıçta kapıyı kapat / Lock door at start
  
  // Blynk ve WiFi bağlantısını başlat / Initialize Blynk and WiFi
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V2, "Sistem Aktif. Kart Bekleniyor..."); // System Active. Waiting for card...
}

// Kapıyı Açma Fonksiyonu / Function to Open the Door
void kapiyiAc(String tetikleyen) {
  Serial.println("Erisim Onaylandi: " + tetikleyen); // Access Granted
  Blynk.virtualWrite(V2, tetikleyen + " ile kapi acildi!");
  
  digitalWrite(YESIL_LED, HIGH); // Yeşil LED'i yak / Turn on Green LED
  digitalWrite(BUZZER, HIGH);    // Kısa bip / Short beep
  delay(150); 
  digitalWrite(BUZZER, LOW);
  
  kapiServosu.write(kapiAcikAci); // Servoyu döndür (Kapı açıldı) / Rotate servo (Door opened)
  
  delay(3000); // 3 saniye açık kalsın / Keep open for 3 seconds
  
  kapiServosu.write(kapiKapaliAci); // Kapıyı geri kapat / Re-lock the door
  digitalWrite(YESIL_LED, LOW);
  Blynk.virtualWrite(V2, "Kapi kilitlendi. Kart bekleniyor...");
}

// Erişim Reddedildi Fonksiyonu / Access Denied Function
void kapiyiReddet() {
  Serial.println("Erisim Reddedildi!"); // Access Denied
  Blynk.virtualWrite(V2, "UYARI: Yetkisiz Kart Denemesi!"); // WARNING: Unauthorized Card!
  
  digitalWrite(KIRMIZI_LED, HIGH); // Kırmızı LED'i yak / Turn on Red LED
  digitalWrite(BUZZER, HIGH);      // Uzun bip / Long beep
  delay(600); 
  digitalWrite(BUZZER, LOW);
  
  delay(1000);
  digitalWrite(KIRMIZI_LED, LOW);
}

// Blynk Uygulamasından Gelen Komut (V1 Butonu) / Blynk App Command (V1 Button)
BLYNK_WRITE(V1) {
  int butonDurumu = param.asInt();
  if (butonDurumu == 1) {
    kapiyiAc("Blynk Web Panel");
  }
}

void loop() {
  Blynk.run(); // Blynk iletişimini sürdür / Maintain Blynk communication

  // Yeni bir kart okutulup okutulmadığını kontrol et / Check for a new card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  bool kartDogruMu = true;

  // Okunan kartın UID'sini kontrol et / Check scanned card's UID
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] != dogruKartUID[i]) {
      kartDogruMu = false;
      break;
    }
  }

  // Kart yetkiliyse aç, değilse reddet / Open if authorized, otherwise deny
  if (kartDogruMu) {
    kapiyiAc("RFID Kart");
  } else {
    kapiyiReddet();
  }

  // Kart okumayı sonlandır / Stop card reading
  rfid.PICC_HaltA();
}
