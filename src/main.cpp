#include <iostream>

#include "data_structures/process.h"
#include "data_structures/queue.h"
#include "io/reader/process_file_reader.h"

using namespace std;

int main() {
    vector<Process*> processes = ProcessFileReader::ReadFile("test.csv");

    for (auto process : processes) {
        cout << process->ToString() << endl;
    }

    return 0;
}