#include "Library.h"

Library::Library()
{
	publications = new Publication * [INITIAL_CAPACITY] {nullptr};
	publicationsCopies = new unsigned[INITIAL_CAPACITY] {0};
	availablePublications = new unsigned[INITIAL_CAPACITY] {0};
	borrowedPublications = new BorrowedPublication * [INITIAL_CAPACITY] {nullptr};
	users = new User * [INITIAL_CAPACITY] {nullptr};

	publicationsCapacity = usersCapacity = borrowedPublicationsCapacity = INITIAL_CAPACITY;
	publicationsCount = usersCount = borrowedPublicationsCount = INITIAL_COUNT;
}

void Library::addUser(const User& user)
{
	if (usersCount >= usersCapacity)
	{
		resizeUsers(usersCapacity * 1.5);
	}

	users[usersCount++] = new User(user);
}

void Library::removeUser(const MyString& username)
{
	try
	{
		unsigned userIndex = getUserIndex(username);

		const unsigned* userPublications = users[userIndex]->getBorrowed();
		unsigned count = users[userIndex]->getCount();

		const MyString& username = users[userIndex]->getUsername();

		for (size_t i = 0; i < count; i++)
		{
			int index = userPublications[i];

			giveBack(username, index);
		}

		delete users[userIndex];

		users[userIndex] = users[--usersCount];
		users[usersCount] = nullptr;
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

unsigned Library::getUserIndex(const MyString& username) const
{
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i]->getUsername() == username)
		{
			return i;
		}
	}

	throw std::invalid_argument("User does not exist!");
}

void Library::addPublication(const Publication* publication, const unsigned count)
{
	unsigned index;

	if (publicationsCount >= publicationsCapacity)
	{
		resizePublications(publicationsCapacity * 1.5);
		index = publicationsCount;
	}
	else
	{
		index = getFirstInsertionIndex();
	}

	publications[index] = publication->clone();

	publicationsCopies[index] = count;
	availablePublications[index] = count;

	publicationsCount++;
}

void Library::printPublicationsData() const
{
	for (size_t i = 0; i < publicationsCount; i++)
	{
		if (publications[i] != nullptr)
		{
			std::cout << publications[i]->getTitle() << " -> " << "Copies: " << publicationsCopies[i] << " Availability: " << availablePublications[i] << std::endl;
		}
	}
}

void Library::resizePublications(unsigned newCapacity)
{
	publicationsCapacity = newCapacity;

	Publication** resizedPublications = new Publication * [publicationsCapacity];
	unsigned* resizedPublicationsCopies = new unsigned[publicationsCapacity];
	unsigned* resizedAvailablePublications = new unsigned[publicationsCapacity];

	for (size_t i = 0; i < publicationsCount; i++)
	{
		resizedPublications[i] = publications[i];
		publications[i] = nullptr;

		resizedPublicationsCopies[i] = publicationsCopies[i];
		resizedAvailablePublications[i] = availablePublications[i];
	}

	delete[] publications;
	delete[] publicationsCopies;
	delete[] availablePublications;

	publications = resizedPublications;
	publicationsCopies = resizedPublicationsCopies;
	availablePublications = resizedAvailablePublications;
}

void Library::resizeUsers(unsigned newCapacity)
{
	usersCapacity = newCapacity;

	User** resizedUsers = new User * [usersCapacity];

	for (size_t i = 0; i < usersCount; i++)
	{
		resizedUsers[i] = users[i];
		users[i] = nullptr;
	}

	delete[] users;
	users = resizedUsers;
}

void Library::printUsers()const
{
	for (size_t i = 0; i < usersCount - 1; i++)
	{
		for (size_t j = 0; j < usersCount - 1; j++)
		{
			if (users[j]->compareTo(*(users[j + 1])) == 1)
			{
				std::swap(users[j], users[j + 1]);
			}
		}
	}

	for (size_t i = 0; i < usersCount; i++)
	{
		std::cout << users[i]->getUsername() << "(read: " << users[i]->getReadPublicationsCount() << "):" << std::endl;

		const unsigned* borrowed = users[i]->getBorrowed();
		unsigned count = users[i]->getCount();

		for (size_t i = 0; i < count; i++)
		{
			unsigned index = borrowed[i];

			std::cout << " -- " << publications[index]->getTitle() << std::endl;
		}

		std::cout << "Read: ";

		const unsigned* read = users[i]->getRead();
		unsigned readCount = users[i]->getReadPublicationsCount();

		for (size_t i = 0; i < readCount; i++)
		{
			std::cout << read[i] << ", ";
		}
		std::cout << std::endl;
	}
}

unsigned Library::getFirstInsertionIndex() const
{
	for (size_t i = 0; i < publicationsCount; i++)
	{
		if (!publicationsCopies[i])
		{
			return i;
		}
	}
}

unsigned Library::getPublicationIndex(unsigned libraryNumber) const
{
	for (size_t i = 0; i < publicationsCount; i++)
	{
		if ((publicationsCopies[i] != 0) && (publications[i]->getLibraryNumber() == libraryNumber))
		{
			return i;
		}
	}

	throw std::invalid_argument("Publication does not exist!");
}

void Library::removePublication(unsigned libraryNumber)
{
	try
	{
		unsigned removeIndex = getPublicationIndex(libraryNumber);

		if (publicationsCopies[removeIndex] != availablePublications[removeIndex])
		{
			throw std::invalid_argument("Not all publication copies are returned to the library!");
		}

		delete publications[removeIndex];
		publications[removeIndex] = nullptr;

		publicationsCopies[removeIndex] = 0;
		availablePublications[removeIndex] = 0;

		publicationsCount--;
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
		return;
	}
}

void Library::borrow(const MyString& username, const unsigned libraryNumber, unsigned day, unsigned month, unsigned year)
{
	try
	{
		unsigned userIndex = getUserIndex(username);
		unsigned publicationIndex = getPublicationIndex(libraryNumber);

		if (availablePublications[publicationIndex] == 0)
		{
			throw std::invalid_argument("No copies available!");
		}

		*(users[userIndex]) += libraryNumber;

		addBorrowedPublication(username, libraryNumber, day, month, year);

		availablePublications[publicationIndex]--;
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

void Library::addBorrowedPublication(const MyString& username, unsigned libraryNumber, unsigned day, unsigned month, unsigned year)
{
	if (borrowedPublicationsCount >= borrowedPublicationsCapacity)
	{
		resizeBorrowed(borrowedPublicationsCapacity * 1.5);
	}

	try
	{
		borrowedPublications[borrowedPublicationsCount++] = new BorrowedPublication(username, libraryNumber, day, month, year);
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

void Library::removeBorrowedPublication(unsigned libraryNumber)
{
	for (size_t i = 0; i < borrowedPublicationsCount; i++)
	{
		if (borrowedPublications[i]->getLibraryNumber() == libraryNumber)
		{
			std::swap(borrowedPublications[i], borrowedPublications[--borrowedPublicationsCount]);
			return;
		}
	}
}

void Library::giveBack(const MyString& username, const unsigned libraryNumber) // petar (0,1,2) 7
{
	try
	{
		unsigned userIndex = getUserIndex(username);
		unsigned publicationIndex = getPublicationIndex(libraryNumber);

		*(users[userIndex]) -= publicationIndex;

		users[userIndex]->addReadPublication(publications[publicationIndex]->getLibraryNumber());

		removeBorrowedPublication(libraryNumber);

		availablePublications[publicationIndex]++;
	}
	catch (const std::invalid_argument& exception)
	{
		std::cout << exception.what();
	}
}

void Library::printUsersWithOverduedPublication(unsigned libraryNumber, unsigned day, unsigned month, unsigned year) const
{
	Date currentCheckDate(day, month, year);

	std::cout << "Users with overdued publication:" << std::endl;

	for (size_t i = 0; i < borrowedPublicationsCount; i++)
	{
		if (Validator::dateDifference(currentCheckDate, borrowedPublications[i]->getDate()) > 31)
		{
			std::cout << borrowedPublications[i]->getUsername() << std::endl;
		}
	}
}

unsigned Library::getLibraryNumberFromIndex(unsigned inedx) const
{
	return publications[inedx]->getLibraryNumber();
}

void Library::copyFrom(const Library& other)
{
	publicationsCount = other.publicationsCount;
	publicationsCapacity = other.publicationsCapacity;

	publications = new Publication * [publicationsCount];
	unsigned* publicationsCopies = new unsigned[publicationsCapacity];
	unsigned* availablePublications = new unsigned[publicationsCapacity];

	for (size_t i = 0; i < publicationsCount; i++)
	{
		publications[i] = other.publications[i]->clone();
		publicationsCopies[i] = other.publicationsCopies[i];
		availablePublications[i] = other.availablePublications[i];
	}

	unsigned usersCount = other.usersCount;
	unsigned usersCapacity = other.usersCapacity;

	users = new User * [usersCapacity];

	for (size_t i = 0; i < usersCount; i++)
	{
		users[i] = new User(*(other.users[i]));
	}
}

void Library::free()
{
	for (size_t i = 0; i < publicationsCount; i++)
	{
		delete publications[i];
		publications[i] = nullptr;
	}

	delete[] publications;
	delete[] publicationsCopies;
	delete[] availablePublications;

	for (size_t i = 0; i < usersCount; i++)
	{
		delete users[i];
		users[i] = nullptr;
	}

	delete[] users;

	for (size_t i = 0; i < borrowedPublicationsCount; i++)
	{
		delete borrowedPublications[i];
	}

	delete[] borrowedPublications;
}

Library::Library(const Library& other)
{
	copyFrom(other);
}

Library& Library::operator= (const Library& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Library::~Library()
{
	free();
}

void Library::resizeBorrowed(unsigned newCapacity)
{
	borrowedPublicationsCapacity = newCapacity;

	BorrowedPublication** resizedBorrowed = new BorrowedPublication * [borrowedPublicationsCapacity];

	for (size_t i = 0; i < borrowedPublicationsCount; i++)
	{
		resizedBorrowed[i] = borrowedPublications[i];

		borrowedPublications[i] = nullptr;
	}

	delete[] borrowedPublications;

	borrowedPublications = resizedBorrowed;
}

void Library::printOverduedPublications(unsigned day, unsigned month, unsigned year) const
{
	Date currentCheckDate(day, month, year);

	std::cout << "Overdued publications:" << std::endl;

	for (size_t i = 0; i < borrowedPublicationsCount; i++)
	{
		if (Validator::dateDifference(currentCheckDate, borrowedPublications[i]->getDate()) > 30)
		{
			unsigned libraryNumber = borrowedPublications[i]->getLibraryNumber();
			std::cout << getTitleByLibraryNumber(libraryNumber) << std::endl;
		}
	}
}

const MyString& Library::getTitleByLibraryNumber(unsigned libraryNumber) const
{
	for (size_t i = 0; i < publicationsCount; i++)
	{
		if (publications[i]->getLibraryNumber() == libraryNumber)
		{
			return  publications[i]->getTitle();
		}
	}
}

void Library::printLibrary()
{
	sortPublications();

	for (size_t i = 0; i < publicationsCount; i++)
	{
		std::cout << publications[i]->getTitle() << std::endl;
		std::cout << publications[i]->getType() << std::endl;
		std::cout << publications[i]->getDescription() << std::endl;
		std::cout << publications[i]->getLibraryNumber() << std::endl;

		std::cout << std::endl;
	}
}

void Library::sortPublications()
{
	for (size_t i = 0; i < publicationsCount - 1; i++)
	{
		for (size_t j = 0; j < publicationsCount - 1; j++)
		{
			if (publications[j]->compareTo(publications[j + 1]) == 1)
			{
				std::swap(publications[j], publications[j + 1]);
			}
		}
	}
}

void Library::exit() const
{
	std::ofstream fileWriter("users.txt");

	try
	{
		if (!fileWriter.is_open())
		{
			throw std::invalid_argument("file not opened!");
		}

		for (size_t i = 0; i < usersCount; i++)
		{
			users[i]->writeToFile(fileWriter);
		}
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what();
	}

	fileWriter.flush();

	writePublicationsToFile();

	fileWriter.flush();
	fileWriter.close();
}

void Library::writePublicationsToFile() const
{
	std::ofstream fileWriter("publications.txt");

	try
	{
		if (!fileWriter.is_open())
		{
			throw std::invalid_argument("file not opened!");
		}

		fileWriter << publicationsCount << " " << publicationsCapacity << std::endl;

		for (size_t i = 0; i < publicationsCount; i++)
		{
			fileWriter << publications[i]->getTitle() << ", ";
		}

		fileWriter << std::endl;

		fileWriter << usersCount << " " << usersCapacity << std::endl;

		for (size_t i = 0; i < usersCount; i++)
		{
			std::cout << users[i]->getUsername() << " ";
		}

		fileWriter << std::endl;

		fileWriter << borrowedPublicationsCount << " " << borrowedPublicationsCapacity << std::endl;

		for (size_t i = 0; i < borrowedPublicationsCount; i++)
		{
			fileWriter << borrowedPublications[i]->getLibraryNumber() << " ";
		}

		fileWriter << std::endl;
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what();
	}

	fileWriter.flush();
	fileWriter.close();
}