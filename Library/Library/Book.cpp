#include "Book.h"

Book::Book(const MyString& title, const MyString& description, const int publishingYear,
	const MyString& author, const MyString& publisher, const Characteristic& charachetisitc, const Type& type, const Auditory& auditory) :
	Publication(title, description, publishingYear)
{
	try
	{
		setAuthor(author);
		setPublisher(publisher);
		setGenre(charachetisitc, type, auditory);
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

void Book::setAuthor(const MyString& author)
{
	Validator::validateName(author);

	this->author = author;
}

void Book::setPublisher(const MyString& publisher)
{
	Validator::validateName(publisher);

	this->publisher = publisher;
}
void Book::setGenre(const Characteristic& charachetisitc, const Type& type, const Auditory& auditory)
{
	unsigned short genre = 0;

	short auditoryMask = ((unsigned)auditory) << 11;
	short typeMask = ((unsigned)type) << 7;
	unsigned characteristicMask = (unsigned)charachetisitc;

	genre |= auditoryMask;
	genre |= typeMask;
	genre |= characteristicMask;

	unsigned ones = getOnesCount(genre);

	if (ones % 2 == 1)
	{
		unsigned short seniorBitMask = 1 << 15;
		genre |= seniorBitMask;
	}

	this->genre = genre;
}

unsigned Book::getOnesCount(short genre) const
{
	unsigned ones = 0;

	short shortBitsCount = sizeof(short) * 8;

	short mask = 1;

	for (size_t i = 0; i < shortBitsCount; i++)
	{
		if ((genre & mask) != 0)
		{
			ones++;
		}

		mask <<= 1;
	}

	return ones;
}

const MyString Book::getType() const
{
	return MyString("Book");
}

Publication* Book::clone() const
{
	Publication* copy = new Book(*this);

	return copy;
}

const MyString& Book::getAuthor() const
{
	return author;
}

const MyString& Book::getPublisher() const
{
	return publisher;
}

const unsigned short Book::getGenre() const
{
	return genre;
}