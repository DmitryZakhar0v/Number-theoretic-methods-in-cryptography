#include <iostream>
#include <cmath>
#include <vector>

/*
* @brief Умножающая двух чисел методом Карацубы
* @param value_1 - Первое число
* @param value_2 - Второе число
* @param base - Основание системы исчисления
* @return Результат произведения двух чисел
*/
int karatsuba(const int value_1, const int value_2, const size_t base);


/*
* @brief Разделение числа на разряды
* @param value - Число для разделения
* @param base - Основание системы исчисления
* @return Массив разрядов
*/
std::vector<int> split_to_digits(int value, int base);


int main()
{
    int a = 12;
    int b = 25;
    size_t base = 10;
    int result = karatsuba(a, b, base);
    std::cout << "Result: " << result;
    return 0;
}

std::vector<int> split_to_digits(int value, int base)
{
    std::vector<int> vector;
    while (value != 0)
    {
        vector.insert(vector.begin(), value % base);
        value /= base;
    }
    if (vector.size() % 2 != 0)
    {
        vector.insert(vector.begin(), 0);
    }
    return vector;
}

int karatsuba(const int value_1, const int value_2, const size_t base)
{
    std::vector<int> u_dig;
    std::vector<int> v_dig;
    u_dig = split_to_digits(value_1, base);
    v_dig = split_to_digits(value_2, base);
    size_t n = u_dig.size() / 2;
    int v_0 = 0;
    int v_1 = 0;
    int u_0 = 0;
    int u_1 = 0;
    for (size_t i = 0; i < n; i++)
    {
        u_1 += u_dig[n - i - 1] * pow(base, i);
        u_0 += u_dig[2 * n - i - 1] * pow(base, i);
        v_1 += v_dig[n - i - 1] * pow(base, i);
        v_0 += v_dig[2 * n - i - 1] * pow(base, i);
    }
    int A = v_1 * u_1;
    int B = v_0 * u_0;
    int C = (u_1 + u_0) * (v_1 + v_0);
    int result = (A * pow(base, n + n)) + ((C - A - B) * pow(base, n)) + B;
    return result;
}

