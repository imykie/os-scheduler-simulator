#include "scheduler.h"

#include <iomanip>

bool Scheduler::IsProcessing() { return terminated_queue->Length() < process_count; }

Process *Scheduler::GetCurrentProcess() { return current_process; };

void Scheduler::SetCurrentProcess(Process *process) { current_process = process; };

void Scheduler::AnalyzeProcess(std::string filename) {
    const size_t N = terminated_queue->Length();
    std::stringstream ss;

    ss << std::left << std::setw(14) << "Process ID" << std::setw(16) << "Arrival Time" << std::setw(20)
       << "Termination Time" << std::setw(17) << "Response Time" << std::setw(19) << "Turnaround Time" << std::setw(16)
       << "Waiting Time" << std::endl;

    for (int i = 0; i < N; ++i) {
        Process *process = terminated_queue->Dequeue();
        ss << std::left << std::setw(14) << process->GetProcessID() << std::setw(16) << process->GetArrivalTime()
           << std::setw(20) << process->GetTerminationTime() << std::setw(17) << process->GetResponseTime()
           << std::setw(19) << process->GetTurnAroundTime() << std::setw(16) << process->GetWaitTime() << std::endl;
        terminated_queue->Enqueue(process);
    }

    filename = filename + "-ProcessAnalysis.log";
    FileWriter::AppendToFile(filename, ss.str());
}