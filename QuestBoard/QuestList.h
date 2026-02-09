#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

class Quest;
//#include "Quest.h"

class QuestList {
public:
	void push_back(Quest* quest);

	// TODO: Remove a quest from the data list.
	//		 Maintain list order.
	Quest* removeQuest(const std::string name);

	bool empty() const;

	void print() const;

	void sortListAlph();

	void sortListPrio();

	using const_iterator = std::vector<Quest*>::const_iterator;
	const_iterator begin() const ;
	const_iterator end() const;

private:
	std::vector<Quest*> data;
};