#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>

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
        std::string fileName = std::string(argv[1]);

        std::map<uint32_t, std::string> msgTypes =
        {
            {0, "INFO"},
            {1, "ERROR"}
        };

        std::vector<std::shared_ptr<ls::IOutput>> outputs;
        {
            std::shared_ptr<ls::TextFileOutput> output = std::make_shared<ls::TextFileOutput>();
            std::string outputName("My text file output");
            output->setName(outputName);

            output->setWriteCallbackForMsgType(0, [](std::ofstream& fileOut, uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
            {

            });
            output->setWriteCallbackForMsgType(1, [](std::ofstream& fileOut, uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)
            {

            });

            if(!output->open(fileName, ls::TextFileOutput::FileOpenType::Append))
            {
                retVal = 1;
            }
            else
            {
                int failed = 0;

                failed |= (output->getName() != outputName);
                if(failed)
                {
                    std::cout << "getName() incorrect data." << std::endl;
                }

                if(!failed)
                {
                    failed |= (output->getFilePath() != fileName);
                    if(failed)
                    {
                        std::cout << "getFilePath() incorrect data." << std::endl;
                    }
                }

                if(!failed)
                {
                    failed |= (output->getFileOpenType() != ls::TextFileOutput::FileOpenType::Append);
                    if(failed)
                    {
                        std::cout << "getFileOpenType() incorrect data." << std::endl;
                    }
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
