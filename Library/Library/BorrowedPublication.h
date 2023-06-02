#pragma once
#include "MyStringSso.h"
#include "Date.h"

class BorrowedPublication
{
private:
	MyString username;
	Date date;
	unsigned libraryNumber;

public:
	BorrowedPublication(const MyString& username, const unsigned libraryNumber, unsigned day, unsigned month, unsigned year)
		: username(username), date(day, month, year), libraryNumber(libraryNumber) {}

	const MyString& getUsername() const;
	const Date& getDate() const;
	const unsigned getLibraryNumber() const;
};

