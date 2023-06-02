#pragma once
#include <iostream>

class Date
{
private:
	unsigned day;
	unsigned month;
	unsigned year;

	void setDay(unsigned day);
	void setMonth(unsigned month);
	void setYear(unsigned year);

public:
	Date(unsigned day, unsigned month, unsigned year);

	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;
};

