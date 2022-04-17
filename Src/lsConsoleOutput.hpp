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
            using WriteMessageCallback = std::function<void(uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)>;

        public:
            ConsoleOutput();
            ~ConsoleOutput();

            void write(uint32_t type, const std::string& typeName, const std::string &msg, const std::string& dateTimeStr) override;

            void setName(const std::string &name) override;
            std::string getName() const override;

            std::vector<uint32_t> getMessageTypes() override;

            void setDefaultWriteCallback(const WriteMessageCallback& callback);
            void setWriteCallbackForMsgType(uint32_t msgType, const WriteMessageCallback& callback);

        private:
            std::map<uint32_t, WriteMessageCallback> mMapMsgTypeToWriteCallback;
            WriteMessageCallback mDefaultWriteCallback;

            std::string mName;
    };
}

#endif /* #ifndef _CONSOLE_OUTPUT_HPP_ */
