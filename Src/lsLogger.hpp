#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>

#include <loggingsystem_export.h>

namespace ls
{
    class IOutput;

    class LOGGINGSYSTEM_EXPORT Logger
    {
        public:
            using GetDateTimeAsStringCallback = std::string();

        public:
            Logger(std::map<unsigned int, std::string> msgTypes, std::vector<std::shared_ptr<IOutput>> outputs);
            ~Logger();

            void log(unsigned int msgType, const std::string& msg) const;

            void setGetDateTimeAsStringCallback(GetDateTimeAsStringCallback callback);

        private:
            std::map<unsigned int, std::string> mMsgTypes;
            std::vector<std::shared_ptr<IOutput>> mOutputs;
            std::function<GetDateTimeAsStringCallback> mGetDateTimeAsString;
    };
}

#endif /* #ifndef _LOGGER_HPP_ */
