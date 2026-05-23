#include "edge-impulse-sdk/classifier/ei_run_classifier.h"

extern "C" {
    // main.c'den gelen çağrıyı karşılayan fonksiyon
    int run_inference_from_c(float *features) {
        ei_impulse_result_t result = { 0 };

        // Sinyal yapısını oluştur (Edge Impulse SDK'nın beklediği format)
        signal_t signal;
        // Not: 1024, main.c'deki buffer boyutunla aynı olmalı
        int err = numpy::signal_from_buffer(features, 1024, &signal);
        if (err != 0) return -1;

        // Modeli koştur
        EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

        if (res != EI_IMPULSE_OK) {
            return -2; // Inference hatası
        }

        // En yüksek olasılıklı sınıfın indeksini dön (Örnek mantık)
        return (int)result.classification[0].label;
    }
}
