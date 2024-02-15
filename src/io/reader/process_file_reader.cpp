#include "process_file_reader.h"

std::vector<Process *> ProcessFileReader::ReadFile(const std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("could not open file at path: " + path);
    }

    std::string line;
    std::vector<Process *> processes;
    int line_count = 1;
    bool validate_titles = false;

    while (getline(file, line)) {
        if (!validate_titles) {
            std::vector<std::string> csv_titles = Helper::Split(line, DELIM);

            if (csv_titles.size() == COLS_NUM) {
                for (size_t i = 0; i < csv_titles.size(); ++i) {
                    if (csv_titles[i] != TITLES[i]) {
                        throw std::invalid_argument("invalid column" + std::to_string(i + 1) + "title '" +
                                                    csv_titles[i] + "' should be '" + TITLES[i] + "'");
                    };
                }
            } else {
                throw std::invalid_argument("invalid number columns in: " + path);
            }

            validate_titles = true;
            continue;
        }

        std::vector<std::string> columns = Helper::Split(line, DELIM);
        Process *process = new Process();

        if (columns.size() == COLS_NUM) {
            process->SetProcessID(std::stoul(columns[0]));
            process->SetArrivalTime(std::stoul(columns[1]));
            process->SetCPUBurstTime1(std::stoul(columns[2]));
            process->SetCPUBurstTime2(std::stoul(columns[3]));
            process->SetIOBurstTime(std::stoul(columns[4]));
        } else {
            file.close();
            throw std::invalid_argument("input format invalid at line " + std::to_string(line_count) +
                                        " of file on path: " + path);
        }
        processes.push_back(process);
        line_count++;
    }

    file.close();
    return processes;
}