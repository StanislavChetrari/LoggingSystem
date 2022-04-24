#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include <lsLogger.hpp>

int main()
{
    int retVal = 0;

    std::map<uint32_t, std::string> msgTypes;
    std::vector<std::shared_ptr<ls::IOutput>> outputs;

    try
    {
        ls::Logger logger(msgTypes, outputs);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        retVal = 1;
    }

    return retVal;
}
