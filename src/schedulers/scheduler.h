#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../data_structures/process.h"
#include "../data_structures/queue.h"
#include "../io/writer/file_writer.h"
#include "../timestamp/timestamp.h"

class Scheduler {
   public:
    virtual void Simulate() = 0;
    virtual bool IsProcessing();
    virtual Process *GetCurrentProcess();

   protected:
    Queue<Process *> *job_queue;
    Queue<Process *> *waiting_queue;
    Queue<Process *> *ready_queue;
    Queue<Process *> *terminated_queue;
    Timestamp *timer;
    Process *current_process;
    int process_count;
    virtual void SetCurrentProcess(Process *process);
    void AnalyzeProcess(std::string filename);
};
