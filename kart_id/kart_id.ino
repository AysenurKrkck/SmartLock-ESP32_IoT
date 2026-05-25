#include <SPI.h>       // SPI iletişim kütüphanesi / SPI communication library
#include <MFRC522.h>   // MFRC522 RFID kütüphanesi / MFRC522 RFID library

// Pin Tanımlamaları / Pin Definitions
#define SS_PIN  5
#define RST_PIN 22

// RFID nesnesi oluşturuluyor / Creating RFID instance
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  // Seri haberleşme başlatılıyor / Initializing serial communication
  // (Seri monitörü 115200 baud yapmayı unutma! / Don't forget to set serial monitor to 115200 baud!)
  Serial.begin(115200); 
  
  // SPI ve RFID modülü başlatılıyor / Initializing SPI and RFID module
  SPI.begin();
  rfid.PCD_Init();
  
  Serial.println("Sistem Hazir. Kartinizi okutun... / System Ready. Scan your card...");
}

void loop() {
  // Kart okunsun okunmasın, 2 saniyede bir nokta koyar. 
  // Eğer nokta geliyorsa ESP32 çalışıyor, RFID kartı görmüyor demektir.
  // Prints a dot every 2 seconds whether a card is read or not.
  // If dots are appearing, ESP32 is running but RFID is not detecting a card.
  Serial.print("."); 
  delay(2000); 

  // Yeni bir kart okutulmadıysa veya okunamadıysa döngüden çık
  // If a new card is not present or cannot be read, exit the loop
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
  
  // Kart algılandığında UID numarasını ekrana yazdırır
  // Prints the UID number when a card is detected
  Serial.print("\nKart bulundu! UID: / Card found! UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    // Tek haneli hex değerlerinin başına '0' ekler / Adds leading '0' for single-digit hex values
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX); // Hexadecimal formatta yazdırır / Prints in HEX format
  }
  Serial.println();
  
  // Kart okumayı sonlandır (Aynı kartın üst üste okunmasını engeller)
  // Halt PICC (Prevents continuous reading of the same card)
  rfid.PICC_HaltA();
}
