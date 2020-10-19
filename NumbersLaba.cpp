#include <iostream>
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

    for (unsigned char i = 1; i < NumberOfDigits; i++) {
        if (a.dataInt[i] > b.dataInt[i] || a.dataFloat[i] > b.dataFloat[i])
            return false;
    }
    
    return true;
}

bool Read_TLong(ifstream& fin, TLong& num)
{
    string str;

    fin >> str;
    cout << str << endl;

    unsigned short strLength = str.length();

    if (str[0] == '-') {
        num.sign = true;
        str = str.substr(1);
    }

    int posDot = str.find('.');
    strLength = str.length();
    if (posDot < 0)
        posDot = strLength;

    num.dataFloat[0] = (strLength - posDot + 2) / 3;

    num.dataInt[0] = (posDot + 2) / 3;

    unsigned char j = 0;
    unsigned short cur = 0;
    unsigned char curCell = 1;

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

    for (unsigned char i = num.dataInt[0]; i >= 1; i--) {
        if (num.dataInt[i] == 0)
            num.dataInt[0]--;
        else
            break;
    }

    for (unsigned char i = num.dataFloat[0]; i >= 1; i--) {
        if (num.dataFloat[i] == 0)
            num.dataFloat[0]--;
        else
            break;
    }

    return false;
}

void Write_TLong(ofstream& fout, TLong& num)
{
    if (num.sign)
        fout << "-";
    for (char i = num.dataInt[0]; i >= 1; i--) {
        if (i > 1 && num.dataInt[i] == 0)
            fout << "000";
        else if (i > 1 && num.dataInt[i] < 10)
            fout << num.dataInt[i] * 100;
        else if (i > 1 && num.dataInt[i] < 100)
            fout << num.dataInt[i] * 10;
        else
            fout << num.dataInt[i];
    }

    if (num.dataFloat[0] != 0) {
        fout << '.';
        for (char i = 1; i <= num.dataFloat[0]; i++) {
            if (num.dataFloat[i] == 0)
                fout << "000";
            else if (num.dataFloat[i] < 10)
                fout << "00" << num.dataFloat[i];
            else if (num.dataFloat[i] < 100)
                fout << '0' << num.dataFloat[i];
            else
                fout << num.dataFloat[i];
        }
    }

}

TLong Sum_TLong(TLong& a, TLong& b)
{
    //прописать присвоение переменной С знака числа А, тк знаки у а и b одинаковые
    TLong c;
    c.sign = a.sign;



    return c;
}

TLong Sub_TLong(TLong a, TLong b)
{
    
    
    return a;

}

TLong Sum_or_Sub(TLong& a, TLong& b, char oper) 
{
    if (oper == '+') {
        if (a.sign == false && b.sign == false)
            return Sum_TLong(a, b);

        if (a.sign == false && b.sign)
            return Sub_TLong(a, b);

        if (a.sign && b.sign == false)
            return Sub_TLong(b, a);

        if (a.sign && b.sign)
            return Sum_TLong(a, b);
    }

    if (oper == '-') {
        if (a.sign == false && b.sign == false)
            return Sub_TLong(a, b);

        if (a.sign == false && b.sign)
            return Sum_TLong(a, b);

        if (a.sign && b.sign == false)
            return Sum_TLong(a, b);

        if (a.sign && b.sign)
            return Sub_TLong(b, a);
    }
    
    return a;
}

int main()
{

    ifstream fin;
    ofstream fout;
    fin.open("./files/input.txt", ios_base::in);
    fout.open("./files/output.txt", ios_base::out);

    TLong num;
    string str;
     
    Read_TLong(fin, num);
    Write_TLong(fout, num);

    fin.close();
    fout.close();

    return 0;
}

