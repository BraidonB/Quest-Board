// QuestBoard.cpp : Defines the entry point for the application.
//

#include "QuestBoard.h"
#include "Quest.h"
#include <iostream>

using namespace std;

int main()
{
	const std::string name1 = "A fair test";
	const std::string description1 = "This test is only for the bravest of hearts to test their mettle(code).";
	int priority1 = 5;
	Quest quest1(name1, description1, priority1);

	const std::string name2 = "A slightly fairer test";
	const std::string description2 = "This test is of priority 2, and is a dependency of the fair test.";
	int priority2 = 3;
	Quest quest2(name2, description2, priority2);

	const std::string name3 = "The most fair of tests";
	const std::string description3 = "This test is the final dependency of A Fair Test.";
	int priority3 = 1;
	Quest quest3(name3, description3, priority3);

	quest1.addPrerequisite(quest2);
	quest1.addPrerequisite(quest3);

	quest1.print();
	//std::cout << quest1.name << ":\n" << quest1.priority << "\n\n" << quest1.description << std::endl;
	return 0;
}