"""
StyleSight Akıllı Kalem Projesi - TinyML Veri Ön İşleme Betiği
Yazar: StyleSight Ekibi (Yapay Zeka İş Paketi)

Bu betik, Kaggle'dan indirilen farklı çözünürlükteki ham kumaş/desen resimlerini
gömülü sistemlerde (STM32) çalışacak Edge Impulse modeline uygun olarak
96x96 piksel boyutuna getirir ve kararlı bir klasör yapısına kaydeder.
"""

import os
import sys
import cv2

# ==============================================================================
# 1. DIZIN VE PARAMETRE TANIMLAMALARI
# ==============================================================================
# Doğrudan projenin çalıştığı ana dizini baz alacak şekilde güncelliyoruz
INPUT_DATASET_DIR = os.path.abspath("datasets/kaggle_images")
OUTPUT_DATASET_DIR = os.path.abspath("datasets/processed_96x96")

# İşlenecek desen hedef sınıfları
DATA_CLASSES = ["cicek", "cizgili", "duz", "hayvan",  "kareli", "puantiye"]

# TinyML Modeli için hedef görsel boyutları
TARGET_WIDTH = 96
TARGET_HEIGHT = 96


# ==============================================================================
# 2. GÖRSEL ÖN İŞLEME FONKSİYONU
# ==============================================================================
def preprocess_images():
    """
    Ham görselleri okur, 96x96 boyutuna yeniden boyutlandırır ve
    processed_96x96 klasörü altında ilgili sınıf dizinine kaydeder.
    """
    print("=== StyleSight Veri Ön İşleme Hattı Başlatıldı ===\n")

    # Giriş dizininin varlığını kontrol et
    if not os.path.exists(INPUT_DATASET_DIR):
        print(f"[HATA] Giriş dizini bulunamadı: {INPUT_DATASET_DIR}")
        print("Lütfen datasetleri doğru klasöre yüklediğinizden emin olun.")
        sys.exit(1)

    total_processed_counter = 0

    # Her bir desen sınıfı için döngü başlatıyoruz
    for class_name in DATA_CLASSES:
        source_class_path = os.path.join(INPUT_DATASET_DIR, class_name)
        target_class_path = os.path.join(OUTPUT_DATASET_DIR, class_name)

        # Hedef sınıf klasörü yoksa otomatik oluşturulur
        os.makedirs(target_class_path, exist_ok=True)

        # Eğer ham veri klasörü boş veya yoksa pas geç
        if not os.path.exists(source_class_path):
            print(f"[UYARI] {class_name} sınıfına ait ham klasör bulunamadı, atlanıyor...")
            continue

        # Klasör içindeki dosyaları listele
        image_files = os.listdir(source_class_path)
        class_processed_counter = 0

        print(f"> {class_name.upper()} sınıfı işleniyor (Toplam dosya: {len(image_files)})...")

        for file_name in image_files:
            source_image_file_path = os.path.join(source_class_path, file_name)
            target_image_file_path = os.path.join(target_class_path, file_name)

            try:
                # 1. Görseli OpenCV ile disken oku
                img = cv2.imread(source_image_file_path)

                # Dosya bozuksa veya görsel formatında değilse atla
                if img is None:
                    continue

                # 2. Görseli hedef TinyML boyutuna (96x96) getir
                # INTER_AREA interpolasyonu, küçültme işlemlerinde en net sonucu verir
                resized_img = cv2.resize(img, (TARGET_WIDTH, TARGET_HEIGHT), interpolation=cv2.INTER_AREA)

                # 3. İşlenmiş görseli hedef klasöre kaydet
                cv2.imwrite(target_image_file_path, resized_img)

                class_processed_counter += 1
                total_processed_counter += 1

            except Exception as error:
                print(f"   [HATA] {file_name} işlenirken bir sorun oluştu: {error}")

        print(f"  └─ {class_name} sınıfından {class_processed_counter} adet görsel başarıyla optimize edildi.\n")

    print("==============================================================================")
    print(f"[BAŞARILI] İşlem tamamlandı! Toplam {total_processed_counter} görsel 96x96 boyutuna getirildi.")
    print(f"Hedef Klasör: {OUTPUT_DATASET_DIR}")
    print("Artık bu klasörü Edge Impulse sistemine yüklemeye hazırsınız.")
    print("==============================================================================")


# ==============================================================================
# 3. ANA ÇALIŞTIRMA BLOKU
# ==============================================================================
if __name__ == "__main__":
    preprocess_images()