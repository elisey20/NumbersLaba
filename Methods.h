#include "Structs.h"

bool Eq(TLong& a, TLong& b);

bool Less(TLong& a, TLong& b);

bool Read_TLong(string& str, TLong& num);

void Write_TLong(ofstream& fout, TLong num);

TLong Sum_TLong(TLong& a, TLong& b);

TLong Sub_TLong(TLong a, TLong b);

TLong Sum_or_Sub(TLong a, char oper, TLong& b);

ETAR Try_Read_String(string& str);

