# SmartLock-ESP32_IoT

# 🔑 SmartLock-ESP32-V2 (Blynk IoT & Servo)

[TR] ESP32, RFID ve **Blynk IoT** kullanılarak geliştirilmiş, internet üzerinden veya fiziksel kartla kontrol edilebilen akıllı kapı kilidi sistemi.

[EN] A smart door lock system developed using ESP32, RFID, and **Blynk IoT**, controllable via internet or physical card.

---

## 🚀 Proje Özellikleri / Features

### [TR] Türkçe
* **Çift Kontrol Mekanizması:** Yetkili RFID kart veya Blynk bulut paneli üzerinden kapıyı açma.
* **IoT İzleme:** Kapının kim tarafından açıldığını (Kart veya Uygulama) Blynk üzerinden anlık takip etme.
* **Otomatik Kilitleme:** Kapı açıldıktan 3 saniye sonra servo motor yardımıyla otomatik olarak geri kilitlenir.
* **Güvenlik Bildirimleri:** Yetkisiz kart denemelerinde sesli (Buzzer) ve ışıklı (Kırmızı LED) uyarı.

### [EN] English
* **Dual Control:** Open the door with an authorized RFID tag or via the Blynk Cloud panel.
* **IoT Monitoring:** Track access logs (who opened the door) in real-time on the Blynk dashboard.
* **Auto-Lock:** The servo motor automatically re-locks the door 3 seconds after access is granted.
* **Security Alerts:** Visual (Red LED) and audible (Buzzer) alerts for unauthorized card attempts.

---

## 📦 Kütüphaneler / Libraries

Bu projenin çalışması için aşağıdaki kütüphanelerin Arduino IDE'ye yüklenmesi gerekmektedir:
*The following libraries must be installed for this project to work:*

| Kütüphane / Library | Açıklama / Description |
| :--- | :--- |
| **Blynk** | Cloud IoT connection / Bulut IoT bağlantısı |
| **MFRC522** | RFID card reading / RFID kart okuma |
| **ESP32Servo** | Servo motor control / Servo motor kontrolü |
| **WiFi & SPI** | Connection & Communication / Bağlantı ve Haberleşme |

---

## 🛠️ Donanım Bileşenleri / Hardware Components

* ESP32 Development Board
* MFRC522 RFID Module
* SG90 Servo Motor (Kilitleme Mekanizması)
* 1x Green LED & 1x Red LED
* 1x Buzzer
* Jumper Wires & Breadboard

---

## 🛠️ Kurulum ve Kullanım / Installation & Usage

### 1️⃣ Blynk Yapılandırması / Blynk Configuration
1. Blynk Cloud üzerinden yeni bir **Template** oluşturun.
2. **V1** pini için bir "Button" widget'ı ekleyin (Kapıyı açmak için).
3. **V2** pini için bir "Value Display" widget'ı ekleyin (Durum mesajları için).
4. Size verilen `AUTH_TOKEN` bilgisini kodun içine yapıştırın.

### 2️⃣ Kart Tanımlama / Card Identification
[TR] Kod içindeki `dogruKartUID[]` dizisini, kendi kartınızın UID numarasıyla güncellemeyi unutmayın.
[EN] Remember to update the `dogruKartUID[]` array with your own card's UID number.

---

## 📂 Dosya Yapısı / Repository Structure

* 📄 `rfid_system_IoT.ino` -> [TR] Blynk entegreli ana kod. / [EN] Main IoT-enabled code.
* 📄 `kart_id.ino` -> [TR] Kart UID tespiti için test kodu. / [EN] Test code for UID detection.

---
