#pragma once
#include <string>

class Process
{
private:
    unsigned int process_id;   // ID of the process
    unsigned int arrival_time; // Time when the process arrives
    unsigned int CPU_burst_time_1;
    unsigned int CPU_burst_time_2;
    unsigned int IO_burst_time;
    int response_time;    // Beginning of first CPU burst time
    int turn_around_time; // Time from arrival to termination
    int waiting_time;     // Time spent in ready queue
    int termination_time; // Time when process is terminated

public:
    Process(unsigned int process_id, unsigned int arrival_time, unsigned int CPU_burst_time_1, unsigned int CPU_burst_time_2, unsigned int IO_burst_time);
    static Process CopyProcess(Process *process);
    std::string ToString();

    // Getters
    unsigned int GetProcessID() const;
    unsigned int GetArrivalTime() const;
    unsigned int GetCPUBurstTime1() const;
    unsigned int GetCPUBurstTime2() const;
    unsigned int GetIOBurstTime() const;
    int GetResponseTime() const;
    int GetTurnAroundTime() const;
    int GetWaitTime() const;
    int GetTerminationTime() const;

    // Setters
    void SetProcessID(unsigned int process_id);
    void SetArrivalTime(unsigned int arrival_time);
    void SetCPUBurstTime1(unsigned int CPU_burst_time_1);
    void SetCPUBurstTime2(unsigned int CPU_burst_time_2);
    void SetIOBurstTime(unsigned int IO_burst_time);
    void SetResponseTime(int response_time);
    void SetTurnAroundTime(int turn_around_time);
    void SetWaitTime(int waiting_time);
    void SetTerminationTime(int termination_time);
};