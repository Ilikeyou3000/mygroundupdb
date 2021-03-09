#include "test.h"

#include <filesystem>
#include <string>
#include "groundupdb/groundupdb.h"

namespace fs = std::filesystem;

TEST_CASE("(Create a new empty database", "[createEmptyDB]"){

    // story:
    //      [who] As a dagtabase administrator
    //      [what] I need to create a new empty database
    //      [Value] So I can later store and retrieve data
    SECTION("Default settings"){
        std::string dbname("myemptydb");
        Database db(GroundUpDB::createEmptyDB(dbname));

        //We know we have been successful when
        //1. We have a valid database reference returned
        //  - No test -> The above would have errored
        //2. The DB has a folder that exists on the filesystem
        REQUIRE(fs::is_directory(fs::status(db.getDirectory())));

        //3. The dastabase folder is emtpy (no database file yet)
        const auto& p = fs::directory_iterator(db.getDirectory());
        REQUIRE(p == end(p) );

        db.destroy();
        REQUIRE(!fs::is_directory(fs::status(db.getDirectory())));
    }
}

TEST_CASE("LOAD an existing database", "[loadDB]"){
    // story:-
    //      [Who] as a database user
    //      [What] I need to create a reference to a database
    //      [Value] So I can store and retrieve data

    SECTION("Default settings"){
        std::string dbname("myemptydb");
        Database db(GroundUpDB::createEmptyDB(dbname));

        Database db2(GroundUpDB::loadDB(dbname));

        REQUIRE(fs::is_directory(fs::status(db2.getDirectory())));

        const auto& p = fs::directory_iterator(db2.getDirectory());
        REQUIRE(p == end(p));

        db2.destroy();
        REQUIRE(!fs::exists(fs::status(db2.getDirectory())));
    }
}
