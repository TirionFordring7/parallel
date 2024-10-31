#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//#define PI 3.14159265358979323846
#define NUM_SEGMENTS 99999 // Число разбиений отрезка

int main() {
    clock_t start_time, end_time; // Переменные для измерения времени
    double cpu_time; // Переменная для хранения затраченного времени

    start_time = clock(); // Начало измерения времени

    double long f[NUM_SEGMENTS + 1];
    double long tau, integral, alpha[NUM_SEGMENTS - 1], beta[NUM_SEGMENTS - 1], c_coeff[NUM_SEGMENTS - 1], temp = 0.0;
    int i;

    double long start = 0.0; 
    double long end = 100.0; // Границы интегрирования
    tau = (end - start) / NUM_SEGMENTS; // Шаг разбиения

    // Заполнение массива f значениями функции f(x) = sin(x)
    for(i = 0; i <= NUM_SEGMENTS; i++)  {
        double long x = start + tau * i;
        f[i] = exp(x); // Функция f(x)
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
    for(i = 0; i < NUM_SEGMENTS - 1; i++) {
        c_coeff[i] = c_coeff[i] * 3.0 / (tau * tau);
    }

    // Считаем приближенное значение интеграла по формуле для равномерного разбиения:
    integral = (5.0 * f[0] + 13.0 * f[1] + 13.0 * f[NUM_SEGMENTS-1] + 5.0 * f[NUM_SEGMENTS]) / 12.0;

    // Суммирование
    for(i = 2; i < NUM_SEGMENTS-1; i++) {
        temp += f[i];
    }
    integral = (integral + temp) * tau - (c_coeff[0] + c_coeff[NUM_SEGMENTS - 2]) * tau * tau * tau / 36.0;

    printf("DIntegral=%.10Lf\n", integral);

    end_time = clock(); // Конец измерения времени
    cpu_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC; // Вычисление затраченного времени

    printf("Время выполнения программы: %.6f секунд\n", cpu_time);

    return 0;
}