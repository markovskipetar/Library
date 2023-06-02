#pragma once
#include <iostream>
#include "User.h"
#include "Publication.h"
#include "BorrowedPublication.h"

// TO DO IMPORTANT   !!!!!!!!!!
// ADD GETTERS !!!!!!!!!!!!

class Library
{
public:
	//private:
	Publication** publications;
	unsigned* publicationsCopies;
	unsigned* availablePublications;

	unsigned publicationsCount;
	unsigned publicationsCapacity;

	User** users;
	unsigned usersCount;
	unsigned usersCapacity;

	BorrowedPublication** borrowedPublications;
	unsigned borrowedPublicationsCount;
	unsigned borrowedPublicationsCapacity;

	void resizePublications(unsigned newCapacity);
	void resizeUsers(unsigned newCapacity);
	void resizeBorrowed(unsigned newCapacity);

	unsigned getUserIndex(const MyString& username) const;
	unsigned getFirstInsertionIndex() const;

	unsigned getPublicationIndex(unsigned libraryNumber) const;
	unsigned getLibraryNumberFromIndex(unsigned inedx) const;

	void copyFrom(const Library& other);
	void free();

	void addBorrowedPublication(const MyString& username, unsigned libraryNumber, unsigned day, unsigned month, unsigned year);
	void removeBorrowedPublication(unsigned libraryNumber);
	const MyString& getTitleByLibraryNumber(unsigned libraryNumber) const;
	void sortPublications();

	void writePublicationsToFile() const;
public:
	Library();
	Library(const Library& other);
	Library& operator= (const Library& other);
	~Library();

	void addUser(const User& user);
	void removeUser(const MyString& username);

	void addPublication(const Publication* publication, const unsigned count);
	void removePublication(unsigned libraryNumber);

	void borrow(const MyString& username, const unsigned libraryNumber, unsigned day, unsigned month, unsigned year);
	void giveBack(const MyString& username, const unsigned libraryNumber);

	void printPublicationsData() const;
	void printOverduedPublications(unsigned day, unsigned month, unsigned year) const;
	void printUsersWithOverduedPublication(unsigned libraryNumber, unsigned day, unsigned month, unsigned year) const;
	void printUsers() const;
	void printLibrary();

	void exit() const;
};