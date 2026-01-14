#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <iostream>

class Quest {
public:
	Quest(std::string_view name, std::string_view description, int priority);
	const int id;
	bool isCompleted;
	const int priority;
	const std::string description;
	const std::string name;
	std::vector<Quest> prerequisites;

	void setComplete();
	void print();
	void addPrerequisite(Quest prerequisite);
};