#include "Validator.h"

void Validator::validateName(const MyString& name)
{
	validateLength(name);

	const char* textCStr = name.c_str();

	while (true)
	{
		char symbol = (*textCStr);

		if (symbol == '\0')
		{
			break;
		}

		bool isLowercase = ('a' <= symbol && symbol <= 'z');
		bool isUppercase = ('A' <= symbol && symbol <= 'Z');
		bool isDigit = ('0' <= symbol && symbol <= '9');
		bool isWhitespace = (symbol == ' ');

		if (!isLowercase && !isUppercase && !isDigit && !isWhitespace)
		{
			throw std::invalid_argument("Invalid characters!");
		}

		textCStr++;
	}
}

void Validator::validateLength(const MyString& text)
{
	if (text.length() < 3)
	{
		throw std::invalid_argument("Length must be more than 3 characters!");
	}
}

void Validator::validateYear(const int year)
{
	if (year <= 0)
	{
		throw std::invalid_argument("Invalid year!");
	}
}

void Validator::validateNumber(const int number)
{
	if (number <= 0)
	{
		throw std::invalid_argument("Invalid value!");
	}
}

unsigned Validator::dateDifference(const Date& firstDate, const Date& secondDate)
{
	int firstDateToDays = firstDate.getDay() + (firstDate.getMonth() * 30) + (firstDate.getYear() * 365);
	int secondDateToDays = secondDate.getDay() + (secondDate.getMonth() * 30) + (secondDate.getYear() * 365);
	unsigned result = abs(firstDateToDays - secondDateToDays);

	return result;
}

