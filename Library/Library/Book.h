#pragma once
#include "Publication.h"
#include "Genre.h"

class Book : virtual public Publication
{
private:
	MyString author;
	MyString publisher;
	unsigned short genre;

	void setAuthor(const MyString& author);
	void setPublisher(const MyString& publisher);
	void setGenre(const Characteristic& charachetisitc, const Type& type, const Auditory& auditory);

	unsigned getOnesCount(short genre) const;

public:
	Book(const MyString& title, const MyString& description, const int publishingYear,
		const MyString& author, const MyString& publisher, const Characteristic& charachetisitc, const Type& type, const Auditory& auditory);

	const MyString& getAuthor() const;
	const MyString& getPublisher() const;
	const unsigned short getGenre() const;
	const MyString getType() const override;

	Publication* clone() const override;
};

