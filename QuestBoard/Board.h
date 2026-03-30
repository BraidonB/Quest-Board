#pragma once

#include "Quest.h"
#include "QuestList.h"

class Board {
public:
	Board();

	void addQuest(const Quest& quest);
	void editQuest();
	void completeQuest();
	void reopenQuest();
	void acceptQuest();

	void printList(const int i);

private:
	QuestList available;
	QuestList unavailable;
	QuestList active;
	QuestList completed;
};