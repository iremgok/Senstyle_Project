"""
StyleSight Akıllı Kalem Projesi - Sentetik Düz Renk Veri Üretici
Yazar: StyleSight Ekibi (Yapay Zeka İş Paketi)

Bu betik, diğer sınıflarla veri dengesini (Dataset Balance) sağlamak amacıyla
600 adet farklı RGB tonlarında, üzerinde hafif doku/gürültü barındıran
desensiz düz kumaş simülasyon görselleri üretir.
"""

import os
import cv2
import numpy as np

# Görsellerin ilk toplanacağı ham veri klasörü
HEDEF_KLASOR = r"C:\Users\irem\PycharmProjects\Senstyle_Project\datasets\kaggle_images\duz"
os.makedirs(HEDEF_KLASOR, exist_ok=True)

print("=== StyleSight Sentetik Düz Renk Verisi Üretimi Başlatıldı ===")
print("> Hedef veri sayısı: 800 adet dengeli örnek.")

TOTAL_SAMPLES = 800
sayac = 0

for i in range(TOTAL_SAMPLES):
    # 1. Rastgele BGR (OpenCV formatı) ana renk tonunu seçiyoruz
    b = np.random.randint(0, 256)
    g = np.random.randint(0, 256)
    r = np.random.randint(0, 256)

    # 2. Önce 96x96 boyutunda tamamen düz renkten oluşan matrisi oluştur
    base_image = np.zeros((96, 96, 3), dtype=np.uint8)
    base_image[:] = [b, g, r]

    # 3. Gerçek kumaş liflerini ve kamera gürültüsünü taklit etmek için
    # hafif bir Gausyen Gürültü (Texture Effect) üretiyoruz
    noise = np.random.normal(0, 3, (96, 96, 3)).astype(np.int16)

    # Gürültüyü ana resmin üzerine ekle ve sınırları (0-255) koru
    noisy_image = base_image.astype(np.int16) + noise
    final_image = np.clip(noisy_image, 0, 255).astype(np.uint8)

    # 4. Görseli ham klasöre .jpg formatında disk üzerine kaydet
    dosya_yolu = os.path.join(HEDEF_KLASOR, f"sentetik_duz_{sayac}.jpg")
    cv2.imwrite(dosya_yolu, final_image)
    sayac += 1

print("\n==============================================================================")
print(f"[BAŞARILI] {sayac} adet dokulu/desensiz düz renk görseli üretildi!")
print(f"Konum: {HEDEF_KLASOR}")
print("Şimdi 'resize_and_format.py' kodunu çalıştırarak processed klasörünü güncelleyebilirsiniz.")
print("==============================================================================")