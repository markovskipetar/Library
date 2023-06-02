#pragma once
#include "MyStringSso.h"
#include "Validator.h"
#include "GlobalConstants.h"
#include "Publication.h"

class User
{
private:
	MyString username;

	unsigned* borrowed;
	unsigned borrowedCount;
	unsigned borrowedCapacity;

	unsigned* read;
	unsigned readCount;
	unsigned readCapacity;

	void setUsername(const MyString& username);

	void addBorrowedPublication(const unsigned libraryNumber);
	void giveBackPublication(const unsigned publicationIndex);

	void resize(const unsigned newCapacity);
	void resizeRead(const unsigned newCapacity);
	void copyFrom(const User& other);
	void free();
public:
	User(const MyString& username);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	const MyString& getUsername() const;
	const unsigned* getBorrowed() const;
	const unsigned* getRead() const;
	const unsigned getCount() const;
	const unsigned getReadPublicationsCount() const;

	void addReadPublication(unsigned libraryNumber);

	User& operator+= (const unsigned libraryNumber);
	User& operator-= (const unsigned libraryNumber);

	MyString operator[](const unsigned publicationIndex) const;

	short compareTo(const User& other) const;

	void writeToFile(std::ofstream& writer) const;
};

User operator+ (const User& user, const unsigned publicationIndex);
User operator- (const User& user, const unsigned publicationIndex);

bool operator== (const User& firstUser, const User& secondUser);
bool operator!= (const User& firstUser, const User& secondUser);

bool operator> (const User& firstUser, const User& secondUser);
bool operator>= (const User& firstUser, const User& secondUser);
bool operator<  (const User& firstUser, const User& secondUser);
bool operator<= (const User& firstUser, const User& secondUser);

