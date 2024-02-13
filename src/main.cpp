#include <iostream>

#include "data_structures/process.h"
#include "data_structures/queue.h"
#include "io/reader/process_file_reader.h"
#include "schedulers/fcfs.h"
#include "schedulers/rr.h"
#include "schedulers/sjf.h"
#include "timestamp/timestamp.h"
#include "timestamp/timestamp_observer.h"

using namespace std;

Queue<Process *> *convert_process_vector_to_queue(vector<Process *> processes) {
    Queue<Process *> *queue = new Queue<Process *>();

    for (size_t i = 0; i < processes.size(); ++i) {
        Process *process =
            new Process(processes[i]->GetProcessID(), processes[i]->GetArrivalTime(), processes[i]->GetCPUBurstTime1(),
                        processes[i]->GetCPUBurstTime2(), processes[i]->GetIOBurstTime());
        queue->Enqueue(process);
    }

    return queue;
}

int main() {
    vector<Process *> processes = ProcessFileReader::ReadFile("test.csv");
    Timestamp *timer = new Timestamp("FCFS");
    Timestamp *timer2 = new Timestamp("RR");
    Timestamp *timer3 = new Timestamp("SJF");

    try {
        FCFS *fcfs = new FCFS(timer, convert_process_vector_to_queue(processes));
        RR *rr = new RR(timer2, convert_process_vector_to_queue(processes));
        SJF *sjf = new SJF(timer3, convert_process_vector_to_queue(processes));
        fcfs->Simulate();
        rr->Simulate();
        sjf->Simulate();
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}