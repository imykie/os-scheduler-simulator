#include <iostream>

#include "data_structures/process.h"
#include "data_structures/queue.h"
#include "io/reader/process_file_reader.h"
#include "timestamp/timestamp.h"
#include "timestamp/timestamp_observer.h"

using namespace std;

int main() {
    vector<Process *> processes = ProcessFileReader::ReadFile("test.csv");
    TimeStamp *timer = new TimeStamp("Timer1");
    TimeStampObserver *observer1 = new TimeStampObserver(timer);
    TimeStampObserver *observer2 = new TimeStampObserver(timer);

    for (auto process : processes) {
        cout << process->ToString() << endl;
    }

    for (float i = 1; i < 10; ++i) {
        timer->IncreaseTime(i);
    }

    return 0;
}