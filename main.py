import serial
import pygame
import os
import time

# Ses sistemini başlat
pygame.mixer.init()

PORT = 'COM3'
BAUD_RATE = 9600

try:
    arduino = serial.Serial(PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Bağlantının oturması için bekle
    print("Sistem Basariyla Baslatildi... Dinleniyor.")
except serial.SerialException:
    print(f"Hata: {PORT} portuna ulaşılamadı!")
    exit()


def ses_cal(renk):
    # 'renk' verisini temizle ve dosya uzantısını kontrol et
    dosya = os.path.join("voice", f"{renk.lower()}.mp3")

    if os.path.exists(dosya):
        try:
            pygame.mixer.music.load(dosya)
            pygame.mixer.music.play()
            while pygame.mixer.music.get_busy():
                time.sleep(0.1)
        except Exception as e:
            print(f"Ses çalma hatası: {e}")
    else:
        # Eğer dosya yoksa, sistemin çökmesini engellemek için sessiz kal
        print(f"Uyarı: '{renk}' için ses dosyası bulunamadı!")


try:
    while True:
        if arduino.in_waiting > 0:
            veri = arduino.readline().decode('utf-8', errors='ignore').strip()

            # Veri gelmişse ve bizim tanımladığımız bir renkse işlem yap
            if veri and veri != "Bilinmiyor":
                print(f"Algilanan Renk: {veri}")
                ses_cal(veri)

except KeyboardInterrupt:
    print("\nProgram kullanıcı tarafından sonlandırıldı.")
finally:
    # Program kapanırken portu güvenli şekilde kapat
    if 'arduino' in locals() and arduino.is_open:
        arduino.close()
        print("Seri port kapatıldı.")
    pygame.mixer.quit()