#ifndef _TEST
#define _TEST

#include <openssl/rand.h>
#include <math.h>

void test_pcg();
double bench_pcg_c(size_t n, size_t t, size_t c);

void sample_a_and_a2(uint8_t *fft_a, uint32_t *fft_a2, size_t poly_size, size_t c);

#endif
