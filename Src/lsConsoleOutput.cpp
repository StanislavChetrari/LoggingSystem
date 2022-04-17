#include "lsConsoleOutput.hpp"

#include <iostream>

ls::ConsoleOutput::ConsoleOutput() :
    mName("unnamed")
{
    mDefaultWriteCallback = [](uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
    {
        std::cout << dateTimeStr << " " << typeName << "(" << type << ") " << msg << std::endl;
    };
}

ls::ConsoleOutput::~ConsoleOutput()
{

}

void ls::ConsoleOutput::write(uint32_t type, const std::string& typeName, const std::string &msg, const std::string& dateTimeStr)
{
    auto findIter = mMapMsgTypeToWriteCallback.find(type);
    if(mMapMsgTypeToWriteCallback.end() != findIter)
    {
        findIter->second(type, typeName, msg, dateTimeStr);
    }
    else
    {
        mDefaultWriteCallback(type, typeName, msg, dateTimeStr);
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

std::vector<uint32_t> ls::ConsoleOutput::getMessageTypes()
{
    std::vector<uint32_t> msgTypes;
    for(auto iter = mMapMsgTypeToWriteCallback.begin(); iter != mMapMsgTypeToWriteCallback.end(); ++iter)
    {
        msgTypes.push_back(iter->first);
    }
    return msgTypes;
}

void ls::ConsoleOutput::setDefaultWriteCallback(const WriteMessageCallback& callback)
{
    mDefaultWriteCallback = callback;
}

void ls::ConsoleOutput::setWriteCallbackForMsgType(uint32_t msgType, const WriteMessageCallback& callback)
{
    mMapMsgTypeToWriteCallback.insert(std::make_pair(msgType, callback));
}
