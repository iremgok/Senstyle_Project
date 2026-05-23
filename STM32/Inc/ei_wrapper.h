#ifndef INC_EI_WRAPPER_H_
#define INC_EI_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

// Kameradan gelen ham piksel verisini alıp tahmin üreten ana fonksiyonumuz
int run_inference_from_c(float *images_buffer);

#ifdef __cplusplus
}
#endif

#endif /* INC_EI_WRAPPER_H_ */
