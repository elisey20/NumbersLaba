#include <iostream>
#include <fstream>
#include "Structs.h"

bool Eq(TLong& a, TLong& b)
{
	if (a.sign != b.sign || a.dataInt != b.dataInt || a.dataFloat != b.dataFloat)
		return false;

	return true;
}

bool Less(TLong& a, TLong& b)
{
	//���� � �����, b �����
	if (a.sign == true && b.sign == false)
		return true;

	//���� � �����, b �����
	else if (a.sign == false && b.sign == true)
		return false;

	//����������� ���������� � ����� �����
	for (unsigned char i = NumberOfDigits - 1; i > 0; i--) {
		if (a.dataInt[i] > b.dataInt[i])
			return false;
		else if (a.dataInt[i] < b.dataInt[i])
			return true;
	}

	//����������� ���������� � ������� �����
	for (unsigned char i = 1; i < NumberOfDigits; i++) {
		if (a.dataFloat[i] > b.dataFloat[i])
			return false;
		else if (a.dataFloat[i] < b.dataFloat[i])
			return true;
	}

	//���� ����� �����
	return false;
}

bool Read_TLong(string& str, TLong& num)
{
	//������� ������
	/*string str;

	fin >> str;
	cout << str << endl;*/

	//����� ������
	unsigned short strLength = str.length();

	//�������� �� ���� �����
	if (str[0] == '-') {
		num.sign = true;
		str = str.substr(1);
	}

	//����� ������������ ����� �����
	int posDot = str.find('.');
	strLength = str.length();
	if (posDot < 0)
		posDot = strLength;

	//����� ����� ������ ��������� ������ ������������ �����
	num.dataFloat[0] = (strLength - posDot + 2) / 3;

	//����� ����� ������� ��������� ������ ����� �����
	num.dataInt[0] = (posDot + 2) / 3;

	unsigned char j = 0;
	//������� �������� �����
	unsigned short cur = 0;
	//������� ������ ����������
	unsigned char curCell = 1;

	//���������� ����� ����� ����������
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

	//���������� ������������ ����� ����������
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

	//����� ����� ������� ��������� ������ ����� �����
	for (unsigned char i = num.dataInt[0]; i >= 1; i--) {
		if (num.dataInt[i] == 0)
			num.dataInt[0]--;
		else
			break;
	}

	//����� ����� ������� ��������� ������ ������������ �����
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

	//��� ��������� � ������� ������ �����
	char end = num.dataInt[0];

	//������ ����� ����� �����
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

	//������ ������������ ����� �����
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

		//������ ��������� ������ ������������ ����� �����
		if (num.dataFloat[end] < 10)
			fout << "00";
		else if (num.dataFloat[end] < 100)
			fout << '0';

		//������� ������� ����
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
	//��������� ��������
	TLong c;
	c.sign = a.sign;

	//����������, ��� ����� ��������� ������� � ��������� ������
	bool pred = false;
	//��� ������ ����� ������� ��������� ������
	bool dontNull = true;

	//�������� ������������ �����
	for (unsigned char i = NumberOfDigits - 1; i >= 1; i--) {
		//��������
		c.dataFloat[i] = a.dataFloat[i] + b.dataFloat[i];

		//���������� �������, ���� � ���������� ������ ����� ��������� ����������� ���������� ��������
		if (pred)
			c.dataFloat[i] += 1;

		//�������� �� ���������� ����� � ������
		if (c.dataFloat[i] >= 1000) {
			c.dataFloat[i] -= 1000;
			pred = true;
		}
		else
			pred = false;

		//����� ����� ������� ��������� ������
		if (dontNull && c.dataFloat[i] != 0) {
			c.dataFloat[0] = i;
			dontNull = false;
		}
	}

	//�������� ����� �����
	for (unsigned char i = 1; i <= NumberOfDigits - 1; i++) {
		//��������
		c.dataInt[i] = a.dataInt[i] + b.dataInt[i];

		//���������� �������, ���� � ���������� ������ ����� ��������� ����������� ���������� ��������
		if (pred)
			c.dataInt[i] += 1;

		//�������� �� ���������� ����� � ������
		if (c.dataInt[i] >= 1000) {
			c.dataInt[i] -= 1000;
			pred = true;
		}
		else
			pred = false;
	}

	//��� �����
	unsigned char i = NumberOfDigits - 1;
	dontNull = true;

	//����� ����� ������� ��������� ������ 
	while (i >= 1 && dontNull)
		if (c.dataInt[i] != 0) {
			c.dataInt[0] = i;
			dontNull = false;
		}
		else
			i--;

	//��������� ��������
	return c;
}

TLong Sub_TLong(TLong a, TLong b)
{
	//���� a == b ������� 0
	TLong c;
	if (Eq(a, b))
		return c;

	//���� b > a ������� b - a �� ������ �����
	if (Less(a, b)) {
		c = Sub_TLong(b, a);
		c.sign = true;
		return c;
	}

	//����������, ��� ����� ������ ������� �� ��������� ������
	bool pred = false;

	//��� ������ ����� ������� ��������� ������
	bool dontNull = true;

	//�������� ������������ �����
	for (unsigned char i = NumberOfDigits - 1; i >= 1; i--) {
		//���������
		c.dataFloat[i] = a.dataFloat[i] + 1000 - b.dataFloat[i];

		//�������� �������, ���� � ���������� ������ ����� �� ��������� ���������� ���������� ��������
		if (pred)
			c.dataFloat[i] -= 1;

		//�������� �� ���������� ����� � ������
		if (c.dataFloat[i] >= 1000) {
			c.dataFloat[i] -= 1000;
			pred = false;
		}
		else
			pred = true;;

		//����� ����� ������� ��������� ������
		if (dontNull && c.dataFloat[i] != 0) {
			c.dataFloat[0] = i;
			dontNull = false;
		}
	}

	//��������� ����� �����
	for (unsigned char i = 1; i <= NumberOfDigits - 1; i++) {
		//���������
		c.dataInt[i] = a.dataInt[i] + 1000 - b.dataInt[i];

		//�������� �������, ���� � ���������� ������ ����� �� ��������� ���������� ���������� ��������
		if (pred)
			c.dataInt[i] -= 1;

		//�������� �� ���������� ����� � ������
		if (c.dataInt[i] >= 1000) {
			c.dataInt[i] -= 1000;
			pred = false;
		}
		else
			pred = true;
	}

	//��� �����
	unsigned char i = NumberOfDigits - 1;
	dontNull = true;

	//����� ����� ������� ��������� ������ 
	while (i >= 1 && dontNull)
		if (c.dataInt[i] != 0) {
			c.dataInt[0] = i;
			dontNull = false;
		}
		else
			i--;

	//��������� ���������
	return c;

	return a;

}

TLong Sum_or_Sub(TLong a, char oper, TLong& b)
{
	if (oper == '+') {
		// a + b
		if (a.sign == false && b.sign == false)
			return Sum_TLong(a, b);

		// a + (-b)
		if (a.sign == false && b.sign) {
			b.sign = false;
			return Sub_TLong(a, b);
		}

		// (-a) + b
		if (a.sign && b.sign == false) {
			a.sign = false;
			return Sub_TLong(b, a);
		}

		// (-a) + (-b)
		if (a.sign && b.sign)
			return Sum_TLong(a, b);
	}

	if (oper == '-') {
		// a - b
		if (a.sign == false && b.sign == false)
			return Sub_TLong(a, b);

		// a - (-b)
		if (a.sign == false && b.sign) {
			b.sign = false;
			return Sum_TLong(a, b);
		}

		// (-a) - b
		if (a.sign && b.sign == false)
			return Sum_TLong(a, b);

		// (-a) - (-b)
		if (a.sign && b.sign) {
			b.sign = false;
			a.sign = false;
			return Sub_TLong(b, a);
		}
	}

	TLong c;
	return c;
}

ETAR Read_str(ifstream& fin, string& str)
{
	if (str[0] == '-' || str[0] == '+')
		return ETAR::OPERATOR;
	//�������� ����������� ���� ����� 

	return ETAR::ERROR;
}