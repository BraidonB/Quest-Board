#pragma once

#include <string>
#include <string>
#include <vector>
#include <iostream>

class Quest {
public:
	Quest(int id, std::string name, std::string description, int priority, std::vector<Quest*> prereqs = {});
	const int id;
	bool isCompleted;
	const int priority;
	const std::string description;
	const std::string name;
	std::vector<Quest*> prerequisites;

	void setComplete();
	void print();
	void addPrerequisite(Quest* prerequisite);
};