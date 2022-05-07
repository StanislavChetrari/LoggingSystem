#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include <lsLogger.hpp>
#include <lsTextFileOutput.hpp>

/*
    First argument is the path to temp file where to write.
*/
int main(int argc, char** argv)
{
    int retVal = 0;

    if(argc == 2)
    {
        std::string filePath(argv[1]);

        std::map<uint32_t, std::string> msgTypes;

        std::vector<std::shared_ptr<ls::IOutput>> outputs;
        {
            std::shared_ptr<ls::TextFileOutput> output = std::make_shared<ls::TextFileOutput>();
            output->setName("My text file output");

            if(!output->open(filePath, ls::TextFileOutput::FileOpenType::NewOrOverwrite))
            {
                std::cout << "Could not open file \"" << filePath << "\"." << std::endl;
                retVal = 1;
            }

            outputs.push_back(output);
        }

        try
        {
            ls::Logger logger(msgTypes, outputs);
        }
        catch(std::exception& e)
        {
            retVal = 1;
        }
    }
    else
    {
        std::cout << "Expected to have only 1 argument." << std::endl;
        retVal = 1;
    }

    return retVal;
}
