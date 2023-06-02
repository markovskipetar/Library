#pragma once
#include "MyStringSso.h"
#include "Validator.h"
#include <fstream>

class Publication
{
private:
	static unsigned globalLibraryNumber;

	MyString title;
	MyString description;
	unsigned libraryNumber;
	int publishingYear;

	void setTitle(const MyString& title);
	void setDescription(const MyString& description);
	void setLibraryNumber();
	void setPublishingYear(const int publishingYear);

public:
	Publication(const MyString& title, const MyString& description, const int publishingYear);

	virtual Publication* clone() const = 0;

	const MyString& getTitle() const;
	const MyString& getDescription() const;
	unsigned getLibraryNumber() const;
	int getPublishingYear() const;
	virtual const MyString getType() const = 0;

	short compareTo(const Publication* other) const;

	virtual ~Publication() = default;
};
