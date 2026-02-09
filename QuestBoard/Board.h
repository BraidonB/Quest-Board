#pragma once

#include "Quest.h"
#include "QuestList.h"

class Board {
public:
	Board();

	void addQuest(Quest& quest);
	void editQuest();
	void completeQuest();
	void reopenQuest();
	void acceptQuest();

	void printList(const int i);

	QuestList available;
	QuestList unavailable;
	QuestList active;
	QuestList completed;
};