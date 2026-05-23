#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h" // Not: Eğer F4 serisi değilse, kendi MCU serinizin HAL başlığını yazın (Örn: stm32l4xx_hal.h)

// Eğer logları UART üzerinden terminale basmak isterseniz main.c'deki uart handler'ınızı buraya bağlayın:
// extern "C" UART_HandleTypeDef huart1;

extern "C" {

    // 1. Edge Impulse'ın log yazdırma fonksiyonu
    void ei_printf(const char *format, ...) {
        static char buffer[256];
        va_list args;
        va_start(args, format);
        int len = vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        if (len > 0) {
            // İsteğe bağlı: UART terminal çıkışı için alt satırı aktif edebilirsiniz
            // HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len, HAL_MAX_DELAY);
        }
    }

    // 2. Edge Impulse'ın float değerleri yazdırmak için aradığı özel fonksiyon
    void ei_printf_float(float f) {
        ei_printf("%f", f);
    }

    // 3. Zamanlayıcı fonksiyonu (Mikrosaniye cinsinden)
    uint64_t ei_read_timer_us(void) {
        return (uint64_t)HAL_GetTick() * 1000;
    }

    // 4. Çıkarım iptal kontrol mekanizması (Sürekli çalışması için false dönmeli)
    bool ei_run_impulse_check_canceled(void) {
        return false;
    }

    // 5. SDK'nın ihtiyaç duyabileceği temel bellek yönetim fonksiyonları
    void *ei_malloc(size_t size) {
        return malloc(size);
    }

    void *ei_calloc(size_t nitems, size_t size) {
        return calloc(nitems, size);
    }

    void ei_free(void *ptr) {
        free(ptr);
    }
}
