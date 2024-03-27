#include "scheduler.h"

bool Scheduler::IsProcessing() { return terminated_queue->Length() < process_count; }

Process *Scheduler::GetCurrentProcess() { return current_process; };

void Scheduler::SetCurrentProcess(Process *process) { current_process = process; };

void Scheduler::AnalyzeProcess(std::string filename) {
    std::vector<std::string> out;
    const size_t N = terminated_queue->Length();
    for (int i = 0; i < N; ++i) {
        Process *process = terminated_queue->Dequeue();
        out.push_back("[Process ID]: " + std::to_string(process->GetProcessID()));
        out.push_back("[Arrival Time]: " + std::to_string(process->GetArrivalTime()));
        out.push_back("[Termination Time]: " + std::to_string(process->GetTerminationTime()));
        out.push_back("[Response Time]: " + std::to_string(process->GetResponseTime()));
        out.push_back("[Turnaround Time]: " + std::to_string(process->GetTerminationTime()));
        out.push_back("[Waiting Time]: " + std::to_string(process->GetWaitTime()));
        out.push_back("\n");
        terminated_queue->Enqueue(process);
    }
    filename = filename + "-ProcessAnalysis.log";
    FileWriter::WriteToFile(filename, out);
}