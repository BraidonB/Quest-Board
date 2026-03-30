#include "SQLiteCpp/SQLiteCpp.h"
#include "DatabaseManager.h"
#include <iostream>
#include <string>
#include <filesystem>

DatabaseManager::DatabaseManager()
try :
    db(SQLite::Database("./Quests.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE))
{
    db.exec("PRAGMA foreign_keys = ON");

    resetFiles();
}
catch (std::exception& e) {
    std::cout << "SQLite exception: " << e.what() << std::endl;
}

void DatabaseManager::test(int n) {
    // Insert n quests
    //std::cout << "====  Inserting " << n << " quests  ====" << std::endl;
    //for (int i = 1; i <= n; ++i) {
    //    addQuest(std::format("quest {}", i));
    //}

    db.exec("INSERT INTO quests (id, name, description, priority, state_id)\n"
        "VALUES(0, 'quest 1', '', 3, 3)");

    db.exec("INSERT INTO quests (id, name, description, priority, state_id)\n"
        "VALUES(1, 'quest 2', '', 3, 3)");

    addQuest("quest 3", "", 0, { 0, 1 }); 

    SQLite::Statement statement(db, "SELECT id FROM quests WHERE name = 'quest 3' LIMIT 1");
    statement.executeStep();
    int id = statement.getColumn("id").getInt();

    db.exec("INSERT INTO quests (id, name, description, priority, state_id)\n"
        "VALUES(5, 'quest 4', '', 3, 2)");

    std::cout << "\n\neverything ok, quitting\n";
}

bool DatabaseManager::isAvailable(int id) {
    bool isMet = false;
    try {
        SQLite::Statement statement(db, std::format("SELECT COUNT(id) AS unmet FROM prerequisites WHERE id = {} AND is_met = 0", id));

        statement.executeStep();
        isMet = statement.getColumn("unmet").getInt() == 0;
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
    }
    return isMet;
}

bool DatabaseManager::addPrerequisite(int id, int dependency) {
    if (id == dependency) return 0;

    try {
        SQLite::Statement getDependency(db, std::format("SELECT * FROM quests WHERE id = {}", dependency));

        bool is_met = 0;

        while (getDependency.executeStep()) {
            is_met = getDependency.getColumn("state_id").getInt() == 3;
        }

        db.exec(std::format("INSERT OR IGNORE INTO prerequisites (id, dependency, is_met)\n"
            "VALUES ({}, {}, {})", id, dependency, is_met));

        return 1;
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

bool DatabaseManager::addQuest(std::string name, std::string description, int priority, std::vector<int> prerequisites) {
    SQLite::Statement getNextId(db, "SELECT * FROM ids WHERE available = 1 ORDER BY id ASC LIMIT 1");
    getNextId.executeStep();
    int nextId = getNextId.getColumn("id").getInt();

    try {
        SQLite::Transaction transaction(db);
        db.exec(std::format("INSERT INTO quests (id, name, description, priority, state_id)\n"
            "VALUES({}, '{}', '{}', {}, {})", nextId, name, description, priority, 1));
        
        transaction.commit();

        for (auto i : prerequisites) {
            addPrerequisite(nextId, i);
        }

        updateAvailability(nextId);
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
    return 1;
}

bool DatabaseManager::removeQuest(int questId) {
    try {
        db.exec(std::format("DELETE FROM quests WHERE id = {}", questId));
        return 1;
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

std::vector<int> DatabaseManager::getPrerequisites(int id) {
    std::vector<int> prerequisites = {};

    SQLite::Statement query(db, std::format("SELECT dependency FROM prerequisites WHERE id = {}", id));

    while (query.executeStep()) {
        prerequisites.push_back(query.getColumn("dependency").getInt());
    }
    return prerequisites;
}

bool DatabaseManager::updateName(int id, std::string name) {
    try {
        db.exec(std::format("UPDATE quests\n"
            "SET name = '{}'\n"
            "WHERE id = {}", name, id));
        return 1;
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

bool DatabaseManager::updateDescription(int id, std::string description) {
    try {
        db.exec(std::format("UPDATE quests\n"
            "SET description = '{}'\n"
            "WHERE id = {}", description, id));
        return 1;
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

bool DatabaseManager::updatePriority(int id, int priority) {
    try {
        db.exec(std::format("UPDATE quests\n"
            "SET priority = {}\n"
            "WHERE id = {}", priority, id));
        return 1;
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

bool DatabaseManager::updateAvailability(int id) {
    try {
        db.exec(std::format("UPDATE quests\n"
            "SET state_id = {}\n"
            "WHERE id = {}",
            (isAvailable(id) ? 1 : 2), id));
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

bool DatabaseManager::updatePrerequisites(int id, std::vector<int> prerequisites) {
    std::stringstream ss;
    for (auto prereq : prerequisites) {
        ss << prereq << ",";
    }
    std::string list = ss.str();
    std::size_t sz = list.size();
    if (list.size() > 1 && list.substr(sz - 1) == ",") {
        list = list.substr(0, sz - 1);
    }

    for (auto i : prerequisites) {
        addPrerequisite(id, i);
    }

    try {
        db.exec(std::format("DELETE FROM prerequisites\n"
            "WHERE id = {}\n"
            "AND\n"
            "dependency NOT IN ({})", id, list));

        updateAvailability(id);
        return 1;
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

void DatabaseManager::listQuests(int n) {
    try {
        SQLite::Statement listAll(db, std::format("SELECT * FROM quests ORDER BY id ASC LIMIT {}", n));
        while (listAll.executeStep()) {
            std::cout << listAll.getColumn("id").getInt() << " | " << listAll.getColumn("name").getString() << " | " << listAll.getColumn("priority").getInt() << " | " << listAll.getColumn("state_id") << "\n"
                << listAll.getColumn("description").getString() << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
    }
}

void DatabaseManager::listAllQuests() {
    try {
        SQLite::Statement listAll(db, "SELECT * FROM quests");
        while (listAll.executeStep()) {
            std::cout << listAll.getColumn("id").getInt() << " | " << listAll.getColumn("name").getString() << " | " << listAll.getColumn("priority").getInt() << " | " << listAll.getColumn("state_id") << "\n"
                << listAll.getColumn("description").getString() << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
    }
}

void DatabaseManager::listAllStates() {
    try {
        SQLite::Statement listAll(db, "SELECT * FROM states");
        while (listAll.executeStep()) {
            std::cout << listAll.getColumn("id").getInt() << " | " << listAll.getColumn("name").getString() << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
    }
}

void DatabaseManager::listAllPrerequisites() {
    try {
        SQLite::Statement listAll(db, "SELECT * FROM prerequisites");
        while (listAll.executeStep()) {
            std::cout << listAll.getColumn("id").getInt() << " | " << listAll.getColumn("dependency").getString() << " | " << listAll.getColumn("is_met").getInt() << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
    }
}

void DatabaseManager::listIds(int n) {
    SQLite::Statement getIds(db, std::format("SELECT * FROM ids LIMIT {}", n));

    while (getIds.executeStep()) {
        std::cout << getIds.getColumn("id").getInt() << " | " << getIds.getColumn("available").getInt() << std::endl;
    }
}

void DatabaseManager::resetStates() {
    SQLite::Transaction transaction(db);

    db.exec("DROP TABLE IF EXISTS states");

    db.exec("CREATE TABLE IF NOT EXISTS states(\n"
        "id INTEGER PRIMARY KEY UNIQUE NOT NULL,\n"
        "name VARCHAR(50)\n"
        ")");

    db.exec("INSERT OR IGNORE INTO states (id, name)\n"
        "VALUES(0, 'accepted')");

    db.exec("INSERT OR IGNORE INTO states(id, name)\n"
        "VALUES(1, 'available')");

    db.exec("INSERT OR IGNORE INTO states(id, name)\n"
        "VALUES(2, 'unavailable')");

    db.exec("INSERT OR IGNORE INTO states (id, name)\n"
        "VALUES(3, 'completed')");

    transaction.commit();
}

void DatabaseManager::resetIds() {
    SQLite::Transaction transaction(db);

    db.exec("DROP TABLE IF EXISTS ids");

    db.exec("CREATE TABLE IF NOT EXISTS ids(\n"
        "id INTEGER PRIMARY KEY UNIQUE NOT NULL,\n"
        "available BOOLEAN DEFAULT 1\n"
        ")");

    transaction.commit();

    std::stringstream ss;

    ss << "INSERT INTO ids (id) VALUES (0)";

    for (int i = 1; i <= 99999; i++) {
        ss << ",(" << i << ")";
    }

    db.exec(ss.str());
}

void DatabaseManager::resetQuests() {
    SQLite::Transaction transaction(db);

    db.exec("DROP TABLE IF EXISTS quests");

    db.exec("CREATE TABLE IF NOT EXISTS quests (\n"
        "id INTEGER PRIMARY KEY UNIQUE NOT NULL,\n"
        "name VARCHAR(50),\n"
        "description VARCHAR(200) NULL,\n"
        "priority INTEGER,\n"
        "state_id INTEGER DEFAULT 1 NOT NULL,\n"
        "FOREIGN KEY(state_id) REFERENCES states(id)\n"
        ")");

    transaction.commit();
}

void DatabaseManager::resetPrerequisites() {
    SQLite::Transaction transaction(db);

    db.exec("DROP TABLE IF EXISTS prerequisites");

    db.exec("CREATE TABLE IF NOT EXISTS prerequisites(\n"
        "id INTEGER,\n"
        "dependency INTEGER,\n"
        "is_met BOOLEAN DEFAULT 0,\n"
        "PRIMARY KEY (id, dependency)\n"
        "FOREIGN KEY(id) REFERENCES quests(id)\n"
        "ON DELETE CASCADE,\n"
        "FOREIGN KEY(dependency) REFERENCES quests(id)\n"
        "ON DELETE CASCADE\n"
        ")");

    transaction.commit();
}

void DatabaseManager::resetTriggers() {
    SQLite::Transaction transaction(db);

    db.exec("DROP TRIGGER IF EXISTS make_not_available");

    db.exec("CREATE TRIGGER make_not_available\n"
        "AFTER INSERT ON prerequisites\n"
        "WHEN NEW.is_met = 0\n"
        "BEGIN\n"
        "UPDATE quests\n"
        "SET state_id = 2\n"
        "WHERE id = NEW.id;\n"
        "END");

    db.exec("DROP TRIGGER IF EXISTS claim_id");

    db.exec("CREATE TRIGGER claim_id\n"
        "AFTER INSERT ON quests\n"
        "BEGIN\n"
        "UPDATE ids\n"
        "SET available = 0\n"
        "WHERE id = NEW.id;\n"
        "END");

    db.exec("DROP TRIGGER IF EXISTS release_id");

    db.exec("CREATE TRIGGER release_id\n"
        "AFTER DELETE ON quests\n"
        "BEGIN\n"
        "UPDATE ids\n"
        "SET available = 1\n"
        "WHERE id = OLD.id;\n"
        "END");

    transaction.commit();
}

void DatabaseManager::resetViews() {
    SQLite::Transaction transaction(db);

    db.exec("DROP VIEW IF EXISTS next_id");

    db.exec("CREATE VIEW next_id\n"
        "AS\n"
        "SELECT id FROM ids\n"
        "WHERE available = 1\n"
        "ORDER BY id ASC\n"
        "LIMIT 1");

    transaction.commit();
}

void DatabaseManager::resetTables() {
    resetIds();
    resetPrerequisites();
    resetQuests();
    resetStates();
}

void DatabaseManager::resetFiles() {
    resetTables();
    resetViews();
    resetTriggers();
}