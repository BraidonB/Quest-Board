#include "Quest.h"
#include "Board.h"
#include "QuestList.h"
#include <string>
#include <algorithm>
#include <iostream>

bool isAvailable(const Quest& target) {
	if (target.prerequisites.empty()) { return true; }
	for (const Quest& quest : target.prerequisites) {
		if (!quest.isCompleted) {
			return false;
		}
	}
	return true;
}

Board::Board() {}

void Board::addQuest(const Quest& quest) {
	if (isAvailable(quest)) {
		available.push_back(quest);
		available.sortListAlph();
	}
	else {
		unavailable.push_back(quest);
		unavailable.sortListAlph();
	}
}

void Board::editQuest() {

}

void Board::completeQuest() {

}

void Board::reopenQuest() {

}

void Board::acceptQuest() {

}

void Board::printList(const int i) {
	switch (i) {
	case 0:		// available
		std::cout << "=+++= Available quests =+++=\n";
		available.printDetails();
		break;

	case 1:		// unavailable
		std::cout << "=+++= Unavailable quests =+++=\n";
		unavailable.printDetails();
		break;

	case 2:		// active
		std::cout << "=+++= Accepted quests =+++=\n";
		active.printDetails();
		break;

	case 3:		// completed
		std::cout << "=+++= Completed quests =+++=\n";
		completed.printDetails();
		break;
	}
}