#include "Quest.h"

#include <string>
#include <string_view>
#include <vector>
#include <iostream>

Quest::Quest(std::string_view name, std::string_view description, int priority)
	: id(5) /*TODO make unique id's*/, isCompleted(false), priority(priority), description(description), name(name)
{
}

void Quest::setComplete() {
	isCompleted = true;
}

void Quest::print() {
	std::cout << "<< " << name << " >>\n"
		<< "Priority: " << priority
		<< "\n\n" << description
		<< "\n\nPrerequisites:\n";

	for (auto prerequisite : prerequisites) {
		std::cout << prerequisite.name << "\n";
	}
	std::cout << std::endl;
}

void Quest::addPrerequisite(Quest prerequisite) {
	prerequisites.push_back(prerequisite);
}