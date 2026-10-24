# 🎨 Görme Engelliler İçin Renk Okuyan Akıllı Cihaz (Color Reader Device)

Bu proje, görme engelli bireylerin çevrelerindeki nesnelerin, kıyafetlerin veya yüzeylerin renklerini kolayca algılayabilmesi ve sesli olarak öğrenebilmesi amacıyla geliştirilmiş taşınabilir, akıllı bir yardımcı cihazdır.

---

## 📌 Proje Amacı
Görme engelli bireylerin günlük yaşamda (özellikle kıyafet seçimi, alışveriş veya nesne tanıma süreçlerinde) bağımsızlığını artırmak; dokunulan veya hedeflenen nesnenin rengini anlık olarak algılayıp kulaklık veya hoparlör aracılığıyla sesli geri bildirim (TTS - Text to Speech) sağlamak.

---

## 🛠️ Kullanılan Teknolojiler ve Donanımlar

### Donanım (Hardware)
* **Mikrodenetleyici:** ESP32 / Arduino (Wi-Fi/Bluetooth destekli veya taşınabilir mikrodenetleyici)
* **Renk Sensörü:** TCS3200 veya TCS34725 (RGB renk ve parlaklık algılama)
* **Ses Modülü / Çıkışı:** DFPlayer Mini (veya ses kartı/hoparlör)
* **Buton:** Cihazın renk okumasını tetiklemek için bas-bırak buton
* **Güç Kaynağı:** Şarj edilebilir Li-Po pil ve güç yönetim devresi

### Yazılım ve Kütüphaneler (Software)
* **Programlama Dili:** C++ / Python (Mikrodenetleyici veya Raspberry Pi seçimine göre)
* **Sensör Kütüphaneleri:** Adafruit TCS34725 / TCS3200 kütüphaneleri
* **Ses Dönüşüm / Sentez:** Önceden kaydedilmiş ses dosyaları (MP3/WAV) veya TTS kütüphaneleri

---

## 📂 Proje Klasör Yapısı

```text
Color_Reader_Device/
│
├── hardware/              # Donanım şemaları, Fritzing / devre bağlantı çizimleri
├── firmware/              # Mikrodenetleyici kodları (C++ / Arduino IDE dosyaları)
├── software/              # Ek Python betikleri (eğer Raspberry Pi kullanılıyorsa)
├── audio_prompts/         # Renk isimlerine ait ses dosyaları (kırmızı, mavi, yeşil vb.)
├── docs/                  # Kullanım kılavuzu ve proje sunumları
└── README.md              # Proje dökümantasyonu
⚙️ Çalışma Mantığı
Tetikte Olma: Kullanıcı, cihazı rengini öğrenmek istediği nesnenin yüzeyine yaklaştırır ve üzerindeki butona basar.

Algılama: Renk sensörü (TCS34725/TCS3200) nesneden yansıyan ışığı RGB (Kırmızı, Yeşil, Mavi) değerleri olarak okur.

İşleme: Mikrodenetleyici, okunan bu RGB değerlerini önceden tanımlanmış renk skalası algoritmalarıyla eşleştirir (Örn: En yakın temel renk: Mavi, Kırmızı, Sarı vb.).

Sesli Geri Bildirim: Eşleşen rengin ses dosyası hafıza kartından (TF Card) çağrılır ve hoparlör aracılığıyla kullanıcıya sesli olarak bildirilir.

🚀 Kurulum ve Kullanım
1. Donanım Bağlantıları
Sensörün ve ses modülünün mikrodenetleyiciye bağlantısını hardware/ klasöründeki şemalara göre yapın:

TCS34725 (I2C): SDA ve SCL pinleri ilgili mikrodenetleyici pinlerine bağlanır.

Ses Modülü: UART veya PWM üzerinden ses çıkışı sağlanır.

2. Yazılımın Yüklenmesi
firmware/ klasöründeki ana kodu Arduino IDE veya ilgili geliştirme ortamı ile açın.

Gerekli kütüphaneleri (Adafruit_TCS34725 vb.) IDE kütüphane yöneticisinden yükleyin.

Kodu kartınıza derleyip yükleyin (Upload).

3. Ses Dosyalarının Hazırlanması
audio_prompts/ klasöründe bulunan ses dosyalarını bir microSD karta yükleyin ve ses modülüne takın.

🌟 Katma Değer ve Sosyal Etki
Erişilebilirlik: Kıyafet eşleştirme, renk uyumu sağlama ve günlük yaşamda bağımsız karar alma süreçlerinde büyük kolaylık sağlar.

Taşınabilirlik: Kompakt boyutu sayesinde cepte veya boyun askısıyla kolayca taşınabilir.

Düşük Maliyet: Erişilebilir ve ekonomik donanım elemanları kullanılarak üretilebilir.
