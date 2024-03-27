#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace FileWriter {
    bool FileExists(const std::string path);
    void CreateFile(const std::string path);
    void AppendToFile(const std::string path, const std::string text);
    void WriteToFile(const std::string path, const std::vector<std::string> texts);
    void ClearFile(const std::string path);
    void ClearFiles(const std::vector<std::string> paths);

}  // namespace FileWriter