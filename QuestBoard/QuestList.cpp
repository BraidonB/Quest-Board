#include "QuestList.h"
#include "Quest.h"

static bool sortByAlphabet(const Quest* q1, const Quest* q2) {
	return q1->name < q2->name;
}
static bool sortByPriority(const Quest* q1, const Quest* q2) {
	return q1->priority < q2->priority;
}

void QuestList::sortListAlph() {
	std::sort(data.begin(), data.end(), sortByAlphabet);
}

void QuestList::sortListPrio() {
	std::sort(data.begin(), data.end(), sortByPriority);
}

void QuestList::push_back(Quest* quest) {
	data.push_back(quest);
}

Quest* QuestList::removeQuest(const std::string name) {
	return nullptr;
}

bool QuestList::empty() const {
	return data.empty();
}

void QuestList::print() const {
	for (const Quest* quest : data) {
		std::cout << " - " << quest->name << "\n";
	}
}

QuestList::const_iterator QuestList::begin() const { return data.begin(); }
QuestList::const_iterator QuestList::end() const { return data.end(); }