/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERDATABASE_H_
#define SERVERDATABASE_H_

#include "engine/engine.h"

namespace conf {
	class ConfigManager;
}

class ServerDatabase : public Logger {
	static Vector<Database*>* databases;
	static AtomicInteger currentDB;
	int dbSchemaVersion;

public:
	ServerDatabase(conf::ConfigManager* configManager);
	~ServerDatabase();

	const static int DEFAULT_SERVERDATABASE_INSTANCES = 8;

	inline static Database* instance() {
		if (databases == nullptr)
			throw DatabaseException("No Server Database initiated");

		int i = currentDB.get() % databases->size();

		currentDB.increment();

		return databases->get(i);
	}

	inline int getSchemaVersion() {
		return dbSchemaVersion;
	}
private:
	void alterDatabase(int nextVersion, const String& alterSql);
	void updateDatabaseSchema();
};

#endif /*SERVERDATABASE_H_*/
