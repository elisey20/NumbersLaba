#pragma once

#include "structs.h"

extern bool isTrue;

bool Eq(TLong& a, TLong& b);

bool Less(TLong& a, TLong& b);

bool Read_TLong(std::string& str, TLong& num);

void Write_TLong(std::ofstream& fout, TLong num);

TLong Sum_TLong(TLong& a, TLong& b);

TLong Sub_TLong(TLong a, TLong b);

TLong Sum_or_Sub(TLong a, char oper, TLong& b);

ETAR Try_Read_String(std::string& str);

