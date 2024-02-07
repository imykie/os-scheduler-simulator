#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../data_structures/process.h"
#include "../data_structures/queue.h"
#include "../io/writer/file_writer.h"
#include "../timestamp/timestamp.h"
#include "../timestamp/timestamp_observer.h"

class FCFS : public TimestampObserver {
   public:
    FCFS(Timestamp *timer, Queue<Process *> *processes);
    ~FCFS();
    void Simulate();
    bool IsProcessing();
    Process *GetCurrentProcess();

   private:
    Queue<Process *> *job_queue;
    Queue<Process *> *waiting_queue;
    Queue<Process *> *ready_queue;
    Queue<Process *> *terminated_queue;
    Timestamp *timer;
    Process *current_process;
    int process_count;

    void SetCurrentProcess(Process *process);
};