#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include <lsLogger.hpp>
#include <lsConsoleOutput.hpp>

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
        std::string outputName("My console output");
        output->setName(outputName);

        output->setWriteCallbackForMsgType(0, [](uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
        {

        });
        output->setWriteCallbackForMsgType(1, [](uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
        {

        });

        int failed = 0;

        failed |= (output->getName() != outputName);
        if(failed)
        {
            std::cout << "getName() incorrect data." << std::endl;
        }

        if(!failed)
        {
            std::vector<uint32_t> outputMsgTypes = output->getMessageTypes();
            if(outputMsgTypes.size() == 2)
            {
                int i = 0;
                for(auto iter = msgTypes.begin(); iter != msgTypes.end(); ++iter, ++i)
                {
                    if(iter->first != outputMsgTypes[i])
                    {
                        failed = 1;
                        break;
                    }
                }
            }
            else
            {
                failed = 1;
            }
            if(failed)
            {
                std::cout << "getMessageTypes() incorrect data." << std::endl;
            }
        }

        retVal = failed;
    }

    try
    {
        ls::Logger logger(msgTypes, outputs);
    }
    catch(std::exception& e)
    {
        retVal = 1;
    }

    return retVal;
}
