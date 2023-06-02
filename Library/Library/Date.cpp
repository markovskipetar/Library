#include "Date.h"

Date::Date(unsigned day, unsigned month, unsigned year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

void Date::setYear(unsigned year)
{
	if (year == this->year)
	{
		return;
	}

	this->year = year;

	
}
void Date::setDay(unsigned day)
{
	if (day == this->day)
	{
		return;
	}

	if (day == 0 || day > 31)
	{
		throw std::invalid_argument("Invalid day!");
	}

	this->day = day;
}
void Date::setMonth(unsigned month)
{
	if (month == this->month)
	{
		return;
	}

	if (month == 0 || month > 12)
	{
		throw std::invalid_argument("Invalid month!");
	}

	this->month = month;
}

unsigned Date::getDay() const
{
	return day;
}
unsigned Date::getMonth() const
{
	return month;
}
unsigned Date::getYear() const
{
	return year;
}