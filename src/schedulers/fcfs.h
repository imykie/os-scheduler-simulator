#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../timestamp/timestamp_observer.h"
#include "scheduler.h"

class FCFS : public Scheduler, TimestampObserver {
   public:
    FCFS(Timestamp *timer, Queue<Process *> *processes);
    ~FCFS();
    void Simulate() override;
};