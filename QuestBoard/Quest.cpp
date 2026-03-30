#include "Quest.h"

#include <string>
#include "QuestList.h"
#include <iostream>

Quest::Quest(int id, const std::string& name, const std::string& description, int priority, const QuestList& prereqs)
	: id{ id }, isCompleted{ false }, priority{ priority }, description{ description }, name{ name }, prerequisites{ prereqs }
{

}

void Quest::setComplete() {
	isCompleted = true;
}

void Quest::print() const {
	std::cout << "  --== " << name << " ==--\n"
		<< "  Priority: " << priority
		<< "\n\n  " << description
		<< "\n\n  Prerequisites:\n  ";

	prerequisites.print();
	std::cout << std::endl;
}

void Quest::addPrerequisite(const Quest& prerequisite) {
	prerequisites.push_back(prerequisite);
}