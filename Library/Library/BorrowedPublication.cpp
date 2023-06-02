#include "BorrowedPublication.h"

const MyString& BorrowedPublication::getUsername() const
{
	return username;
}
const Date& BorrowedPublication::getDate() const
{
	return date;
}
const unsigned BorrowedPublication::getLibraryNumber() const
{
	return libraryNumber;
}