#ifndef _TEXT_FILE_OUTPUT_HPP_
#define _TEXT_FILE_OUTPUT_HPP_

#include "lsIOutput.hpp"

#include <cstdint>
#include <functional>
#include <fstream>
#include <string>
#include <map>

#include <loggingsystem_export.h>

namespace ls
{
    class LOGGINGSYSTEM_EXPORT TextFileOutput : public IOutput
    {
        public:
            using WriteMessageCallback = std::function<void(std::ofstream& fileOut, uint32_t type, const std::string& typeName, const std::string& msg, const std::string& dateTimeStr)>;

            enum class FileOpenType { NewOrOverwrite, Append };

        public:
            TextFileOutput();
            ~TextFileOutput();

            void write(uint32_t type, const std::string& typeName, const std::string &msg, const std::string& dateTimeStr) override;

            void setName(const std::string& name) override;
            std::string getName() const override;

            std::vector<uint32_t> getMessageTypes() override;

            bool open(const std::string& filePath, FileOpenType fileOpenType);
            void close();

            std::string getFilePath() const;
            FileOpenType getFileOpenType() const;

            void setDefaultWriteCallback(const WriteMessageCallback& callback);
            void setWriteCallbackForMsgType(uint32_t msgType, const WriteMessageCallback& callback);

        private:
            std::map<uint32_t, WriteMessageCallback> mMapMsgTypeToWriteCallback;
            WriteMessageCallback mDefaultWriteCallback;

            std::string mName;
            std::string mFilePath;
            FileOpenType mFileOpenType;
            std::ofstream mFile;
    };
}

#endif /* #ifndef _TEXT_FILE_OUTPUT_HPP_ */
