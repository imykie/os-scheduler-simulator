#include "fcfs.h"

FCFS::FCFS(Timestamp *timer, Queue<Process *> *processes)
    : TimestampObserver(timer) {
    this->timer = timer;
    process_count = processes->Length();
    job_queue = processes->Copy();
    ready_queue = new Queue<Process *>;
    waiting_queue = new Queue<Process *>;
    terminated_queue = new Queue<Process *>;
    current_process = nullptr;
}

void FCFS::Simulate() {
    while (terminated_queue->Length() < process_count) {
        // handle job queue
        std::cout << "[Time]: " << timer->GetCurrentTime() << " - "
                  << timer->GetCurrentTime() + 1 << std::endl;
        if (!job_queue->IsEmpty() &&
            job_queue->Peek()->GetArrivalTime() <= timer->GetCurrentTime()) {
            ready_queue->Enqueue(job_queue->Dequeue());
            std::cout << "[Process ID]: " << ready_queue->Rear()->GetProcessID()
                      << ", Moved from Job Queue to Ready Queue [NEW -> READY]"
                      << std::endl;
        }

        // handle ready queue
        if (!ready_queue->IsEmpty() && current_process == nullptr) {
            SetCurrentProcess(ready_queue->Dequeue());
            if (current_process->GetResponseTime() == -1) {
                current_process->SetResponseTime(timer->GetCurrentTime());
            }
            std::cout << "[Process ID]: " << current_process->GetProcessID()
                      << ", Moved from Ready Queue to Running State [READY -> "
                         "RUNNING]"
                      << std::endl;
        }

        // handle waiting queue
        if (!waiting_queue->IsEmpty()) {
            waiting_queue->Peek()->SetIOBurstTime(
                waiting_queue->Peek()->GetIOBurstTime() - 1);
            std::cout << "[Process ID]: "
                      << waiting_queue->Peek()->GetProcessID()
                      << ", Waited for IO resources for 1 second, [Remaining "
                         "IOBurstTime]: "
                      << waiting_queue->Peek()->GetIOBurstTime() << std::endl;

            if (waiting_queue->Peek()->GetIOBurstTime() == 0) {
                ready_queue->Enqueue(waiting_queue->Dequeue());
                std::cout << "[Process ID]: "
                          << ready_queue->Rear()->GetProcessID()
                          << ", IO waiting time finished, Moved from Waiting "
                             "Queue to Ready Queue [WAITING -> READY]"
                          << std::endl;
            }
        }

        // handle current process
        if (current_process != nullptr) {
            if (current_process->GetCPUBurstTime1() == 0) {
                if (current_process->GetIOBurstTime() == 0 &&
                    current_process->GetCPUBurstTime2() != 0) {
                    current_process->SetCPUBurstTime2(
                        current_process->GetCPUBurstTime2() - 1);
                    std::cout
                        << "[Process ID]: " << current_process->GetProcessID()
                        << ", Second CPUBurstTime was executed for 1 second, "
                           "[Reamining CPUBurstTime 2]: "
                        << current_process->GetCPUBurstTime2() << std::endl;
                    if (current_process->GetCPUBurstTime2() == 0) {
                        terminated_queue->Enqueue(current_process);
                        current_process->SetTerminationTime(
                            timer->GetCurrentTime() + 1);
                        current_process->SetTurnAroundTime(
                            current_process->GetTerminationTime() -
                            current_process->GetArrivalTime());
                        current_process->SetWaitTime(
                            current_process->GetTurnAroundTime() -
                            (current_process->GetCPUBurstTime1() +
                             current_process->GetCPUBurstTime2() +
                             current_process->GetIOBurstTime()));
                        current_process = nullptr;
                        std::cout << "[Process ID]: "
                                  << terminated_queue->Rear()->GetProcessID()
                                  << ", was terminated [RUNNING - TERMINATED]"
                                  << std::endl;
                    }
                }
            } else {
                current_process->SetCPUBurstTime1(
                    current_process->GetCPUBurstTime1() - 1);
                std::cout << "[Process ID]: " << current_process->GetProcessID()
                          << ", First CPUBurstTime was executed for 1 second, "
                             "[Reamining CPUBurstTime 1]: "
                          << current_process->GetCPUBurstTime1() << std::endl;
                if (current_process->GetCPUBurstTime1() == 0 &&
                    current_process->GetIOBurstTime() != 0) {
                    waiting_queue->Enqueue(current_process);
                    current_process = nullptr;
                    std::cout
                        << "[Process ID]: "
                        << waiting_queue->Rear()->GetProcessID()
                        << ", Moved from Running State to Waiting Queue to "
                           "execute IO burst time [RUNNING -> WAITING]"
                        << std::endl;
                }
            }
        }

        timer->IncreaseTime(1);
    }
}

bool FCFS::IsProcessing() { return terminated_queue->Length() < process_count; }

Process *FCFS::GetCurrentProcess() { return current_process; };

void FCFS::SetCurrentProcess(Process *process) { current_process = process; };