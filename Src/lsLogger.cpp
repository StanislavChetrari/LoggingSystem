#include "lsLogger.hpp"

#include <ctime>

#include "lsIOutput.hpp"

ls::Exceptions::OutputIncorrectMsgTypes::OutputIncorrectMsgTypes(const std::string& whatStr)
    : mWhatString(whatStr)
{

}

const char* ls::Exceptions::OutputIncorrectMsgTypes::what() const noexcept
{
    return mWhatString.c_str();
}

std::string ls::Exceptions::OutputIncorrectMsgTypes::constructWhatStr(const std::vector<MsgData>& vectorMsgData)
{
    std::string whatString = "Exception OutputIncorrectMsgTypes. IOutput contains one or more invalid message types:\n";
    for(const auto& data: vectorMsgData)
    {
        whatString += "Message type " + std::to_string(data.mTypeId) + " in output \"" + data.mOutputName + "\"\n";
    }
    return whatString;
}

ls::Logger::Logger(std::map<unsigned int, std::string> msgTypes, std::vector<std::shared_ptr<IOutput>> outputs)
    : mMapMsgTypes(msgTypes)
    , mVectorOutputs(outputs)
{
    mGetDateTimeAsString = []()
    {
        std::string retStr("");

        std::time_t utcTime = std::time(nullptr);
        if((std::time_t)(-1) != utcTime)
        {
            std::tm* utcTmTime = std::gmtime(&utcTime);
            // dd.mm.yyyy hh:mm:ss:ms
            retStr += std::to_string(utcTmTime->tm_hour);
            retStr += ":";
            retStr += std::to_string(utcTmTime->tm_min + 1);
            retStr += ":";
            retStr += std::to_string(utcTmTime->tm_sec);
            retStr += " ";
            retStr += std::to_string(utcTmTime->tm_mday);
            retStr += ".";
            retStr += std::to_string(utcTmTime->tm_mon + 1);
            retStr += ".";
            retStr += std::to_string(utcTmTime->tm_year + 1900);
        }

        return retStr;
    };

    // Check if message types in outputs exist in msgTypes map.
    std::vector<Exceptions::OutputIncorrectMsgTypes::MsgData> vectorMsgData;
    for(const auto& output: outputs)
    {
        std::vector<unsigned int> outputMsgTypes = output->getMessageTypes();

        for(const auto& outputMsgType: outputMsgTypes)
        {
            auto findIter = msgTypes.find(outputMsgType);
            if(msgTypes.end() == findIter)
            {
                Exceptions::OutputIncorrectMsgTypes::MsgData data;
                data.mOutputName = output->getName();
                data.mTypeId = outputMsgType;
                vectorMsgData.push_back(data);
            }
        }
    }
    if(0 < vectorMsgData.size())
    {
        throw Exceptions::OutputIncorrectMsgTypes(Exceptions::OutputIncorrectMsgTypes::constructWhatStr(vectorMsgData));
    }
}

ls::Logger::~Logger()
{

}

void ls::Logger::log(unsigned int type, const std::string& msg) const
{
    std::string dateTimeStr = mGetDateTimeAsString();

    auto findIter = mMapMsgTypes.find(type);
    if(mMapMsgTypes.end() != findIter)
    {
        for(const auto& output: mVectorOutputs)
        {
            output->write(type, findIter->second, msg, dateTimeStr);
        }
    }
    else
    {
        for(const auto& output: mVectorOutputs)
        {
            output->write(type, "", msg, dateTimeStr);
        }
    }
}

void ls::Logger::setGetDateTimeAsStringCallback(GetDateTimeAsStringCallback callback)
{
    mGetDateTimeAsString = callback;
}
