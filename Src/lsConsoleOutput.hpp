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
            ConsoleOutput();
            ~ConsoleOutput();

            void write(unsigned int type, const std::string& typeName, const std::string &msg, const std::string& dateTimeStr) override;

            void setName(const std::string &name) override;
            std::string getName() const override;

        private:
            using WriteMessageCallback = std::function<void(unsigned int type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)>;

            std::map<unsigned int, WriteMessageCallback> mMapMsgTypeToWriteCallback;
            WriteMessageCallback mDefaultWriteCallback;

            std::string mName;
    };
}

#endif /* #ifndef _CONSOLE_OUTPUT_HPP_ */
