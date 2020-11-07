#include <iostream>
#include <fstream>
#include "Methods.h"

int main()
{

	ifstream fin;
	ofstream fout;
	fin.open("./files/input.txt", ios_base::in);
	fout.open("./files/output.txt", ios_base::out);
	
	TLong num; 
	TLong SUN;
	char oper;
	string str;
	unsigned short NumberOfString = 1;
	ETAR etar;
	str = "1\n";
	cout << str.length();
	while (!fin.eof()) {\
		//сделать передачу строки в метод без передачи входного файла
		etar = Read_str(fin, str);
		if (etar == ETAR::NUMBER)
			//если встретилось два раза число и между ними оператор то вызываем метод сложения-вычитания
			Read_TLong(str, num);
		else if (etar == ETAR::OPERATOR)
			//запоминаем в переменую. Если оператор встретился два раза подрят то ошибка
			oper = str[0];
		else {
			cout << "Input error on line " << NumberOfString << "! Enter a number or operator (+, -)" << endl;
			return 1;
		}
		NumberOfString++;
	}

	fin.close();
	fout.close();

	return 0;
}

