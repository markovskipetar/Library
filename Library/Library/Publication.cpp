#include "Publication.h"

unsigned Publication::globalLibraryNumber = 0;

Publication::Publication(const MyString& title, const MyString& description, const int publishingYear)
{
	try
	{
		setTitle(title);
		setDescription(description);
		setLibraryNumber();
		setPublishingYear(publishingYear);
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

void Publication::setTitle(const MyString& title)
{
	Validator::validateName(title);

	this->title = title;
}

void Publication::setDescription(const MyString& description)
{
	Validator::validateLength(description);

	this->description = description;
}

void Publication::setLibraryNumber()
{
	this->libraryNumber = globalLibraryNumber++;
}

void Publication::setPublishingYear(const int publishingYear)
{
	Validator::validateYear(publishingYear);

	this->publishingYear = publishingYear;
}

unsigned Publication::getLibraryNumber() const
{
	return libraryNumber;
}

const MyString& Publication::getTitle() const
{
	return title;
}

const MyString& Publication::getDescription() const
{
	return description;
}

int Publication::getPublishingYear() const
{
	return publishingYear;
}

short Publication::compareTo(const Publication* other) const
{
	if (publishingYear < other->publishingYear)
	{
		return -1;
	}

	if (publishingYear > other->publishingYear)
	{
		return 1;
	}

	return strcmp(this->getTitle().c_str(), other->getTitle().c_str());
}