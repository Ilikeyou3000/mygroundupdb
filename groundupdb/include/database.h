 #ifndef DATABASE_H
#define DATABASE_H

#include <string>
namespace groundupdb {
class IDatabase
{
public:
    IDatabase()=default;
    virtual ~IDatabase() = default;
    virtual std::string getDirectory(void) = 0;

    virtual void setKeyValue(std::string key, std::string value) = 0;

    virtual std::string getKeyValue(std::string key)= 0;

    const static std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    const static std::unique_ptr<IDatabase> load(std::string dbname);
    virtual void destroy() = 0;

};
}


#endif // DATABASE_H
