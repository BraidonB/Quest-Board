// QuestBoard.cpp : Defines the entry point for the application.
//

#include "QuestBoard.h"
#include "Quest.h"
#include "Board.h"
#include <iostream>
#include "QuestList.h"

int main()
{
	Board questBoard;
	const std::string namec = "C Fair Quest";
	const std::string descriptionc = "This quest is a test for testing.";
	const int idc = 1;
	const int priorityc = 1;

	Quest questc(idc, namec, descriptionc, priorityc);

	const std::string namea = "A Fair Quest";
	const std::string descriptiona = "This quest is a test for testing.";
	const int ida = 1;
	const int prioritya = 5;

	Quest questa(ida, namea, descriptiona, prioritya);

	const std::string nameb = "B Fair Quest";
	const std::string descriptionb = "This quest is a test for testing.";
	const int idb = 1;
	const int priorityb = 3;

	Quest questb(idb, nameb, descriptionb, priorityb);

	questBoard.addQuest(questc);
	questBoard.addQuest(questa);
	questBoard.addQuest(questb);

	//questBoard.printList(0);

	return 0;
}