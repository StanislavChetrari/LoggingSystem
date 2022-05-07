#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

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
        output->setName("My console output");

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
