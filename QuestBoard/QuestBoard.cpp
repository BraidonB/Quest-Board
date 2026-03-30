// QuestBoard.cpp : Defines the entry point for the application.
//

#include "QuestBoard.h"
#include "Quest.h"
#include "Board.h"
#include <iostream>
#include "QuestList.h"
#include "Windows.h"
#include "DatabaseManager.h"

using namespace std;

int main()
{
	DatabaseManager dbManager;

	dbManager.test(5);

	return 0;
}