#pragma once
#include "Book.h"
#include "Periodical.h"

class Comics : public Book, public Periodical
{
public:
	Comics(const MyString& title, const MyString& description, const int publishingYear,
		const MyString& author, const MyString& publisher, const Characteristic& charachetisitc, const Type& type, const Auditory& auditory,
		const Periodicity& periodicity, const int editionsCount);

	Publication* clone() const override;

	const MyString getType() const override;
};

