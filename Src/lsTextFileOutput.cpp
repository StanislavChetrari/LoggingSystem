#include "lsTextFileOutput.hpp"

#include <iostream>

ls::TextFileOutput::TextFileOutput()
    : mName("unnamed")
    , mFilePath("")
{
    mDefaultWriteCallback = [](std::ofstream& fileOut, uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
    {
        fileOut << dateTimeStr << " " << typeName << "(" << type << ") " << msg << std::endl;
    };
}

ls::TextFileOutput::~TextFileOutput()
{
    close();
}

void ls::TextFileOutput::write(uint32_t type, const std::string& typeName, const std::string &msg, const std::string& dateTimeStr)
{
    if((bool)mFile)
    {
        auto findIter = mMapMsgTypeToWriteCallback.find(type);
        if(mMapMsgTypeToWriteCallback.end() != findIter)
        {
            findIter->second(mFile, type, typeName, msg, dateTimeStr);
        }
        else
        {
            mDefaultWriteCallback(mFile, type, typeName, msg, dateTimeStr);
        }
    }
}

void ls::TextFileOutput::setName(const std::string& name)
{
    mName = name;
}

std::string ls::TextFileOutput::getName() const
{
    return mName;
}

std::vector<uint32_t> ls::TextFileOutput::getMessageTypes()
{
    std::vector<uint32_t> msgTypes;
    for(auto iter = mMapMsgTypeToWriteCallback.begin(); iter != mMapMsgTypeToWriteCallback.end(); ++iter)
    {
        msgTypes.push_back(iter->first);
    }
    return msgTypes;
}

bool ls::TextFileOutput::open(const std::string& filePath, FileOpenType fileOpenType)
{
    std::ios_base::openmode openmode = std::ios_base::out | std::ios_base::binary;
    switch(mFileOpenType)
    {
        case FileOpenType::Append:
        {
            openmode |= std::ios_base::app;
        }break;
    };

    mFile.open(filePath, openmode);
    if((bool)mFile)
    {
        mFilePath = filePath;
        mFileOpenType = fileOpenType;
        return true;
    }
    else
    {
        mFilePath = "";
        mFileOpenType = FileOpenType::NewOrOverwrite;
        return false;
    }
}

void ls::TextFileOutput::close()
{
    mFile.close();
}

std::string ls::TextFileOutput::getFilePath() const
{
    return mFilePath;
}

ls::TextFileOutput::FileOpenType ls::TextFileOutput::getFileOpenType() const
{
    return mFileOpenType;
}

void ls::TextFileOutput::setDefaultWriteCallback(const WriteMessageCallback& callback)
{
    mDefaultWriteCallback = callback;
}

void ls::TextFileOutput::setWriteCallbackForMsgType(uint32_t msgType, const WriteMessageCallback& callback)
{
    mMapMsgTypeToWriteCallback.insert(std::make_pair(msgType, callback));
}
