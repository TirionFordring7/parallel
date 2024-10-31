#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include <immintrin.h> 

//#define PI 3.14159265358979323846
#define NUM_SEGMENTS 99999 // Число разбиений отрезка (надо что бы делилось на 32 общее число байт)

int main() {
    clock_t start_time, end_time; // Переменные для измерения времени
    double cpu_time; // Переменная для хранения затраченного времени

    start_time = clock(); // Начало измерения времени

    double f[NUM_SEGMENTS + 1];
    double tau, integral, alpha[NUM_SEGMENTS - 1], beta[NUM_SEGMENTS - 1], c_coeff[NUM_SEGMENTS - 1], temp = 0.0;
    int i;

    double start_val = 0.0; 
    double end_val = 100.0; // Границы интегрирования
    tau = (end_val - start_val) / NUM_SEGMENTS; // Шаг разбиения

    // Оптимизированное заполнение массива f значениями функции f(x) = cos(x) с использованием AVX2
    __m256d vec_tau = _mm256_set1_pd(tau);
    __m256d vec_start = _mm256_set1_pd(start_val);
    for(i = 0; i <= NUM_SEGMENTS; i += 4)  {
        __m256d idx = _mm256_set_pd(i+3, i+2, i+1, i);
        __m256d x = _mm256_add_pd(vec_start, _mm256_mul_pd(vec_tau, idx));
        // Ну тут уж без векторизованной экспоненты
        f[i] = exp(start_val + tau * i);
        f[i+1] = exp(start_val + tau * (i+1));
        f[i+2] = exp(start_val + tau * (i+2));
        f[i+3] = exp(start_val + tau * (i+3));
    }

    alpha[0] = -1.0 / 4.0; // Инициализация первого элемента массива alpha
    beta[0] = f[2] - 2.0 * f[1] + f[0]; // Инициализация первого элемента массива beta

    // Метод прогонки, прямой ход
    for (i = 1; i < NUM_SEGMENTS - 1; i++) {
        alpha[i] = -1.0 / (alpha[i-1] + 4.0); // Вычисление alpha[i]
        beta[i] = (f[i+2] - 2.0 * f[i+1] + f[i] - beta[i-1]) / (alpha[i-1] + 4.0); // Вычисление beta[i]
    }

    // Обратный ход метода прогонки
    c_coeff[NUM_SEGMENTS - 2] = (f[NUM_SEGMENTS] - 2.0 * f[NUM_SEGMENTS-1] + f[NUM_SEGMENTS-2] - beta[NUM_SEGMENTS - 2]) / (4.0 + alpha[NUM_SEGMENTS - 2]);
    for (i = NUM_SEGMENTS - 3; i >= 0; i--) {
        c_coeff[i] = alpha[i+1] * c_coeff[i+1] + beta[i+1]; // Вычисление c_coeff[i]
    }

    // Масштабирование коэффициентов
    __m256d vec_scale = _mm256_set1_pd(3.0 / (tau * tau));
    for(i = 0; i < NUM_SEGMENTS - 1; i += 4) {
        __m256d coeff = _mm256_loadu_pd(&c_coeff[i]);
        coeff = _mm256_mul_pd(coeff, vec_scale);
        _mm256_storeu_pd(&c_coeff[i], coeff);
    }

    // Считаем приближенное значение интеграла по формуле для равномерного разбиения:
    integral = (5.0 * f[0] + 13.0 * f[1] + 13.0 * f[NUM_SEGMENTS-1] + 5.0 * f[NUM_SEGMENTS]) / 12.0;

    // Векторизированное суммирование
    __m256d sum_vec = _mm256_setzero_pd();
    for(i = 2; i <= NUM_SEGMENTS-2; i += 4) {
        __m256d val = _mm256_loadu_pd(&f[i]);
        sum_vec = _mm256_add_pd(sum_vec, val);
    }
    double temp_array[4];
    _mm256_storeu_pd(temp_array, sum_vec);
    temp = temp_array[0] + temp_array[1] + temp_array[2] + temp_array[3];

    integral = (integral + temp) * tau - (c_coeff[0] + c_coeff[NUM_SEGMENTS - 2]) * tau * tau * tau / 36.0;

    printf("DIntegral=%.10f\n", integral);

    end_time = clock(); // Конец измерения времени
    cpu_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC; // Вычисление затраченного времени

    printf("Время выполнения программы: %.6f секунд\n", cpu_time);

    return 0;
}