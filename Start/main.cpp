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

/*
* @brief Умножающая двух чисел методом Тоома-Кука
* @param value_1 - Первое число
* @param value_2 - Второе число
* @param base - Основание системы исчисления
* @param r - Кол-во разрядов
* @return Результат произведения двух чисел
*/
int Toom_Cook(const int value_1, const int value_2, const size_t base, const size_t r);

/*
* @brief Разделение числа на разряды
* @param value - Число для разделения
* @param base - Основание системы исчисления
* @return Массив разрядов (dobule)
*/
std::vector<double> split_to_digits_double(int value, int base);

/*
* @brief Вычисление в точке полинома представленного ввиде массива 
* @param vector - Массив коэф. полинома
* @param value - Значение в котором его необходимо вычислить
* @return Значение полинома в заданной точке
*/
double calc_in_point(const std::vector<double>& vector, const int value);

/*
* @brief Вычисление коэффициентов полинома Ньютона
* @param vector - Массив значений в точках
* @return Коэф. полинома Ньютона
*/
std::vector<double> newton_coefficients(const std::vector<double>& vector);

/*
* @brief Перемножение двух полиномов
* @param vector_1 - Массив коэф. первого полинома
* @param vector_2 - Массив коэф. второго полинома
* @return Массив коэф. результирующего полинома
*/
std::vector<double> mul_poly(const std::vector<double>& vector_1, const std::vector<double>& vector_2);

/*
* @brief Сложение двух полиномов
* @param vector_1 - Массив коэф. первого полинома
* @param vector_2 - Массив коэф. второго полинома
* @return Массив коэф. результирующего полинома
*/
std::vector<double> add_poly(const std::vector<double>& vector_1, const std::vector<double>& vector_2);

int main()
{
    int a = 12;
    int b = 25;
    size_t base = 10;
    int result = Toom_Cook(a, b, base, 2);
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

std::vector<double> split_to_digits_double(int value, int base)
{
    std::vector<double> vector;
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

int Toom_Cook(const int value_1, const int value_2, const size_t base, const size_t r)
{
    std::vector<double> u_digits = split_to_digits_double(value_1, base);
    std::vector<double> v_digits = split_to_digits_double(value_2, base);

    std::vector<double> w_at_point;
    for (size_t i = 0; i <= 2 * r; ++i)
    {
        int u_at_point = calc_in_point(u_digits, i);
        int v_at_point = calc_in_point(v_digits, i);
        w_at_point.push_back(u_at_point * v_at_point);
    }
    std::vector<double> coef = newton_coefficients(w_at_point);
    std::vector<double> w_result{};
    std::vector<double> term{ 1 };
    for (size_t i = 0; i < coef.size(); i++) {
        std::vector<double> temp_1 = mul_poly(term, std::vector <double> {coef[i]});
        w_result = add_poly(w_result, temp_1);
        std::vector<double> factor{ 1, -static_cast<double>(i) };
        term = mul_poly(term, factor);
    }

    double y = 0;
    for (size_t i = 0; i < w_result.size(); i++)
    {
        y += w_result[w_result.size() - 1 - i] * pow(base, i);
    }
    return y;
}

std::vector<double> newton_coefficients(const std::vector<double>& vector)
{
    size_t n = vector.size();
    std::vector<double> coef = vector;
    for (size_t j = 1; j < n; ++j) {
        for (size_t i = n - 1; i >= j; --i) {
            coef[i] = (coef[i] - coef[i - 1]) / j;
        }
    }
    return coef;
}

std::vector<double> mul_poly(const std::vector<double>& vector_1, const std::vector<double>& vector_2)
{
    int new_degree = vector_1.size() + vector_2.size() - 2;
    std::vector<double> result(new_degree + 1, 0);
    for (int i = 0; i < vector_1.size(); ++i) {
        for (int j = 0; j < vector_2.size(); ++j) {
            result[i + j] += vector_1[i] * vector_2[j];
        }
    }
    return result;
}

std::vector<double> add_poly(const std::vector<double>& vector_1, const std::vector<double>& vector_2)
{
    std::vector<double> result;
    int delta = vector_1.size() - vector_2.size();
    if (vector_1.size() > vector_2.size())
    {
        for (size_t i = 0; i < vector_1.size(); ++i)
        {
            if (i < delta)
            {
                result.push_back(vector_1[i]);
            }
            else
            {
                result.push_back(vector_1[i] + vector_2[i - delta]);
            }
        }
    }
    if (vector_1.size() < vector_2.size())
    {
        for (size_t i = 0; i < vector_2.size(); ++i)
        {
            if (i < -delta)
            {
                result.push_back(vector_2[i]);
            }
            else
            {
                result.push_back(vector_2[i] + vector_1[i + delta]);
            }
        }
    }
    if (vector_1.size() == vector_2.size())
    {
        for (size_t i = 0; i < vector_1.size(); ++i)
        {
            result.push_back(vector_2[i] + vector_1[i]);
        }
    }
    return result;
}

double calc_in_point(const std::vector<double>& vector, const int value)
{
    double result = 0;
    int degree = vector.size() - 1;
    for (int i = 0; i <= degree; ++i) {
        result += vector[i] * std::pow(value, degree - i);
    }
    return result;
}
