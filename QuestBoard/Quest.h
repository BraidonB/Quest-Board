#pragma once

#include <string>
#include "QuestList.h"
#include <iostream>

class Quest {
public:
	Quest(int id, const std::string& name, const std::string& description, int priority, const QuestList& prereqs = QuestList());
	int id;
	bool isCompleted;
	int priority;
	std::string description;
	std::string name;
	QuestList prerequisites;

	void setComplete();
	void print() const;
	void addPrerequisite(const Quest& prerequisite);
};