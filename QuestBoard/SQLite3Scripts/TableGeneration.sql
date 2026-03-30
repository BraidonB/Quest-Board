-- Script Date: 3/6/2026 2:35 PM  - ErikEJ.SqlCeScripting version 3.5.2.103
db.exec("DROP TABLE IF EXISTS prerequisites");
    db.exec("DROP TABLE IF EXISTS quests");
    db.exec("DROP TABLE IF EXISTS states");
    db.exec("DROP TABLE IF EXISTS ids");

    db.exec("CREATE TABLE IF NOT EXISTS ids("
        "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
        "available BOOLEAN,"
        "FOREIGN KEY(id) REFERENCES quests(id)"
        ")");

    db.exec("CREATE TABLE IF NOT EXISTS states("
        "id INTEGER PRIMARY KEY UNIQUE NOT NULL,"
        "name VARCHAR(50)"
        ")");

    db.exec("CREATE TABLE IF NOT EXISTS quests ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
        "name VARCHAR(50),"
        "description VARCHAR(200) NULL,"
        "priority INTEGER,"
        "state_id INTEGER NOT NULL,"
        "FOREIGN KEY(state_id) REFERENCES states(id)"
        ")");

    db.exec("CREATE TRIGGER claim_id"
    "BEFORE INSERT ON quests"
    "BEGIN"
        "NEW.id = SELECT id FROM ids WHERE available = 1 ORDER BY id ASC"
        "THEN"
        "UPDATE ids"
        "SET available = 0"
        "WHERE id = NEW.id"
    ")");

    db.exec("CREATE TRIGGER release_id"
        "AFTER DELETE ON quests"
        "BEGIN"
        "   UPDATE ids"
        "   SET available = 1"
        "   WHERE id = OLD.id"
        ")");

    db.exec("CREATE TABLE IF NOT EXISTS prerequisites("
        "id INTEGER,"
        "dependency INTEGER,"
        "is_met BOOLEAN DEFAULT 0,"
        "FOREIGN KEY(id) REFERENCES quests(id)"
        "ON DELETE CASCADE,"
        "FOREIGN KEY(dependency) REFERENCES quests(id)"
        "ON DELETE CASCADE"
        ")");

    db.exec("INSERT OR IGNORE INTO states (id, name)"
        "VALUES(0, 'accepted')");

    db.exec("INSERT OR IGNORE INTO states(id, name)"
        "VALUES(1, 'available')");

    db.exec("INSERT OR IGNORE INTO states(id, name)"
        "VALUES(2, 'unavailable')");

    db.exec("INSERT OR IGNORE INTO states (id, name)"
        "VALUES(3, 'completed')");