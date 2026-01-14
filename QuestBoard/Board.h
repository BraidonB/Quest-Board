#pragma once

#include "Quest.h"
#include <vector>

class Board {
public:
	Board();

	void addQuest(Quest quest);
	void editQuest();
	void completeQuest();
	void reopenQuest();
	void removeQuest();
	void acceptQuest();

	void printList(const int i);

	std::vector<Quest> available;
	std::vector<Quest> unavailable;
	std::vector<Quest> active;
	std::vector<Quest> completed;
};