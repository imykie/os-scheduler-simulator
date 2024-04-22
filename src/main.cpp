#include <iostream>

#include "data_structures/process.h"
#include "data_structures/queue.h"
#include "io/reader/process_file_reader.h"
#include "schedulers/fcfs.h"
#include "schedulers/mlfq.h"
#include "schedulers/rr.h"
#include "schedulers/sjf.h"
#include "timestamp/timestamp.h"
#include "timestamp/timestamp_observer.h"

using namespace std;

Queue<Process *> *ConvertProcessVectorToQueue(vector<Process *> processes) {
    Queue<Process *> *queue = new Queue<Process *>();

    for (size_t i = 0; i < processes.size(); ++i) {
        Process *process =
            new Process(processes[i]->GetProcessID(), processes[i]->GetArrivalTime(), processes[i]->GetCPUBurstTime1(),
                        processes[i]->GetCPUBurstTime2(), processes[i]->GetIOBurstTime());
        queue->Enqueue(process);
    }

    return queue;
}

int main(int argc, char *argv[]) {
    vector<Process *> processes = ProcessFileReader::ReadFile(argv[1]);
    Timestamp timer("FCFS");
    Timestamp timer2("RR");
    Timestamp timer3("SJF");
    Timestamp timer4("MLFQ");

    try {
        FCFS fcfs(&timer, ConvertProcessVectorToQueue(processes));
        RR rr(&timer2, ConvertProcessVectorToQueue(processes));
        SJF sjf(&timer3, ConvertProcessVectorToQueue(processes));
        MLFQ mlfq(&timer4, ConvertProcessVectorToQueue(processes));
        fcfs.Simulate();
        rr.Simulate();
        sjf.Simulate();
        mlfq.Simulate();
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}