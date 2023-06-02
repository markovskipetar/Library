#include "Periodical.h"

Periodical::Periodical(const MyString& title, const MyString& description, const int publishingYear,
	const Periodicity& periodicity, const int editionsCount) :
	Publication(title, description, publishingYear)
{
	try
	{
		setPeriodicity(periodicity);
		setEditions(editionsCount);
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

void Periodical::setPeriodicity(const Periodicity& periodicity)
{
	this->periodicity = periodicity;
}

void Periodical::setEditions(const int editionsCount)
{
	Validator::validateNumber(editionsCount);

	this->editions = editionsCount;
}

const Periodicity& Periodical::getPeriodicity() const
{
	return periodicity;
}

const unsigned Periodical::getEditons() const
{
	return editions;
}

const MyString Periodical::getType() const
{
	return MyString("Periodical");
}

Publication* Periodical::clone() const
{
	return new Periodical(*this);
}


