#pragma once
#include "Publication.h"
#include "Periodicity.h"

class Periodical :virtual public Publication
{
private:
	Periodicity periodicity;
	unsigned editions;

	void setPeriodicity(const Periodicity& periodicity);
	void setEditions(const int editionsCount);

public:
	Periodical(const MyString& title, const MyString& description, const int publishingYear,
		const Periodicity& periodicity, const int editionsCount);

	const Periodicity& getPeriodicity() const;
	const unsigned getEditons() const;

	Publication* clone() const override;
	const MyString getType() const override;

};