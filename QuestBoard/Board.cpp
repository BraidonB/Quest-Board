#include "Quest.h"
#include "Board.h"
#include "QuestList.h"
#include <string>
#include <algorithm>
#include <iostream>

bool isAvailable(const Quest* target) {
	if (target->prerequisites.empty()) { return true; }
	for (const Quest* quest : target->prerequisites) {
		if (!quest->isCompleted) {
			return false;
		}
	}
	return true;
}

Board::Board() {}

void Board::addQuest(Quest* quest) {
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
		std::cout << "\nAvailable quests:\n";
		available.print();
		break;

	case 1:		// unavailable
		std::cout << "\nUnavailable quests:\n";
		unavailable.print();
		break;

	case 2:		// active
		std::cout << "\nAccepted quests:\n";
		active.print();
		break;

	case 3:		// completed
		std::cout << "\nCompleted quests:\n";
		completed.print();
		break;
	}
}