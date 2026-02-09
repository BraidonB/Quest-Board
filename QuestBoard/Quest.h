#pragma once

#include <string>
#include "QuestList.h"
#include <iostream>

class Quest {
public:
	Quest(int id, std::string name, std::string description, int priority, QuestList prereqs = {});
	int id;
	bool isCompleted;
	int priority;
	std::string description;
	std::string name;
	QuestList prerequisites;

	void setComplete();
	void print();
	void addPrerequisite(Quest* prerequisite);
};