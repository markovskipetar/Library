#include "User.h"

User::User(const MyString& username)
{
	try
	{
		setUsername(username);

		borrowed = new unsigned[INITIAL_CAPACITY] {0};
		read = new unsigned[INITIAL_CAPACITY] {0};

		borrowedCapacity = INITIAL_CAPACITY;
		borrowedCount = INITIAL_COUNT;

		readCapacity = INITIAL_CAPACITY;
		readCount = INITIAL_COUNT;
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

User::User(const User& other) : username(other.username), readCount(other.readCount)
{
	copyFrom(other);
}

void User::copyFrom(const User& other)
{
	borrowedCapacity = other.borrowedCapacity;
	borrowedCount = other.borrowedCount;
	borrowed = new unsigned[borrowedCapacity];

	for (size_t i = 0; i < borrowedCount; i++)
	{
		borrowed[i] = other.borrowed[i];
	}

	readCapacity = other.readCapacity;
	readCount = other.readCount;
	read = new unsigned[readCapacity];

	for (size_t i = 0; i < readCount; i++)
	{
		read[i] = other.read[i];
	}
}

void User::setUsername(const MyString& username)
{
	Validator::validateName(username);

	this->username = username;
}

const MyString& User::getUsername() const
{
	return username;
}

void User::resize(const unsigned newCapacity)
{
	borrowedCapacity = newCapacity;

	unsigned* resizedBorrowed = new unsigned[borrowedCapacity];

	for (size_t i = 0; i < borrowedCount; i++)
	{
		resizedBorrowed[i] = borrowed[i];
	}

	delete borrowed;
	borrowed = resizedBorrowed;
}

void User::addBorrowedPublication(const unsigned publicationIndex)
{
	if (borrowedCount >= borrowedCapacity)
	{
		resize(borrowedCapacity * 1.5);
	}

	borrowed[borrowedCount++] = publicationIndex;
}

void User::giveBackPublication(const unsigned publicationIndex)
{
	for (size_t i = 0; i < borrowedCount; i++)
	{
		if (borrowed[i] == publicationIndex)
		{
			std::swap(borrowed[i], borrowed[--borrowedCount]);

			return;
		}
	}
}

const unsigned User::getReadPublicationsCount() const
{
	return readCount;
}

const unsigned* User::getRead() const
{
	return read;
}

User& User::operator+= (const unsigned libraryNumber)
{
	if (borrowedCount == BORROW_MAX_COUNT)
	{
		throw std::invalid_argument("Not allowd to borrow more books!");
	}


	addBorrowedPublication(libraryNumber);

	return *this;
}

User& User::operator-= (const unsigned libraryNumber)
{
	giveBackPublication(libraryNumber);

	return *this;
}

const unsigned* User::getBorrowed() const
{
	return borrowed;
}

const unsigned User::getCount() const
{
	return borrowedCount;
}

User operator+ (const User& user, const unsigned libraryNumber)
{
	User userCopy(user);

	userCopy += libraryNumber;

	return userCopy;
}

User operator- (const User& user, const unsigned libraryNumber)
{
	User userCopy(user);

	userCopy -= libraryNumber;

	return userCopy;
}

bool operator== (const User& firstUser, const User& secondUser)
{
	return firstUser.getUsername() == secondUser.getUsername();
}

bool operator!= (const User& firstUser, const User& secondUser)
{
	return !(firstUser == secondUser);
}

void User::addReadPublication(unsigned libraryNumber)
{
	if (readCount >= readCapacity)
	{
		resizeRead(readCapacity * 1.5);
	}

	read[readCount++] = libraryNumber;
}

void User::resizeRead(const unsigned newCapacity)
{
	readCapacity = newCapacity;

	unsigned* resizedRead = new unsigned[readCapacity];

	for (size_t i = 0; i < readCount; i++)
	{
		resizedRead[i] = read[i];
	}

	delete[] read;

	read = resizedRead;
}

MyString User::operator[](const unsigned libraryNumber) const
{
	for (size_t i = 0; i < readCount; i++)
	{
		if (read[i] == libraryNumber)
		{
			return MyString("Read!");
		}
	}

	for (size_t i = 0; i < borrowedCount; i++)
	{
		if (borrowed[i] == libraryNumber)
		{
			return MyString("Borrowed!");
		}
	}

	return MyString("Never borrowed!");
}

bool operator> (const User& firstUser, const User& secondUser)
{
	return firstUser.getReadPublicationsCount() > secondUser.getReadPublicationsCount();
}

bool operator>= (const User& firstUser, const User& secondUser)
{
	return firstUser.getReadPublicationsCount() >= secondUser.getReadPublicationsCount();
}

bool operator<  (const User& firstUser, const User& secondUser)
{
	return firstUser.getReadPublicationsCount() < secondUser.getReadPublicationsCount();
}

bool operator<= (const User& firstUser, const User& secondUser)
{
	return firstUser.getReadPublicationsCount() <= secondUser.getReadPublicationsCount();
}

short User::compareTo(const User& other) const
{
	if (readCount == other.readCount)
	{
		return 0;
	}

	if (readCount < other.readCount)
	{
		return -1;
	}

	return 1;
}

void User::free()
{
	delete[] read;
	read = nullptr;

	delete[] borrowed;
	borrowed = nullptr;
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

User::~User()
{
	free();
}

void User::writeToFile(std::ofstream& writer) const
{
	writer << username.c_str() << std::endl;

	writer << borrowedCount << " " << borrowedCapacity << std::endl;

	for (size_t i = 0; i < borrowedCount; i++)
	{
		writer << borrowed[i] << " ";
	}

	writer << std::endl;

	writer << readCount << " " << readCapacity << std::endl;

	for (size_t i = 0; i < readCount; i++)
	{
		writer << read[i] << " ";
	}

	writer << std::endl;
}

//MyString username;
//
//unsigned* borrowed;
//unsigned borrowedCount;
//unsigned borrowedCapacity;
//
//unsigned* read;
//unsigned readCount;
//unsigned readCapacity;