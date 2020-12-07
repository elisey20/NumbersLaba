#pragma once

const int NumberOfDigits = 11;

struct TLong
{
    unsigned short dataInt[NumberOfDigits] = { 0 };
    unsigned short dataFloat[NumberOfDigits] = { 0 };
    bool sign = false;
};

enum class ETAR
{
    NUMBER,
    OPERATOR,
    ERROR,
    FIRST,
};