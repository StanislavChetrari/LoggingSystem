#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <exception>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <loggingsystem_export.h>

namespace ls
{
    class IOutput;

    namespace Exceptions
    {
        class LOGGINGSYSTEM_EXPORT OutputIncorrectMsgTypes : public std::exception
        {
            public:
                struct MsgData
                {
                    unsigned int mTypeId;
                    std::string mOutputName;
                };

            public:
                OutputIncorrectMsgTypes(const std::string& whatStr);

                const char* what() const noexcept override;

                static std::string constructWhatStr(const std::vector<MsgData>& vectorMsgData);

            private:
                const std::string mWhatString;
        };
    }

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
            std::map<unsigned int, std::string> mMapMsgTypes;
            std::vector<std::shared_ptr<IOutput>> mVectorOutputs;
            std::function<GetDateTimeAsStringCallback> mGetDateTimeAsString;
    };
}

#endif /* #ifndef _LOGGER_HPP_ */
