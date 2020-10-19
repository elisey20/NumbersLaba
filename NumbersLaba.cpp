﻿#include <iostream>
#include <fstream>

using namespace std;

const int NumberOfDigits = 34;

struct TLong
{
	unsigned short dataInt[NumberOfDigits] = { 0 };
	unsigned short dataFloat[NumberOfDigits] = { 0 };
	bool sign = false;
};

bool Eq(TLong& a, TLong& b)
{
	if (a.sign != b.sign || a.dataInt != b.dataInt || a.dataFloat != b.dataFloat)
		return false;
	
	return true;
}

bool Less(TLong& a, TLong& b)
{
	if (Eq(a, b))
		return false;

	for (unsigned char i = NumberOfDigits - 1; i > 0; i--) {
		if (a.dataInt[i] > b.dataInt[i])
			return false;
	}
	
	return true;
}

bool Read_TLong(ifstream& fin, TLong& num)
{
	//текущая строка
	string str;

	fin >> str;
	cout << str << endl;

	//длина строки
	unsigned short strLength = str.length();

	//проверка на знак числа
	if (str[0] == '-') {
		num.sign = true;
		str = str.substr(1);
	}

	//поиск вещественной части числа
	int posDot = str.find('.');
	strLength = str.length();
	if (posDot < 0)
		posDot = strLength;

	//номер самой младшей ненулевой ячейки вещественной части
	num.dataFloat[0] = (strLength - posDot + 2) / 3;

	//номер самой младшей ненулевой ячейки целой части
	num.dataInt[0] = (posDot + 2) / 3;

	unsigned char j = 0;
	//текущее значение числа
	unsigned short cur = 0;
	//текущая ячейка переменной
	unsigned char curCell = 1;

	//заполнение целой части переменной
	for (signed char i = posDot - 1; i >= 0; i--) {
		cur += unsigned short((str[i] - '0') * pow(10, j));
		if (j == 2 || i == 0) {
			j = 0;
			num.dataInt[curCell] = cur;
			curCell++;
			cur = 0;
		}
		else
			j++;
	}

	j = 2;
	cur = 0;
	curCell = 1;

	//заполнение вещественной части переменной
	for (unsigned char i = posDot + 1; i <= str.length() - 1; i++) {
		cur += unsigned short((str[i] - '0') * pow(10, j));
		if (j == 0 || i == str.length() - 1) {
			j = 2;
			num.dataFloat[curCell] = cur;
			curCell++;
			cur = 0;
		}
		else
			j--;
	}

	//поиск самой крайней ненулевой ячейки целой части
	for (unsigned char i = num.dataInt[0]; i >= 1; i--) {
		if (num.dataInt[i] == 0)
			num.dataInt[0]--;
		else
			break;
	}

	//поиск самой крайней ненулевой ячейки вещественной части
	for (unsigned char i = num.dataFloat[0]; i >= 1; i--) {
		if (num.dataFloat[i] == 0)
			num.dataFloat[0]--;
		else
			break;
	}

	return false;
}

void Write_TLong(ofstream& fout, TLong num)
{
	if (num.sign)
		fout << "-";

	//для обращения к крайней ячейке числа
	char end = num.dataInt[0];

	//запись целой части числа
	fout << num.dataInt[end];
	for (char i = end - 1; i >= 1; i--) {
		if (num.dataInt[i] == 0)
			fout << "000";
		else if (num.dataInt[i] < 10)
			fout << "00" << num.dataInt[i];
		else if (num.dataInt[i] < 100)
			fout << '0' << num.dataInt[i];
		else
			fout << num.dataInt[i];
	}
	
	//запись вещественной части числа
	if (num.dataFloat[0] != 0) {
		fout << '.';
		end = num.dataFloat[0];
		for (char i = 1; i <= end - 1; i++) {
			if (num.dataFloat[i] == 0)
				fout << "000";
			else if (num.dataFloat[i] < 10)
				fout << "00" << num.dataFloat[i];
			else if (num.dataFloat[i] < 100)
				fout << '0' << num.dataFloat[i];
			else
				fout << num.dataFloat[i];
		}

		//запись последней ячейки вещественной части числа
		if (num.dataFloat[end] < 10)
			fout << "00";
		else if (num.dataFloat[end] < 100)
			fout << '0';

		//убирает ведомые нули
		if (num.dataFloat[end] % 100 == 0)
			fout << num.dataFloat[end] / 100;
		else if (num.dataFloat[end] % 10 == 0)
			fout << num.dataFloat[end] / 10;
		else
			fout << num.dataFloat[end];
		//
	}
}

TLong Sum_TLong(TLong& a, TLong& b)
{
	//результат сложения
	TLong c;
	c.sign = a.sign;

	//показывает, что нужно прибавить единицу к следующей ячейке
	bool pred = false;
	//для поиска самой младшей ненулевой ячейки
	bool dontNull = true;

	//сложение вещественной части
	for (unsigned char i = NumberOfDigits - 1; i >= 1; i--) {
		//сложение
		c.dataFloat[i] = a.dataFloat[i] + b.dataFloat[i];

		//прибавляет единицу, если в предыдущей ячейке число превышает максимально допустимое значение
		if (pred)
			c.dataFloat[i] += 1;

		//проверка на превышение числа в ячейке
		if (c.dataFloat[i] >= 1000) {
			c.dataFloat[i] -= 1000;
			pred = true;
		}
		else
			pred = false;

		//поиск самой младшей ненулевой ячейки
		if (dontNull && c.dataFloat[i] != 0) {
			c.dataFloat[0] = i;
			dontNull = false;
		}
	}

	//сложение целой части
	for (unsigned char i = 1; i <= NumberOfDigits - 1; i++) {
		//сложение
		c.dataInt[i] = a.dataInt[i] + b.dataInt[i];

		//прибавляет единицу, если в предыдущей ячейке число превышает максимально допустимое значение
		if (pred)
			c.dataInt[i] += 1;

		//проверка на превышение числа в ячейке
		if (c.dataInt[i] >= 1000) {
			c.dataInt[i] -= 1000;
			pred = true;
		}
		else
			pred = false;
	}

	//для цикла
	unsigned char i = NumberOfDigits - 1;
	dontNull = true;

	//поиск самой младшей ненулевой ячейки 
	while (i >= 1 && dontNull)
		if (c.dataInt[i] != 0) {
			c.dataInt[0] = i;
			dontNull = false;
		}
		else
			i--;

	//результат сложения
	return c;
}

TLong Sub_TLong(TLong a, TLong b)
{
	
	
	return a;

}

TLong Sum_or_Sub(TLong& a, TLong& b, char oper) 
{
	if (oper == '+') {
		// a + b
		if (a.sign == false && b.sign == false)
			return Sum_TLong(a, b);

		// a + (-b)
		if (a.sign == false && b.sign)
			return Sub_TLong(a, b);

		// (-a) + b
		if (a.sign && b.sign == false)
			return Sub_TLong(b, a);

		// (-a) + (-b)
		if (a.sign && b.sign)
			return Sum_TLong(a, b);
	}

	if (oper == '-') {
		// a - b
		if (a.sign == false && b.sign == false)
			return Sub_TLong(a, b);

		// a - (-b)
		if (a.sign == false && b.sign)
			return Sum_TLong(a, b);

		// (-a) - b
		if (a.sign && b.sign == false)
			return Sum_TLong(a, b);

		// (-a) - (-b)
		if (a.sign && b.sign)
			return Sub_TLong(b, a);
	}
	
	TLong c;
	return c;
}

int main()
{

	ifstream fin;
	ofstream fout;
	fin.open("./files/input.txt", ios_base::in);
	fout.open("./files/output.txt", ios_base::out);

	TLong a; 
	TLong b;
	string str;
	 
	Read_TLong(fin, a);
	Read_TLong(fin, b);
	Write_TLong(fout, a);

	fin.close();
	fout.close();

	return 0;
}

