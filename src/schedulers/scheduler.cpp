#include "scheduler.h"

#include <iomanip>

bool Scheduler::IsProcessing() { return terminated_queue->Length() < process_count; }

Process *Scheduler::GetCurrentProcess() { return current_process; };

void Scheduler::SetCurrentProcess(Process *process) { current_process = process; };

Queue<Process *> *Scheduler::DeepCopy(Queue<Process *> *queue) {
    Queue<Process *> *queue_copy = new Queue<Process *>();
    const size_t N = queue->Length();

    for (size_t _ = 0; _ < N; ++_) {
        Process *process = queue->Dequeue();
        Process *new_process =
            new Process(process->GetProcessID(), process->GetArrivalTime(), process->GetCPUBurstTime1(),
                        process->GetCPUBurstTime2(), process->GetIOBurstTime());
        queue_copy->Enqueue(new_process);
        queue->Enqueue(process);
    }

    return queue_copy;
}

void Scheduler::AnalyzeProcess(std::string filename) {
    const size_t N = terminated_queue->Length();
    std::stringstream ss;

    ss << "***" << filename << " Process Analysis***\n" << std::endl;
    ss << std::left << std::setw(14) << "Process ID" << std::setw(16) << "Arrival Time" << std::setw(20)
       << "Termination Time" << std::setw(17) << "Response Time" << std::setw(19) << "Turnaround Time" << std::setw(16)
       << "Waiting Time" << std::endl;

    for (size_t _ = 0; _ < N; ++_) {
        Process *process = terminated_queue->Dequeue();
        ss << std::left << std::setw(14) << process->GetProcessID() << std::setw(16) << process->GetArrivalTime()
           << std::setw(20) << process->GetTerminationTime() << std::setw(17) << process->GetResponseTime()
           << std::setw(19) << process->GetTurnAroundTime() << std::setw(16) << process->GetWaitTime() << std::endl;
        terminated_queue->Enqueue(process);
    }

    filename = filename + "-ProcessAnalysis.log";
    FileWriter::ClearFile(filename);
    FileWriter::AppendToFile(filename, ss.str());
}

int Scheduler::GetCPUExecutionTime(Queue<Process *> *job_queue_copy) {
    int execution_time = 0;
    const size_t N = job_queue_copy->Length();

    for (size_t _ = 0; _ < N; ++_) {
        Process *process = job_queue_copy->Dequeue();
        execution_time += process->GetCPUBurstTime1() + process->GetCPUBurstTime2();
        job_queue_copy->Enqueue(process);
    }

    return execution_time;
}

int Scheduler::GetFinishTime() {
    int finish_time = INT_MIN;
    const size_t N = terminated_queue->Length();

    for (size_t _ = 0; _ < N; ++_) {
        Process *process = terminated_queue->Dequeue();
        if (process->GetTerminationTime() > finish_time) finish_time = process->GetTerminationTime();
        terminated_queue->Enqueue(process);
    }

    return finish_time;
}

int Scheduler::GetCPUIdleTime(Queue<Process *> *job_queue_copy) {
    return GetFinishTime() - GetCPUExecutionTime(job_queue_copy);
}

float Scheduler::GetCPUUtilizationPercentage(Queue<Process *> *job_queue_copy) {
    return static_cast<float>(GetCPUExecutionTime(job_queue_copy)) / GetFinishTime() * 100;
}

// throughput = algorithm finish time / number of processes
float Scheduler::GetThroughput() { return static_cast<float>(GetFinishTime()) / terminated_queue->Length(); }

float Scheduler::GetAverageTurnaroundTime() {
    int total_turnaround_time = 0;
    const size_t N = terminated_queue->Length();

    for (size_t _ = 0; _ < N; ++_) {
        Process *process = terminated_queue->Dequeue();
        total_turnaround_time += process->GetTurnAroundTime();
        terminated_queue->Enqueue(process);
    }

    return static_cast<float>(total_turnaround_time) / N;
}

float Scheduler::GetAverageResponseTime() {
    int total_response_time = 0;
    const size_t N = terminated_queue->Length();

    for (size_t _ = 0; _ < N; ++_) {
        Process *process = terminated_queue->Dequeue();
        total_response_time += process->GetResponseTime();
        terminated_queue->Enqueue(process);
    }

    return static_cast<float>(total_response_time) / N;
}

float Scheduler::GetAverageWaitTime() {
    int total_wait_time = 0;
    const size_t N = terminated_queue->Length();

    for (size_t _ = 0; _ < N; ++_) {
        Process *process = terminated_queue->Dequeue();
        total_wait_time += process->GetWaitTime();
        terminated_queue->Enqueue(process);
    }

    return static_cast<float>(total_wait_time) / N;
}

void Scheduler::AnalyzeAlgorithm(std::string filename, Queue<Process *> *job_queue_copy) {
    std::stringstream ss;

    ss << "***" << filename << " Algorithm Analysis***\n" << std::endl;
    ss << "[CPU Execution Time]: " << GetCPUExecutionTime(job_queue_copy) << std::endl;
    ss << std::setprecision(4) << "[CPU Utilization Percentage]: " << GetCPUUtilizationPercentage(job_queue_copy)
       << std::endl;
    ss << "[CPU Idle Time]: " << GetCPUIdleTime(job_queue_copy) << std::endl;
    ss << std::setprecision(4) << "[Throughput]: " << GetThroughput() << std::endl;
    ss << std::setprecision(4) << "[Average Turnaround Time]: " << GetAverageTurnaroundTime() << std::endl;
    ss << std::setprecision(4) << "[Average Wait Time]: " << GetAverageWaitTime() << std::endl;
    ss << std::setprecision(4) << "[Average Response Time]: " << GetAverageResponseTime() << std::endl;

    filename = filename + "-AlgorithmAnalysis.log";
    FileWriter::ClearFile(filename);
    FileWriter::AppendToFile(filename, ss.str());
};
