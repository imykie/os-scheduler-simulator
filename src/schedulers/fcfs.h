#pragma once

#include <iostream>

#include "../data_structures/process.h"
#include "../data_structures/queue.h"
#include "../timestamp/timestamp.h"
#include "../timestamp/timestamp_observer.h"

class FCFS : public TimeStampObserver {
   public:
    FCFS(TimeStamp *timer, Queue<Process *> *processes);
    void Simulate();
    bool IsProcessing();
    Process *GetCurrentProcess();

   private:
    Queue<Process *> *job_queue;
    Queue<Process *> *waiting_queue;
    Queue<Process *> *ready_queue;
    Queue<Process *> *terminated_queue;
    TimeStamp *timer;
    Process *current_process;
    int process_count;

    void SetCurrentProcess(Process *process);
};