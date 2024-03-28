#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../data_structures/queue_utils.h"
#include "../timestamp/timestamp_observer.h"
#include "scheduler.h"

class SJF : public Scheduler, TimestampObserver {
   public:
    SJF(Timestamp *timer, Queue<Process *> *processes);
    ~SJF();
    void Simulate() override;

   private:
    static bool SortFunction(Process *p1, Process *p2);
    Queue<Process *> *SortQueue(Queue<Process *> *queue);
};