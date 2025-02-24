#include "core/system/file.h"
#include "core/system/path.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace Runa::System {
    std::vector<uint8_t> LoadFileToBuffer(const std::string &filepath) {
        std::fstream file(System::NativeSeparator(filepath), std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error trying to open file: " << filepath << std::endl;
            return std::vector<uint8_t>();
        }

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<uint8_t> buffer(size);

        if (!file.read(reinterpret_cast<char *>(buffer.data()), size)) {
            std::cerr << "Error trying to read file: " << filepath << std::endl;
            buffer.clear();
        }

        file.close();

        return buffer;
    }

    std::string LoadFileToString(const std::string &filepath) {
        std::ifstream file(System::NativeSeparator(filepath), std::ios::binary);

        if (!file.is_open()) {
            std::cerr << "Error trying to open file: " << filepath << std::endl;
            return "";
        }

        std::stringstream stream_buffer;
        stream_buffer << file.rdbuf();

        file.close();

        return stream_buffer.str();
    }

    bool FileExists(const std::string &filepath) {
        return std::filesystem::exists(filepath);
    }
}
