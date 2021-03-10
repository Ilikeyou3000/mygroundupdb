#ifndef EXTDATABASE_H
#define EXTDATABASE_H

#include "database.h"
namespace groundupdbext {

using namespace groundupdb;

class EmbeddedDatabase: public IDatabase{
public:
    EmbeddedDatabase(std::string dbname, std::string fullpath);

    ~EmbeddedDatabase();
    std::string getDirectory(void);

    void setKeyValue(std::string key, std::string value);

    std::string getKeyValue(std::string key);

    const static std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    const static std::unique_ptr<IDatabase> load(std::string dbname);
    void destroy();

    class Impl;
private:
    std::unique_ptr<Impl> mImpl;
};

}



#endif
