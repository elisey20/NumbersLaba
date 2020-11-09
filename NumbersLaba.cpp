#include <iostream>
#include <fstream>
#include <string>
#include "Methods.h"

int main()
{

	ifstream fin;
	ofstream fout;
	fin.open("./files/input.txt", ios_base::in);
	fout.open("./files/output.txt", ios_base::out);
	
	//текущее число
	TLong num; 
	//сумма выражения
	TLong SUM;
	//текущий оператор
	char oper = 0;
	//текущая строка
	string str;
	//тип строки (оператор, число или с ошибкой)
	ETAR etar;
	//тип предыдущей строки
	ETAR etarPrevious = ETAR::FIRST;
	//номер текущей строки
	unsigned short NumberOfString = 1;
	//если ошибка то завершаем программу
	bool isTrue = true;

	while (getline(fin, str) && isTrue) {
		etar = Try_Read_Str(str);
		if (etar == ETAR::NUMBER) {
			//если встретилось два раза число и между ними оператор то вызываем метод сложения-вычитания
			if (etarPrevious == ETAR::NUMBER) {
				cout << "input error on line " << NumberOfString << ". 2 numbers entered in a row";
				isTrue = false;
			}
			else if (etarPrevious == ETAR::OPERATOR) {
				Read_TLong(str, num);
				SUM = Sum_or_Sub(SUM, oper, num);
			}
			else
				Read_TLong(str, SUM);
			etarPrevious = ETAR::NUMBER;
		}
		else if (etar == ETAR::OPERATOR) {
			//запоминаем в переменую. Если оператор встретился два раза подрят то ошибка
			oper = str[0];
			if (etarPrevious == ETAR::OPERATOR) {
				cout << "input error on line " << NumberOfString << ". 2 operators entered in a row";
				isTrue = false;
			}
			else if (etarPrevious == ETAR::FIRST) {
				cout << "input error on line " << NumberOfString << ". The first line must be a number";
			}
			etarPrevious = ETAR::OPERATOR;
		}
		else {
			isTrue = false;
		}
		NumberOfString++;
	}

	if (isTrue)
		Write_TLong(fout, SUM);

	fin.close();
	fout.close();

	return 0;
}

