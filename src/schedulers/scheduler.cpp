#include "scheduler.h"

bool Scheduler::IsProcessing() { return terminated_queue->Length() < process_count; }

Process *Scheduler::GetCurrentProcess() { return current_process; };

void Scheduler::SetCurrentProcess(Process *process) { current_process = process; };