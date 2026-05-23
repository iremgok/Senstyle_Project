#include "main.h"
#include <stdio.h>
#include <string.h>

/*
 * ÖNEMLİ: Edge Impulse kütüphanesini burada doğrudan include ETMİYORUZ.
 * Bunun yerine, edge_impulse_glue.cpp içinde tanımladığımız C-wrapper
 * fonksiyonunu 'extern' ile bildiriyoruz.
 */
extern int run_inference_from_c(float *features);

// Donanım Sürücü Tanımlamaları
UART_HandleTypeDef huart1;

// Fonksiyon Prototipleri
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

// printf'i UART1'e bağlayan fonksiyon
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

// Model girişi için buffer
#define EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE 1024
float camera_features_buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

int main(void) {
    // 1. STM32 Donanım Katmanını Başlat
    HAL_Init();

    // 2. Çipi Saat Ayarını Yap
    SystemClock_Config();

    // 3. İletişim ve GPIO ayarlarını başlat
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    printf("=== StyleSight Akilli Kalem Yapay Zeka Sistemi Baslatildi ===\r\n");

    while (1) {
        // [ADIM] Modelimizi koştur ve tahmini al
        int predicted_class = run_inference_from_c(camera_features_buffer);

        // [ADIM] Sonucu bilgisayara gönder
        if (predicted_class >= 0) {
            printf("Tahmin Edilen Kumas Deseni ID: %d\r\n", predicted_class);
        } else {
            printf("Yapay zeka model hatasi olustu!\r\n");
        }

        HAL_Delay(500);
    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

static void MX_USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK) {
        // Hata durumunda burası eklenebilir
    }
}

static void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();
}
