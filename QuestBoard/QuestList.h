#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

#include "Quest.h"

class QuestList {
public:
	void push_back(Quest* quest) {
		data.push_back(quest);
	}

	Quest* removeQuest(const std::string name) {
		return nullptr;
	}

	void sortListAlph() {
		std::sort(data.begin(), data.end(), sortByAlphabet);
	}

	void sortListPrio() {
		std::sort(data.begin(), data.end(), sortByPriority);
	}

	void print() const {
		for (const Quest* quest : data) {
			std::cout << " - " << quest->name << "\n";
		}
	}

	using iterator = std::vector<Quest*>::iterator;
	iterator begin() { return data.begin(); }
	iterator end() { return data.end(); }

private:
	std::vector<Quest*> data;
	bool sortByAlphabet(const Quest* q1, const Quest* q2) {
		return q1->name < q2->name;
	}
	bool sortByPriority(const Quest* q1, const Quest* q2) { return q1->priority < q2->priority; }
};