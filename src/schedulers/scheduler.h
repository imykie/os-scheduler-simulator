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
    Queue<Process *> *DeepCopy(Queue<Process *> *queue);

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
    void AnalyzeAlgorithm(std::string filename, Queue<Process *> *job_queue_copy);

   private:
    int GetCPUExecutionTime(Queue<Process *> *job_queue_copy);
    int GetFinishTime();
    int GetCPUIdleTime(Queue<Process *> *job_queue_copy);
    float GetCPUUtilizationPercentage(Queue<Process *> *job_queue_copy);
    float GetThroughput();
    float GetAverageTurnaroundTime();
    float GetAverageWaitTime();
    float GetAverageResponseTime();
};
