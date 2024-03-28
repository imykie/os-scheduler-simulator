#include "mlfq.h"

MLFQ::MLFQ(Timestamp *timer, Queue<Process *> *processes, int time_quantum_level_1, int time_quantum_level_2)
    : TimestampObserver(timer) {
    this->time_quantum_level_1 = time_quantum_level_1;
    this->time_quantum_level_2 = time_quantum_level_2;
    this->process_previous_level = 1;
    this->timer = timer;
    process_count = processes->Length();
    job_queue = processes->Copy();
    ready_queue = new Queue<Process *>;
    ready_queue_level_2 = new Queue<Process *>;
    ready_queue_level_3 = new Queue<Process *>;
    waiting_queue = new Queue<Process *>;
    terminated_queue = new Queue<Process *>;
    this->SetCurrentProcess(nullptr);
}

MLFQ::~MLFQ() {
    delete job_queue;
    job_queue = nullptr;
    delete ready_queue;
    ready_queue = nullptr;
    delete ready_queue_level_2;
    ready_queue_level_2 = nullptr;
    delete ready_queue_level_3;
    ready_queue_level_3 = nullptr;
    delete waiting_queue;
    waiting_queue = nullptr;
    delete terminated_queue;
    terminated_queue = nullptr;
    delete current_process;
    this->SetCurrentProcess(nullptr);
}

void MLFQ::Simulate() {
    Queue<Process *> *job_queue_copy = this->DeepCopy(job_queue);
    std::vector<std::string> out;
    out.push_back("***Multi-Level Feedback Queue (MLFQ) Scheduling Algorithm***\n");
    int execution_elapsed_time = 0;

    while (IsProcessing()) {
        const int current_time = static_cast<int>(timer->GetCurrentTime());
        out.push_back("[Time]: " + std::to_string(current_time) + " - " + std::to_string(current_time + 1));

        // handle new job
        if (!job_queue->IsEmpty() && job_queue->Peek()->GetArrivalTime() <= current_time) {
            ready_queue->Enqueue(job_queue->Dequeue());
            out.push_back("[Process ID]: " + std::to_string(ready_queue->Rear()->GetProcessID()) +
                          ", Moved from Job Queue to Ready Queue Level 1 [NEW -> READY]");
        }

        // handle ready queue level 1
        if (!ready_queue->IsEmpty() && current_process == nullptr) {
            this->SetCurrentProcess(ready_queue->Dequeue());
            process_previous_level = 1;
            execution_elapsed_time = 0;
            if (current_process->GetResponseTime() == -1) {
                current_process->SetResponseTime(current_time);
            }
            out.push_back("[Process ID]: " + std::to_string(current_process->GetProcessID()) +
                          ", Moved from Ready Queue Level 1 to Running State [READY -> "
                          "RUNNING]");
        }
        // handle ready queue level 2
        else if (!ready_queue_level_2->IsEmpty() && current_process == nullptr) {
            this->SetCurrentProcess(ready_queue_level_2->Dequeue());
            process_previous_level = 2;
            execution_elapsed_time = 0;
            if (current_process->GetResponseTime() == -1) {
                current_process->SetResponseTime(current_time);
            }
            out.push_back("[Process ID]: " + std::to_string(current_process->GetProcessID()) +
                          ", Moved from Ready Queue Level 2 to Running State [READY -> "
                          "RUNNING]");
        }
        // handle ready queue level 3
        else if (!ready_queue_level_3->IsEmpty() && current_process == nullptr) {
            this->SetCurrentProcess(ready_queue_level_3->Dequeue());
            process_previous_level = 3;
            execution_elapsed_time = 0;
            if (current_process->GetResponseTime() == -1) {
                current_process->SetResponseTime(current_time);
            }
            out.push_back("[Process ID]: " + std::to_string(current_process->GetProcessID()) +
                          ", Moved from Ready Queue Level 3 to Running State [READY -> "
                          "RUNNING]");
        }

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

        if (current_process != nullptr) {
            if (current_process->GetCPUBurstTime1() == 0) {
                if (current_process->GetIOBurstTime() == 0 && current_process->GetCPUBurstTime2() > 0) {
                    current_process->SetCPUBurstTime2(current_process->GetCPUBurstTime2() - 1);
                    execution_elapsed_time++;
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
                    } else if (process_previous_level == 1 && execution_elapsed_time == time_quantum_level_1) {
                        ready_queue_level_2->Enqueue(current_process);
                        this->SetCurrentProcess(nullptr);
                        out.push_back("[Process ID]: " + std::to_string(ready_queue_level_2->Rear()->GetProcessID()) +
                                      ", Time Quantum was finished and moved "
                                      "from Running "
                                      "State to Ready Queue Level 2 [RUNNING - READY]");
                    } else if (process_previous_level == 2 && execution_elapsed_time == time_quantum_level_2) {
                        ready_queue_level_3->Enqueue(current_process);
                        this->SetCurrentProcess(nullptr);
                        out.push_back("[Process ID]: " + std::to_string(ready_queue_level_3->Rear()->GetProcessID()) +
                                      ", Time Quantum was finished and moved "
                                      "from Running "
                                      "State to Ready Queue Level 3 [RUNNING - READY]");
                    }
                }
            } else {
                current_process->SetCPUBurstTime1(current_process->GetCPUBurstTime1() - 1);
                execution_elapsed_time++;
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
                } else if (process_previous_level == 1 && execution_elapsed_time == time_quantum_level_1) {
                    ready_queue_level_2->Enqueue(current_process);
                    this->SetCurrentProcess(nullptr);
                    out.push_back("[Process ID]: " + std::to_string(ready_queue_level_2->Rear()->GetProcessID()) +
                                  ", Time Quantum was finished and moved "
                                  "from Running State to Ready Queue Level 2 [RUNNING - READY]");
                } else if (process_previous_level == 2 && execution_elapsed_time == time_quantum_level_2) {
                    ready_queue_level_3->Enqueue(current_process);
                    this->SetCurrentProcess(nullptr);
                    out.push_back("[Process ID]: " + std::to_string(ready_queue_level_3->Rear()->GetProcessID()) +
                                  ", Time Quantum was finished and moved "
                                  "from Running State to Ready Queue Level 3 [RUNNING - READY]");
                }
            }
        }
        timer->IncreaseTime(1);
    }
    FileWriter::ClearFile("MLFQ.log");
    FileWriter::WriteToFile("MLFQ.log", out);
    AnalyzeProcess("MLFQ");
    AnalyzeAlgorithm("MLFQ", job_queue_copy);
}