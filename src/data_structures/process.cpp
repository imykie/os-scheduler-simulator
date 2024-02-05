#include "process.h"

#include <iterator>
#include <sstream>
#include <vector>

Process::Process(unsigned int process_id, unsigned int arrival_time,
                 unsigned int CPU_burst_time_1, unsigned int CPU_burst_time_2,
                 unsigned int IO_burst_time) {
    this->process_id = process_id;
    this->arrival_time = arrival_time;
    this->CPU_burst_time_1 = CPU_burst_time_1;
    this->CPU_burst_time_2 = CPU_burst_time_2;
    this->IO_burst_time = IO_burst_time;
    this->response_time = -1;
    this->turn_around_time = -1;
    this->waiting_time = -1;
    this->termination_time = -1;
};

Process *Process::Copy(Process *process) {
    Process *new_process = new Process(
        process->process_id, process->arrival_time, process->CPU_burst_time_1,
        process->CPU_burst_time_2, process->IO_burst_time);
    new_process->SetResponseTime(process->response_time);
    new_process->SetTurnAroundTime(process->turn_around_time);
    new_process->SetWaitTime(process->waiting_time);
    new_process->SetTerminationTime(process->termination_time);
    return new_process;
};

std::string Process::ToString() {
    std::vector<std::string> out;
    out.push_back("[Process ID]: " + std::to_string(this->process_id));
    out.push_back("[Arrive Time]: " + std::to_string(this->arrival_time));
    out.push_back("[CPU Burst Time 1]: " +
                  std::to_string(this->CPU_burst_time_1));
    out.push_back("[CPU Burst Time 2]: " +
                  std::to_string(this->CPU_burst_time_2));
    out.push_back("[IO Burst Time]: " + std::to_string(this->IO_burst_time));
    out.push_back("[Response Time]: " + std::to_string(this->response_time));
    out.push_back("[Turn Around Time]: " +
                  std::to_string(this->turn_around_time));
    out.push_back("[Waiting Time]: " + std::to_string(this->waiting_time));
    out.push_back("[Termination Time]: " +
                  std::to_string(this->termination_time));

    const char *const delim = "\n";
    std::ostringstream imploded;
    std::copy(out.begin(), out.end(),
              std::ostream_iterator<std::string>(imploded, delim));
    return imploded.str();
};

// Getters
unsigned int Process::GetProcessID() const { return this->process_id; };
unsigned int Process::GetArrivalTime() const { return this->arrival_time; };
unsigned int Process::GetCPUBurstTime1() const {
    return this->CPU_burst_time_1;
};
unsigned int Process::GetCPUBurstTime2() const {
    return this->CPU_burst_time_2;
};
unsigned int Process::GetIOBurstTime() const { return this->IO_burst_time; };
int Process::GetResponseTime() const { return this->response_time; };
int Process::GetTurnAroundTime() const { return this->turn_around_time; };
int Process::GetWaitTime() const { return this->waiting_time; };
int Process::GetTerminationTime() const { return this->termination_time; };

// Setters
void Process::SetProcessID(unsigned int process_id) {
    this->process_id = process_id;
};
void Process::SetArrivalTime(unsigned int arrival_time) {
    this->arrival_time = arrival_time;
};
void Process::SetCPUBurstTime1(unsigned int CPU_burst_time_1) {
    this->CPU_burst_time_1 = CPU_burst_time_1;
};
void Process::SetCPUBurstTime2(unsigned int CPU_burst_time_2) {
    this->CPU_burst_time_2 = CPU_burst_time_2;
};
void Process::SetIOBurstTime(unsigned int IO_burst_time) {
    this->IO_burst_time = IO_burst_time;
};
void Process::SetResponseTime(int response_time) {
    this->response_time = response_time;
};
void Process::SetTurnAroundTime(int turn_around_time) {
    this->turn_around_time = turn_around_time;
};
void Process::SetWaitTime(int waiting_time) {
    this->waiting_time = waiting_time;
};
void Process::SetTerminationTime(int termination_time) {
    this->termination_time = termination_time;
};
