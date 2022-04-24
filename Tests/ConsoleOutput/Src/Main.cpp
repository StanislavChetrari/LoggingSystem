#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include <lsLogger.hpp>
#include <lsConsoleOutput.hpp>

int main()
{
    int retVal = 0;

    std::map<uint32_t, std::string> msgTypes =
    {
        {0, "INFO"},
        {1, "ERROR"}
    };

    std::vector<std::shared_ptr<ls::IOutput>> outputs;
    {
        std::shared_ptr<ls::ConsoleOutput> output = std::make_shared<ls::ConsoleOutput>();
        output->setName("My console output");

        output->setWriteCallbackForMsgType(0, [](uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
        {
            std::cout << typeName << " : " << msg << std::endl;
        });

        outputs.push_back(output);
    }

    try
    {
        ls::Logger logger(msgTypes, outputs);

        logger.log(0, "InfoMessage1");
        logger.log(1, "ErrorMessage2");
    }
    catch(std::exception& e)
    {
        retVal = 1;
    }

    return retVal;
}
