#ifndef _CONSOLE_OUTPUT_HPP_
#define _CONSOLE_OUTPUT_HPP_

#include "lsIOutput.hpp"

#include <map>
#include <string>
#include <functional>

#include <loggingsystem_export.h>

namespace ls
{
    class LOGGINGSYSTEM_EXPORT ConsoleOutput : public IOutput
    {
        public:
            using WriteMessageCallback = std::function<void(unsigned int type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)>;

        public:
            ConsoleOutput();
            ~ConsoleOutput();

            void write(unsigned int type, const std::string& typeName, const std::string &msg, const std::string& dateTimeStr) override;

            void setName(const std::string &name) override;
            std::string getName() const override;

            std::vector<unsigned int> getMessageTypes() override;

            void setDefaultWriteCallback(const WriteMessageCallback& callback);
            void setWriteCallbackForMsgType(unsigned int msgType, const WriteMessageCallback& callback);

        private:
            std::map<unsigned int, WriteMessageCallback> mMapMsgTypeToWriteCallback;
            WriteMessageCallback mDefaultWriteCallback;

            std::string mName;
    };
}

#endif /* #ifndef _CONSOLE_OUTPUT_HPP_ */
