// QuestBoard.cpp : Defines the entry point for the application.
//

#include "QuestBoard.h"
#include "Quest.h"
#include "Board.h"
#include <iostream>
#include <vector>

int main()
{
	Board questBoard;
	const std::string name = "A Fair Quest";
	const std::string description = "This quest is a test for testing.";
	const int id = 1;
	const int priority = 5;
	std::vector<Quest*> prereqs = {};
	std::string dummyName = "Dummy quest";
	std::string dummyDescription = "This is simply a dummy quest";
	for (int i = 2; i < 5; ++i) {
		Quest quest(i, dummyName, dummyDescription, 3);
		questBoard.addQuest(quest);
		prereqs.push_back(&quest);
	}
	Quest quest(id, name, description, priority, prereqs);

	questBoard.addQuest(quest);

	questBoard.printList(0);
	questBoard.printList(1);
	questBoard.printList(2);
	questBoard.printList(3);

	return 0;
}