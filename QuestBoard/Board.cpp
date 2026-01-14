#include "Quest.h"
#include "Board.h"
#include <vector>
#include <string>

bool isAvailable(Quest target) {
	if (target.prerequisites.empty()) { return true; }
	for (auto quest : target.prerequisites) {
		if (!quest->isCompleted) {
			return false;
		}
	}
	return true;
}

Board::Board() {}

void Board::addQuest(Quest quest) {

	if (isAvailable(quest)) {
		available.push_back(quest);
	}
	else {
		unavailable.push_back(quest);
	}
}

void Board::editQuest() {

}

void Board::completeQuest() {

}

void Board::reopenQuest() {

}

void Board::removeQuest() {

}

void Board::acceptQuest() {

}

void print(std::vector<Quest> questList) {
	for (auto quest : questList) {
		std::cout << " - " << quest.name << "\n";
	}
}

void Board::printList(const int i) {
	switch (i) {
	case 0:		// available
		std::cout << "\nAvailable quests:\n";
		print(available);
		break;

	case 1:		// unavailable
		std::cout << "\nUnavailable quests:\n";
		print(unavailable);
		break;

	case 2:		// active
		std::cout << "\nAccepted quests:\n";
		print(active);
		break;

	case 3:		// completed
		std::cout << "\nCompleted quests:\n";
		print(completed);
		break;
	}
}