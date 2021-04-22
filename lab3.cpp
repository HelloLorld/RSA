#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <ctime>

#define int64 long long int

int64 generation(int A, int B);		//Генерация простого числа
int NOD(int64 a, int64 b);			//Поиск НОД
int64 findE(int64 fEil);			//Поиск числа е для ключа
int64 findD(int64 e, int64 fEil);	//Поиск числа d для ключа
int64 degree(int64, int64, int64);	//Возведение в степень по модулю
std::vector<int64> encryption(std::string encrypted, int64 e, int64 n); //Шифрование
std::string decryption(std::vector<int64> cipher, int64 d, int64 n);	//Расшифрование
bool primeNumber(int64);			//Проверка простоты числа
int64 binaryNumber(int);			//Перевод в двоичную систему счисления
int numberFromBinary(int64);		//Перевод в десятичную систему счисления

int main()
{
	std::string encrypted;				//Шифруемая строка
	std::vector<int64> cipher;			//Зашифрованные блоки строки
	std::string original;				//Расшифрованная строка
	std::cout << "Enter your string: ";
	std::getline(std::cin, encrypted);
	int64 fEil,p,q,n = 0;
		 p = generation(0, 15000);		//Два простых числа p и q
		 q = 0;
		 while (true)
		 {
			 q = generation(0, 15000);
			 if (q != p) break;
		 }
		 n = p * q;						//Модуль p и q

		 fEil = (p - 1) * (q - 1);		//Функция Эйлера для p и q
	long e = 0;							//Число e (простое, меньше fEil, взаимно простое с fEil)
	while (true)
	{
		e = findE(fEil);
		if (e != q) break;
	}
	long d = 0;							//Число d обратное e по модулю fEil
	d = findD(e, fEil);
	cipher = encryption(encrypted, e, n);
	original = decryption(cipher, d, n);
	std::cout << "p: " << p << "\t" << "q: " << q << "\t" << "n: " << n << "\t" << "fEil: " << fEil << "\t" << "e: " << e << "\t" << "d: " << d;
	std::cout << "\nYour text in blocks: ";
	for (int i = 0; i < cipher.size(); i++)
	{
		std::cout << cipher[i] << "\t";
		if (i % 3 == 0) std::cout << "\n";
	}
	std::cout << "\nYour original text: " << original;
	return 0;
}

//{e,n} открытый ключ

std::vector<int64> encryption(std::string encrypted, int64 e,int64 n)
{//Функция шифрования
	std::vector <int64> number;
	for (int i = 0; i < encrypted.length(); i++)
	{
		int64 symbol = binaryNumber(encrypted[i]);
		int a = degree(symbol, e, n);
		number.push_back(a);
	}
	return number;
}

//{d,n} закрытый ключ 
std::string decryption(std::vector<int64> cipher, int64 d, int64 n)
{//Функция расшифровки
	std::string original;
	for (int i = 0; i < cipher.size(); i++)
	{
		int64 symbol = cipher[i];
		int a = numberFromBinary(degree(symbol, d, n));
		original += (char)a;
	}
	return original;
}

int64 generation(int A,int B)
{//Функция генерации простых чисел
	srand(time(NULL));
	long number = 0;
	while (true)
	{
		bool exit = true;
		number = A + rand() % B;
		exit = primeNumber(number);
		if (exit) break;
	}
	return number;
}

int64 binaryNumber(int number)
{//Перевод в двоичную
	int binary = 0;
	std::string str;
	std::stringstream ss;
	std::string strNumber;
	while (number)
	{
		ss << number % 2;
		number /= 2;
		ss >> str;
		strNumber += str;
		ss.clear();
	}
	std::reverse(strNumber.begin(), strNumber.end());
	binary = atoi(strNumber.c_str());
	return binary;
}

int numberFromBinary(int64 number)
{//Перевод в десятичную
	int decimal = 0;
	std::string str;
	std::stringstream ss;
	ss << number;
	ss >> str;
	std::reverse(str.begin(), str.end());
	for (int i = 0; i < str.length(); i++)
	{
		std::string multiplier;
		multiplier+= str[i];
		decimal += degree(2,i,10000)*atoi(multiplier.c_str());
	}
	return decimal;
}

bool primeNumber(int64 number)
{//Проверка простоты числа
	for (int i = 2; i < number - 1; i++)
	{
		if ((number % i == 0))
		{
			return false;
		}
	}
	return true;
}

int NOD(int64 a, int64 b)
{//Функция нахождения наибольшего общего делителя
	while (a > 0 && b > 0)

		if (a > b)
			a %= b;
		else
			b %= a;

	return a + b;
}

int64 findE(int64 fEil)
{//Функция поиска числа e для открытого ключа
	int64 e = 0;
	while (true)
	{
		e = generation(0, 15000);
		if ((e < fEil) && (NOD(e, fEil) == 1)) 
		{
			return e;
		}
	}
}

int64 findD(int64 e, int64 fEil)
{//Функция поиска чилса d для закрытого ключа
	int64 D = 1;
	while (true)
	{
		if (((D * e) % fEil == 1)&&D!=e) break;
		else D++;
	}
	return D;
}


int64 degree(int64 a, int64 b,int64 m)
{//Функция возведения в степень и нахождения остатка
		int64 r = 1;
		while (b) {
			if (b & 1) {
				r *= a;
				r %= m;
			}
			a *= a;
			a %= m;
			b >>= 1;
		}
		return r;
}

