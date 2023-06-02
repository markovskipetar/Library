#include <iostream>
#include "Library.h"
#include "Comics.h"

int main()
{
	Book book("Pod igoto", "Novel by Ivan Vazov", 2005, "Ivan Vazov", "Prosveta",
		Characteristic::HistoricalFiction, Type::Comedy, Auditory::Adults);

	Comics comics("Spiderman", "The adventures of Marevel", 2003, "Marvel", "Anubis",
		Characteristic::Adventure, Type::Epic, Auditory::Teenagers, Periodicity::Yearly, 3);

	Periodical periodical("Za jenata", "Spisanieto na vs jeni", 2003, Periodicity::Weekly, 2);

	Library asd;

	asd.addPublication(&book, 2);
	asd.addPublication(&comics, 1);
	asd.addPublication(&periodical, 4);

	//asd.testPrint();

	//asd.printLibrary();

	//std::cout << std::endl;

	User u1("Petar");
	User u2("Ivan");
	User u3("Georgi");
	User u4("Mitko");

	asd.addUser(u1);
	asd.addUser(u2);
	asd.addUser(u3); 
	asd.addUser(u4);

	asd.borrow("Petar", 2, 1, 2, 2020);
	asd.borrow("Petar", 2, 1, 2, 2020);
	asd.borrow("Ivan", 1, 1, 1, 2020);
	asd.borrow("Georgi", 2, 1, 1, 2020);
	asd.borrow("Mitko", 3, 1, 1, 2020);

	//asd.printOverduedPublications(4, 3, 2020); 
	asd.printLibrary();

	asd.exit();
}

