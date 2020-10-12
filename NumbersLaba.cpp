#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const int NumberOfDigits = 34;

struct TLong
{
    unsigned short dataInt[NumberOfDigits] = {};
    unsigned short dataFloat[NumberOfDigits] = {};
    bool sign = false;
};

bool Read_TLong(ifstream& fin, TLong& num)
{
    string str;

    /*for (unsigned char i = 0; i <= NumberOfDigits; i++) {

    }*/


    fin >> str;
    cout << str << endl;

    unsigned short strLength = str.length();

    if (str[0] == '-') {
        num.sign = true;
        str = str.substr(1);
    }

    int posDot = str.find(".");
    strLength = str.length();

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
            /*if (num.dataFloat[curCell] % 100 == 0)
                num.dataFloat[curCell] /= 100;
            else if (num.dataFloat[curCell] % 10 == 0)
                num.dataFloat[curCell] /= 10;*/
            num.dataFloat[curCell] = cur;
            curCell++;
            cur = 0;
        }
        else
            j--;
    }

    curCell--;
    if (num.dataFloat[curCell] % 100 == 0)
        num.dataFloat[curCell] /= 100;
    else if (num.dataFloat[curCell] % 10 == 0)
        num.dataFloat[curCell] /= 10;
    
    return false;
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

    fin.close();
    fout.close();

    return 0;
}

