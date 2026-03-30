#pragma once

#include <string>
#include "SQLiteCpp/SQLiteCpp.h"

class DatabaseManager {
public:
    DatabaseManager();
    void test(int n);
    bool addQuest(std::string name, std::string description = "", int priority = 0, std::vector<int> prerequisites = {});
    bool removeQuest(int questId);
    void listAllQuests();   // List ALL quests
    void listQuests(int n); // Lists the first n quests
    void listAllStates();   // List ALL states
    void listAllPrerequisites();    // List ALL prerequisites
    void listIds(int n);    // List the first n ids
    bool updateName(int id, std::string name);
    bool updateDescription(int id, std::string description);
    bool updatePriority(int id, int priority);
    bool updateAvailability(int id);
    bool updatePrerequisites(int id, std::vector<int> prerequisites);

private:
    SQLite::Database db;

    void resetFiles();
    void resetTables();
    void resetIds();
    void resetQuests();
    void resetPrerequisites();
    void resetStates();
    void resetViews();
    void resetTriggers();
    std::vector<int> getPrerequisites(int id);
    bool isAvailable(int id);
    bool addPrerequisite(int id, int dependency);
};