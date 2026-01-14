#include "Quest.h"

#include <string>
#include <string>
#include <vector>
#include <iostream>

Quest::Quest(int id, std::string name, std::string description, int priority, std::vector<Quest*> prereqs)
	: id{ id }, isCompleted{ false }, priority{ priority }, description{ description }, name{ name }, prerequisites{ std::move(prereqs) }
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
		std::cout << prerequisite->name << "\n";
	}
	std::cout << std::endl;
}

void Quest::addPrerequisite(Quest* prerequisite) {
	prerequisites.push_back(prerequisite);
}