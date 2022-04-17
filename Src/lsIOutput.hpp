#ifndef _I_OUTPUT_HPP_
#define _I_OUTPUT_HPP_

#include <string>
#include <vector>

namespace ls
{
    class IOutput
    {
        public:
            virtual void write(uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr) = 0;

            virtual void setName(const std::string& name) = 0;
            virtual std::string getName() const = 0;

            virtual std::vector<uint32_t> getMessageTypes() = 0;
    };
}

#endif /* #ifndef _I_OUTPUT_HPP_ */
