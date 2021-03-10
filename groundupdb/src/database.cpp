#include "database.h"
#include "extensions/extdatabase.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace groundupdb;
using namespace groundupdbext;


class EmbeddedDatabase::Impl : public IDatabase{
public:
    Impl(std::string dbname, std::string fullpath);
    ~Impl();
    std::string getDirectory(void);

    void setKeyValue(std::string key, std::string value);

    std::string getKeyValue(std::string key);

    const static std::unique_ptr<IDatabase> createEmpty(std::string dbname);
    const static std::unique_ptr<IDatabase> load(std::string dbname);
    void destroy();

private:
    std::string m_name;
    std::string m_fullpath;

};


EmbeddedDatabase::Impl::Impl(std::string  dbname, std::string fullpath)
   :m_name(dbname), m_fullpath(fullpath)
{

}

EmbeddedDatabase::Impl::~Impl() {
  ;
  // Z. [Optional] Flush the latest known state to disc here
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(std::string dbname){
    std::string basedir(".groundupdb");
    if (!fs::exists(basedir)){
        fs::create_directory(basedir);
    }

    std::string dbfolder(basedir + "/" + dbname);
    if(!fs::exists(dbfolder)){
        fs::create_directory(dbfolder);
    }
    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::load(std::string dbname){
    std::string basedir(".groundupdb");
    std::string dbfolder(basedir + "/" +dbname);
    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder);
}

void EmbeddedDatabase::Impl::destroy(){
    if(fs::exists(m_fullpath)){
        fs::remove_all(m_fullpath);
    }
}

std::string EmbeddedDatabase::Impl::getDirectory(void) {
    return m_fullpath;
}

void EmbeddedDatabase::Impl::setKeyValue(std::string key ,std::string value){
    std::ofstream ofs;
    ofs.open(m_fullpath + "/" + key + "_string.kv", std::ios::out | std::ios::trunc);
    ofs << value;
    ofs.close();
}

std::string EmbeddedDatabase::Impl::getKeyValue(std::string key) {
    std::ifstream t(m_fullpath + "/" + key + "_string.kv");
    std::string value;

    t.seekg(0, std::ios::end);
    value.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    value.assign(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());

    return  value;
}


EmbeddedDatabase::EmbeddedDatabase(std::string dbname, std::string fullpath)
    : mImpl(std::make_unique<EmbeddedDatabase::Impl>(dbname, fullpath))
{
    ;
}

EmbeddedDatabase::~EmbeddedDatabase(){
    ;
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmpty(std::string dbname){
    return EmbeddedDatabase::Impl::createEmpty(dbname);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::load(std::string dbname){
    return EmbeddedDatabase::Impl::load(dbname);
}

void EmbeddedDatabase::destroy(){
    mImpl->destroy();
}

std::string EmbeddedDatabase::getDirectory(){
    return mImpl->getDirectory();
}

void EmbeddedDatabase::setKeyValue(std::string key, std::string value){
    mImpl->setKeyValue(key, value);
}

std::string EmbeddedDatabase::getKeyValue(std::string key){
    return mImpl->getKeyValue(key);
}


