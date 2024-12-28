#include <iostream>
#include <vector>
#include <random>


/**
* @brief Создание случайного числа в диапазоне
* @param min Минимальное значение
* @param max Максимальное значение
* @return Случайное число
*/
int generate_random(const int min, const int max);


/**
* @brief Возведение числа в степень по модулю, для избегания переполнения
* @param value Число для возведения в степень
* @param exp Степерь
* @param mod Подуль для вычислений
* @return Число в степень по модулю
*/
int modular_exp(int value, int exp, int mod);


/**
* @brief Простое ли число методом Ферма
* @param t Параметр надежности
* @return true - число простое, иначе false
*/
bool fermat(const int n, const int t);


/**
* @brief Вычисление символа Якоби
* @param a Параметр a
* @param n Параметр n
* @return Значение символа Якоби
*/
int jacobi_sign(int a, int n);


/**
* @brief Простое ли число методом Соловея-Штрассена
* @param t Параметр надежности
* @return true - число простое, иначе false
*/
bool solovai_strassen(const int n, const int t);


/**
* @brief Простое ли число методом Миллера-Рабина
* @param t Параметр надежности
* @return true - число простое, иначе false
*/
bool miller_rabin(const int n, const int t);


int main()
{
	int t = 20;
	int value = 113;
	bool fermat_result = fermat(value, t);
	bool solovai_strassen_result = solovai_strassen(value, t);
	bool miller_rabin_result = miller_rabin(value, t);
	std::cout << "Fermat test: " << fermat_result << std::endl;
	std::cout << "Solovay-Strassen test: " << solovai_strassen_result << std::endl;
	std::cout << "Miller-Rabin test: " << miller_rabin_result << std::endl;
	return 0;
}

int generate_random(const int min, const int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> uniformIntDistribution(min, max);
	return uniformIntDistribution(gen);
}

int modular_exp(int value, int exp, int mod) {
	int result = 1;
	value = value % mod;
	while (exp > 0) {
		if (exp % 2 == 1) {
			result = (result * value) % mod;
		}
		value = (value * value) % mod;
		exp /= 2;
	}
	return result;
}

bool fermat(const int n, const int t)
{
	for (size_t i = 0; i < t; i++)
	{
		int a = generate_random(2, n - 2);
		int r = modular_exp(a, n - 1, n);
		if (r != 1)
			return false;
	}
	return true;
}

int jacobi_sign(int a, int n)
{
	if (a == 0)
	{
		return a;

	}
	else if (a == 1)
	{
		return a;
	}
	else
	{
		int s;
		int counter = 0;
		while (a % 2 == 0)
		{
			a = a / 2;
			counter += 1;
		}
		if (counter % 2 == 0)
		{
			s = 1;
		}
		else if ((n % 8 == 1) or (n % 8 == 7))
		{
			s = 1;
		}
		else
		{
			s = -1;
		}
		if ((n % 4 == 3) and (a % 4 == 3))
		{
			s = -s;
		}
		if (a == 1)
		{
			return s;
		}
		else
		{
			return s * jacobi_sign(n % a, a);
		}
	}
}

bool solovai_strassen(const int n, const int t)
{
	for (size_t i = 0; i < t; i++)
	{
		int a = generate_random(2, n - 2);
		int r = modular_exp(a, (n - 1) / 2, n);
		if (r != 1 && r != n - 1)
			return false;
		if (r == n - 1)
		{
			r = -1;
		}
		int s = jacobi_sign(a, n);
		if (r != s)
			return false;
	}
	return true;
}

bool miller_rabin(const int n, const int t)
{
	int r = n - 1;
	int s = 0;
	while (r % 2 == 0) {
		r /= 2;
		s++;
	}
	for (size_t i = 0; i < t; i++)
	{
		int b = generate_random(2, n - 2);
		int y = modular_exp(b, r, n);
		if (y != 1 && y != -1)
		{
			int j = 1;
			while (j < s && y != n - 1)
			{
				y = modular_exp(y, 2, n);
				if (y == 1)
					return false;
				j++;
			}
			if (y != n - 1)
				return false;
		}
	}
	return true;
}