#include "lsLogger.hpp"

#include <ctime>

#include "lsIOutput.hpp"

ls::Logger::Logger(std::map<unsigned int, std::string> msgTypes, std::vector<std::shared_ptr<IOutput>> outputs)
    : mMsgTypes(msgTypes)
    , mOutputs(outputs)
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
}

ls::Logger::~Logger()
{

}

void ls::Logger::log(unsigned int type, const std::string& msg) const
{
    std::string dateTimeStr = mGetDateTimeAsString();

    auto findIter = mMsgTypes.find(type);
    if(mMsgTypes.end() != findIter)
    {
        for(const auto& output: mOutputs)
        {
            output->write(type, findIter->second, msg, dateTimeStr);
        }
    }
    else
    {
        for(const auto& output: mOutputs)
        {
            output->write(type, "", msg, dateTimeStr);
        }
    }
}

void ls::Logger::setGetDateTimeAsStringCallback(GetDateTimeAsStringCallback callback)
{
    mGetDateTimeAsString = callback;
}
