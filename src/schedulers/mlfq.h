#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../io/helper.h"
#include "../timestamp/timestamp_observer.h"
#include "scheduler.h"

class MLFQ : public Scheduler, TimestampObserver {
   public:
    MLFQ(Timestamp *timer, Queue<Process *> *processes, int time_quantum_level_1 = 2, int time_quantum_level_2 = 1);
    ~MLFQ();
    void Simulate() override;

   private:
    int time_quantum_level_1;
    int time_quantum_level_2;
    int process_previous_level;

   protected:
    Queue<Process *> *ready_queue_level_2;
    Queue<Process *> *ready_queue_level_3;
};