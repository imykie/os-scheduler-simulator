#include "fcfs.h"

FCFS::FCFS(Timestamp *timer, Queue<Process *> *processes) : TimestampObserver(timer) {
    this->timer = timer;
    process_count = processes->Length();
    job_queue = processes->Copy();
    ready_queue = new Queue<Process *>;
    waiting_queue = new Queue<Process *>;
    terminated_queue = new Queue<Process *>;
    this->SetCurrentProcess(nullptr);
}

// clean up pointers in destructor
FCFS::~FCFS() {
    delete job_queue;
    job_queue = nullptr;
    delete ready_queue;
    ready_queue = nullptr;
    delete waiting_queue;
    waiting_queue = nullptr;
    delete terminated_queue;
    terminated_queue = nullptr;
    delete current_process;
    this->SetCurrentProcess(nullptr);
}

void FCFS::Simulate() {
    std::vector<std::string> out;
    out.push_back("***First Come First Serve (FCFS) Scheduling Algorithm***\n");

    while (terminated_queue->Length() < process_count) {
        const int current_time = static_cast<int>(timer->GetCurrentTime());
        out.push_back("[Time]: " + std::to_string(current_time) + " - " + std::to_string(current_time + 1));

        // handle job queue
        if (!job_queue->IsEmpty() && job_queue->Peek()->GetArrivalTime() <= current_time) {
            ready_queue->Enqueue(job_queue->Dequeue());
            out.push_back("[Process ID]: " + std::to_string(ready_queue->Rear()->GetProcessID()) +
                          ", Moved from Job Queue to Ready Queue [NEW -> READY]");
        }

        // handle ready queue
        if (!ready_queue->IsEmpty() && current_process == nullptr) {
            this->SetCurrentProcess(ready_queue->Dequeue());
            if (current_process->GetResponseTime() == -1) {
                current_process->SetResponseTime(current_time);
            }
            out.push_back("[Process ID]: " + std::to_string(current_process->GetProcessID()) +
                          ", Moved from Ready Queue to Running State [READY -> "
                          "RUNNING]");
        }

        // handle waiting queue
        if (!waiting_queue->IsEmpty()) {
            waiting_queue->Peek()->SetIOBurstTime(waiting_queue->Peek()->GetIOBurstTime() - 1);
            out.push_back("[Process ID]: " + std::to_string(waiting_queue->Peek()->GetProcessID()) +
                          ", Waited for IO resources for 1 second, [Remaining "
                          "IO Burst Time]: " +
                          std::to_string(waiting_queue->Peek()->GetIOBurstTime()));

            if (waiting_queue->Peek()->GetIOBurstTime() == 0) {
                ready_queue->Enqueue(waiting_queue->Dequeue());
                out.push_back("[Process ID]: " + std::to_string(ready_queue->Rear()->GetProcessID()) +
                              ", IO waiting time finished, Moved from Waiting "
                              "Queue to Ready Queue [WAITING -> READY]");
            }
        }

        // handle current process
        if (current_process != nullptr) {
            if (current_process->GetCPUBurstTime1() == 0) {
                if (current_process->GetIOBurstTime() == 0 && current_process->GetCPUBurstTime2() != 0) {
                    current_process->SetCPUBurstTime2(current_process->GetCPUBurstTime2() - 1);
                    out.push_back("[Process ID]: " + std::to_string(current_process->GetProcessID()) +
                                  ", Second CPU Burst Time was executed for 1 second, "
                                  "[Remaining Second CPU Burst Time]: " +
                                  std::to_string(current_process->GetCPUBurstTime2()));
                    if (current_process->GetCPUBurstTime2() == 0) {
                        terminated_queue->Enqueue(current_process);
                        current_process->SetTerminationTime(current_time + 1);
                        current_process->SetTurnAroundTime(current_process->GetTerminationTime() -
                                                           current_process->GetArrivalTime());
                        current_process->SetWaitTime(current_process->GetTurnAroundTime() -
                                                     (current_process->GetCPUBurstTime1() +
                                                      current_process->GetCPUBurstTime2() +
                                                      current_process->GetIOBurstTime()));
                        this->SetCurrentProcess(nullptr);
                        out.push_back("[Process ID]: " + std::to_string(terminated_queue->Rear()->GetProcessID()) +
                                      ", was terminated [RUNNING - TERMINATED]");
                    }
                }
            } else {
                current_process->SetCPUBurstTime1(current_process->GetCPUBurstTime1() - 1);
                out.push_back("[Process ID]: " + std::to_string(current_process->GetProcessID()) +
                              ", First CPU Burst Time was executed for 1 second, "
                              "[Remaining First CPU Burst Time]: " +
                              std::to_string(current_process->GetCPUBurstTime1()));
                if (current_process->GetCPUBurstTime1() == 0 && current_process->GetIOBurstTime() != 0) {
                    waiting_queue->Enqueue(current_process);
                    this->SetCurrentProcess(nullptr);
                    out.push_back("[Process ID]: " + std::to_string(waiting_queue->Rear()->GetProcessID()) +
                                  ", Moved from Running State to Waiting Queue to "
                                  "execute IO burst time [RUNNING -> WAITING]");
                }
            }
        }
        timer->IncreaseTime(1);
    }
    FileWriter::WriteToFile("FCFS.log", out);
}
