#include <iostream>

#include "data_structures/process.h"
#include "data_structures/queue.h"
#include "io/reader/process_file_reader.h"
#include "schedulers/fcfs.h"
#include "schedulers/rr.h"
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
    // Timestamp *timer = new Timestamp("FCFS");
    Timestamp *timer2 = new Timestamp("RR");

    try {
        Queue<Process *> *process_vector_to_queue =
            convert_process_vector_to_queue(processes);
        // FCFS *fcfs = new FCFS(timer, process_vector_to_queue);
        RR *rr = new RR(timer2, process_vector_to_queue);
        // fcfs->Simulate();
        rr->Simulate();
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}