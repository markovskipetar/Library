#pragma once
#include "MyStringSso.h"
#include "Date.h"
#include <cmath>

class Validator
{
public:
	static void validateName(const MyString& name);
	static void validateLength(const MyString& text);
	static void validateYear(const int year);
	static void validateNumber(const int number);
	static unsigned dateDifference(const Date& firstDate, const Date& secondDate);
};

