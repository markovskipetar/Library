#include "Comics.h"

Comics::Comics(const MyString& title, const MyString& description, const int publishingYear,
	const MyString& author, const MyString& publisher, const Characteristic& characteristics, const Type& type, const Auditory& auditory,
	const Periodicity& periodicity, const int editionsCount) :

	Publication(title, description, publishingYear),
	Book(title, description, publishingYear, author, publisher, characteristics, type, auditory),
	Periodical(title, description, publishingYear, periodicity, editionsCount)
{

}

Publication* Comics::clone() const
{
	Publication* copy = new Comics(*this);

	return copy;
}

const MyString Comics::getType() const
{
	return MyString("Comics");
}

