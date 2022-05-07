#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include <lsLogger.hpp>
#include <lsConsoleOutput.hpp>

bool callbackInfoExecuted = false;
bool callbackDefauleExecuted = false;

/*
    First argument is the path to temp file where to write.
*/
int main(int argc, char** argv)
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

        output->setDefaultWriteCallback([](uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
        {
            callbackDefauleExecuted = true;
        });

        output->setWriteCallbackForMsgType(0, [](uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
        {
            callbackInfoExecuted = true;
        });

        outputs.push_back(output);
    }

    try
    {
        ls::Logger logger(msgTypes, outputs);
        logger.log(0, "InfoMessage1");
        logger.log(1, "ErrorMessage2");

        if(!callbackInfoExecuted)
        {
            std::cout << "Info callback not executed!" << std::endl;
            retVal = 1;
        }
        if(!callbackDefauleExecuted)
        {
            std::cout << "Default callback not executed!" << std::endl;
            retVal = 1;
        }
    }
    catch(std::exception& e)
    {
        retVal = 1;
    }

    return retVal;
}
