#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../../data_structures/process.h"
#include "../helper.h"

namespace ProcessFileReader {
    // const used to seperate line inputs in txt file
    const std::string DELIM = ",";
    const int COLS_NUM = 5;
    const std::string COL1 = "process_id";
    const std::string COL2 = "arrival_time";
    const std::string COL3 = "cpu_time1";
    const std::string COL4 = "cpu_time2";
    const std::string COL5 = "io_time";
    const std::vector<std::string> TITLES{COL1, COL2, COL3, COL4, COL5};

    std::vector<Process *> ReadFile(std::string path);
}  // namespace ProcessFileReader