#ifndef _I_OUTPUT_HPP_
#define _I_OUTPUT_HPP_

#include <string>

namespace ls
{
    class IOutput
    {
        public:
            virtual void write(unsigned int type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr) = 0;

            virtual void setName(const std::string& name) = 0;
            virtual std::string getName() const = 0;
    };
}

#endif /* #ifndef _I_OUTPUT_HPP_ */
