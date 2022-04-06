#include "lsConsoleOutput.hpp"

#include <iostream>

ls::ConsoleOutput::ConsoleOutput() :
    mName("unnamed")
{
    mDefaultWriteCallback = [](unsigned int type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
    {
        std::cout << dateTimeStr << " " << typeName << "(" << type << ") " << msg << std::endl;
    };
}

ls::ConsoleOutput::~ConsoleOutput()
{

}

void ls::ConsoleOutput::write(unsigned int type, const std::string& typeName, const std::string &msg, const std::string& dateTimeStr)
{
    auto findIter = mMapMsgTypeToWriteCallback.find(type);
    if(mMapMsgTypeToWriteCallback.end() == findIter)
    {
        findIter->second(type, typeName, msg, dateTimeStr);
    }
}

void ls::ConsoleOutput::setName(const std::string &name)
{
    mName = name;
}

std::string ls::ConsoleOutput::getName() const
{
    return mName;
}
