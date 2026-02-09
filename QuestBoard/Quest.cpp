#include "Quest.h"

#include <string>
#include "QuestList.h"
#include <iostream>

Quest::Quest(int id, std::string name, std::string description, int priority, QuestList prereqs)
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

	prerequisites.print();
	std::cout << std::endl;
}

void Quest::addPrerequisite(Quest* prerequisite) {
	prerequisites.push_back(prerequisite);
}