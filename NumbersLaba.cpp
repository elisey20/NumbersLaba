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
	TLong Sum;
	char oper;
	string str;
	unsigned short NumberOfString = 1;
	ETAR etar;
	
	while (!fin.eof()) {
		etar = Read_str(fin, str);
		if (etar == ETAR::NUMBER)
			Read_TLong(str, num);
		else if (etar == ETAR::OPERATOR)
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

