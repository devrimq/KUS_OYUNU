# 🐦 ESP32 ile Mikrodenetleyici Kuş Oyunu (Pixel Bird)

Bu proje, **ESP32** mikrodenetleyicisi, **SSD1306 OLED Ekran** (128x64) ve bir adet buton kullanılarak geliştirilmiş, telif ve marka hakkı riski barındırmayan ticari kullanıma uygun bir retro kuş uçurma oyunudur. Orijinal mekanikler daha konforlu, akıcı ve yavaşlatılmış bir oynanış deneyimi sunması adına optimize edilmiştir.

---

## 🚀 Özellikler

* **Telif Risksiz Tasarım:** Açılış ve bitiş ekranlarında, marka ihlali oluşturabilecek tüm ifadeler temizlenerek "Kuş Oyunu" ismiyle tamamen güvenli hale getirilmiştir.
* **Dengeli Fizik Motoru:** Yerçekimi ve zıplama kuvveti ile boru geçiş boşlukları hassas şekilde dengelenerek oyun keyfi artırılmıştır.
* **Dinamik Zorluk:** Skor her 5 puana ulaştığında oyun hızı kademeli olarak artar (oyunun kilitlenmemesi için 2.5 hızı ile sınırlandırılmıştır).
* **Retro Ses Efektleri:** Zıplama, skor kazanma ve yanma durumlarında buzzer üzerinden farklı frekanslarda 8-bit sesler üretilir.

---

## 🛠️ Gerekli Malzemeler

* 1x ESP32 Geliştirme Kartı (NodeMCU ESP32 vb.)
* 1x SSD1306 I2C OLED Ekran (128x64 piksel, Monokrom)
* 1x Push Buton (Kontrol için)
* 1x Pasif veya Aktif Buzzer (Ses efektleri için)
* Jumper Kablolar ve Breadboard

---

## 🔌 Bağlantı Şeması (Pinout)

Bileşenleri ESP32 kartınıza aşağıdaki pin şemasına göre bağlayabilirsiniz:

| Bileşen | ESP32 Pini | İşlev / Açıklama |
| :--- | :--- | :--- |
| **OLED VCC** | 3.3V veya 5V | Güç Girişi |
| **OLED GND** | GND | Toprak Hattı |
| **OLED SDA** | GPIO 21 | I2C Veri Hattı |
| **OLED SCL** | GPIO 22 | I2C Saat Hattı |
| **Buton (Bacak 1)**| GPIO 4 | Yeşil Kablo (Dahili `INPUT_PULLUP` aktif) |
| **Buton (Bacak 2)**| GND | Toprak Hattı |
| **Buzzer (+)** | GPIO 23 | Kırmızı Kablo (Sinyal Çıkışı) |
| **Buzzer (-)** | GND | Toprak Hattı |

> ⚠️ **Önemli Not:** Buton için yazılımda dahili `INPUT_PULLUP` direnci aktif edilmiştir. Bu sayede butonun bir bacağını doğrudan **GPIO 4** pinine, diğer bacağını ise harici hiçbir direnç kullanmadan direkt **GND**'ye bağlamanız yeterlidir.

---

## 💻 Kurulum ve Yükleme

Oyun kodunu ESP32 kartınıza yüklemeden önce Arduino IDE'de şu kütüphanelerin kurulu olduğundan emin olun:

1. **Adafruit SSD1306** (Ekran Sürücüsü)
2. **Adafruit GFX Library** (Grafik ve Çizim Çekirdeği)

### Adımlar:
1. Arduino IDE uygulamasını açın.
2. **Araçlar > Kart** menüsünden kullandığınız ESP32 modelini seçin.
3. **Araçlar > Kütüphane Yöneticisi...** yolunu izleyin ve yukarıdaki iki kütüphaneyi aratarak en güncel sürümlerini kurun.
4. Kod dosyasındaki içeriği editöre yapıştırın.
5. ESP32 kartınızı USB kablosu ile bilgisayara bağlayıp doğru portu seçtikten sonra **Yükle (Upload)** butonuna basın.

---

## 🎮 Nasıl Oynanır?

1. Kart açıldığında ekranda **"KUS OYUNU - Ziplamak icin bas"** mesajı görünür.
2. Butona bir kez basarak oyunu başlatın.
3. Kuşun engellere (borulara) çarpmaması ya da ekranın altına/üstüne vurup düşmemesi için butona zamanlamalı olarak basarak havada tutun.
4. Geçtiğiniz her boru sütunu size **+1 Skor** kazandırır.
5. Yandığınızda skorunuz ekranda donar. Yeniden başlamak için butona bir kez daha basmanız yeterlidir.
