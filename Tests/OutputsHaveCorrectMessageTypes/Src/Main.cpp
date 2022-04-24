#include <iostream>

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

    // ==============================================================================================
    // Test case when everything is good. All message types in outputs are valid.
    // ==============================================================================================
    {
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
                std::cout << "Callback for message type 0" << std::endl;
            });

            output->setWriteCallbackForMsgType(1, [](uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
            {
                std::cout << "Callback for message type 1" << std::endl;
            });

            outputs.push_back(output);
        }

        try
        {
            ls::Logger logger(msgTypes, outputs);
        }
        catch(ls::Exceptions::OutputIncorrectMsgTypes& e)
        {
            std::cout << "Case when all message types are valid in outputs failed!" << std::endl;
            retVal = 1;
        }
    }

    // ==============================================================================================
    // Test case when there are invalid message types in outputs.
    // ==============================================================================================
    {
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
                std::cout << "Callback for message type 0" << std::endl;
            });

            output->setWriteCallbackForMsgType(5, [](uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
            {
                std::cout << "Callback for message type 5(Not valid type)" << std::endl;
            });

            outputs.push_back(output);
        }

        try
        {
            ls::Logger logger(msgTypes, outputs);

            std::cout << "Case when there are invalid message types in outputs failed!" << std::endl;
            retVal = 1;
        }
        catch(ls::Exceptions::OutputIncorrectMsgTypes& e)
        {

        }
    }

    return retVal;
}
