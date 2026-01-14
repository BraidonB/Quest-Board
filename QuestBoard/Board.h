#pragma once

#include "Quest.h"
#include <vector>

class Board {
public:

private:
	vector<Quest> available;
	vector<Quest> unavailable;
	vector<Quest> active;
	vector<Quest> completed;
};