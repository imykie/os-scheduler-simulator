#include <iostream>

#include "data_structures/process.h"
#include "data_structures/queue.h"
#include "io/reader/process_file_reader.h"
#include "schedulers/fcfs.h"
#include "timestamp/timestamp.h"
#include "timestamp/timestamp_observer.h"

using namespace std;

Queue<Process *> *convert_process_vector_to_queue(vector<Process *> processes) {
    Queue<Process *> *queue = new Queue<Process *>();

    for (size_t i = 0; i < processes.size(); ++i) {
        Process *process = new Process(
            processes[i]->GetProcessID(), processes[i]->GetArrivalTime(),
            processes[i]->GetCPUBurstTime1(), processes[i]->GetCPUBurstTime2(),
            processes[i]->GetIOBurstTime());
        queue->Enqueue(process);
    }

    return queue;
}

int main() {
    vector<Process *> processes = ProcessFileReader::ReadFile("test.csv");
    TimeStamp *timer = new TimeStamp("Timer");
    // TimeStampObserver *observer1 = new TimeStampObserver(timer);
    FCFS *fcfs = new FCFS(timer, convert_process_vector_to_queue(processes));
    fcfs->Simulate();

    return 0;
}