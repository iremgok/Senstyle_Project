// EDGE IMPULSE KLASÖRÜNÜ VE DOSYALARINI SADECE BURADA VE "extern C" İÇİNDE BAĞLIYORUZ:
extern "C" {
	#include "classifier/ei_run_classifier.h"
}

#include <string.h>

// Lambda sorununu çözmek için veriyi güvenli bir şekilde paylaşacak statik işaretçi
static float *current_images_buffer = NULL;

// Edge Impulse'ın ham veriyi okumak için beklediği standart C tipi fonksiyon
static int get_signal_data(size_t offset, size_t length, float *out_ptr) {
    if (current_images_buffer == NULL) {
        return -1;
    }
    memcpy(out_ptr, current_images_buffer + offset, length * sizeof(float));
    return 0;
}

extern "C" int run_inference_from_c(float *images_buffer) {
    // Gelen buffer işaretçisini statik değişkene aktarıyoruz
    current_images_buffer = images_buffer;

    signal_t signal;
    signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;

    // Fonksiyon işaretçisini doğrudan güvenli bir şekilde bağlıyoruz
    signal.get_data = &get_signal_data;

    ei_impulse_result_t result = { 0 };

    // Modeli kart üzerinde koşturuyoruz
    EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);
    if (res != EI_IMPULSE_OK) {
        return -1; // Eğitim kodunda veya modelde hata oluştu
    }

    // En yüksek olasılığa sahip desen sınıfını buluyoruz
    int max_idx = 0;
    float max_val = result.classification[0].value;
    for (size_t ix = 1; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        if (result.classification[ix].value > max_val) {
            max_val = result.classification[ix].value;
            max_idx = ix;
        }
    }

    return max_idx; // Çıktı: Örn: 0->CICEK, 1->CIZGILI, 2->DUZ...
}
