#include "file_writer.h"

bool FileWriter::FileExists(const std::string path) {
    std::ifstream file(path);
    return file.good();
}

void FileWriter::CreateFile(const std::string path) {
    if (FileWriter::FileExists(path)) throw std::invalid_argument(path + " already exist");

    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::invalid_argument("could not create file at: " + path);
    }
    file.close();
}

void FileWriter::AppendToFile(const std::string path, const std::string text) {
    std::ofstream file(path, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        throw std::invalid_argument("could not open/create file at: " + path);
    }
    file << text;
    file.close();
}

void FileWriter::WriteToFile(const std::string path, const std::vector<std::string> texts) {
    std::ofstream file(path, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        throw std::invalid_argument("could not open/create file at: " + path);
    }
    for (const std::string &text : texts) {
        file << text << std::endl;
    }
    file.close();
}