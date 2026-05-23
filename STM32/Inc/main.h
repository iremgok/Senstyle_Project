#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

// STM32'nin donanım sürücü kütüphanesini projeye dahil ediyoruz
#include "stm32f4xx_hal.h"

void Error_Handler(void);
int run_inference_from_c(float *images_buffer);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
