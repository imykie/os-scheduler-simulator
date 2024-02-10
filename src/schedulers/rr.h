#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../timestamp/timestamp_observer.h"
#include "scheduler.h"

class RR : public Scheduler, TimestampObserver {
   public:
    RR(Timestamp *timer, Queue<Process *> *processes, int time_quantum = 1);
    ~RR();
    void Simulate();
    bool IsProcessing();
    Process *GetCurrentProcess();

   private:
    void SetCurrentProcess(Process *process);
    int time_quantum;
};