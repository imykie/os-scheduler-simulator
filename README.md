# Operating System Scheduler Simulator

  <p><strong>The objective of this project is to simulate the scheduling procedures utilized by operating systems in a comprehensive manner. Through the implementation of various scheduling algorithms, users can analyze and assess their performance across different scenarios. The project seeks to enhance understanding of scheduling concepts and enable comparison of the efficacy of different algorithms.</strong></p>

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage Guide](#usage-guide)
- [Example](#example)

## Features

- Implementation of the following scheduling algorithms:
  - First-Come, First-Served (FCFS)
  - Shortest Job First (SJF)
  - Round Robin (RR)
  - Multilevel Feedback Queue (MLFQ)
- Generate detailed timeline logs to track process movements based on the implemented algorithms for simulating scheduling processes.
- States in the scheduling procedure:

  - NEW
  - READY
  - RUNNING
  - WAITING
  - TERMINATED

  ## Project Structure

```
├── src/
│   └── data_structures/
│       ├── process.cpp
│       ├── process.h
│       ├── queue_node.h
│       ├── queue_util.h
│       └── queue.h
│   └── io/
│       └── reader/
│           ├── process_file_reader.cpp
│           └── process_file_reader.h
│       └── writer/
│           ├── file_writer.cpp
│           └── file_writer.h
│       ├── helper.cpp
│       └── helper.h
│   └── schedulers/
│       ├── fcfs.cpp
│       ├── fcfs.h
│       ├── mlfq.cpp
│       ├── mlfq.h
│       ├── rr.cpp
│       ├── rr.h
│       ├── scheduler.cpp
│       ├── scheduler.h
│       ├── sjf.cpp
│       └── sjf.h
│   └── timestamp/
│       ├── timestamp_interface.h
│       ├── timestamp_observer.cpp
│       ├── timestamp_observer.h
│       ├── timestamp_topic.cpp
│       ├── timestamp_topic.h
│       ├── timestamp.cpp
│       └── timestamp.h
│   └── main.cpp
├── .clang-format
├── .gitignore
├── example.csv
├── LICENSE
├── README.md
└── run.sh
```

### Requirements

- C++ compiler (C++17 e.g. GCC or CLANG)
- Git CLI tool (or Git GUI client) to clone the repository.

### Installation

1. Clone this repository: `git clone https://github.com/imykie/os-scheduler-simulator`
2. Navigate to the cloned repository's directory and Compile the source code using the following command: `./run.sh <your-test-file-path.csv>` (the program will also run after using this command)
3. Run the compiled executable: `./program`

### Usage Guide

1. Prepare a CSV file containing the processes of the job queue in the following format:
   ```
   process_id,arrival_time,cpu_time1,cpu_time2,io_time
   ```
   - **process_id**: The process unique identifier.
   - **arrival_time**: The time at which the process arrives.
   - **cpu_time1**: The first CPU burst time duration.
   - **cpu_time2**: The second CPU burst time duration.
   - **io_time**: The I/O burst time duration for the process.
2. Compile and run the program.
3. After the execution is completed, the following log files will be generated:
   ```
   ├── FCFS-Algorithm-Analysis.log
   ├── FCFS-Processes-Analysis.log
   ├── FCFS.log
   ├── MLFQ-Algorithm-Analysis.log
   ├── MLFQ-Processes-Analysis.log
   ├── MLFQ.log
   ├── RR-Algorithm-Analysis.log
   ├── RR-Processes-Analysis.log
   ├── RR.log
   ├── SJF-Algorithm-Analysis.log
   ├── SJF-Processes-Analysis.log
   └── SJF.log
   ```

## Example

**example.csv**

```
process_id,arrival_time,cpu_time1,cpu_time2,io_time
1,0,2,2,2
2,1,1,1,0
```

**FCFS.log**
```
***First Come First Serve (FCFS) Scheduling Algorithm***

[Time]: 0 - 1
[Process ID]: 1, Moved from Job Queue to Ready Queue [NEW -> READY]
[Process ID]: 1, Moved from Ready Queue to Running State [READY -> RUNNING]
[Process ID]: 1, First CPU Burst Time was executed for 1 second, [Remaining First CPU Burst Time]: 1
[Time]: 1 - 2
[Process ID]: 2, Moved from Job Queue to Ready Queue [NEW -> READY]
[Process ID]: 1, First CPU Burst Time was executed for 1 second, [Remaining First CPU Burst Time]: 0
[Process ID]: 1, Moved from Running State to Waiting Queue to execute IO burst time [RUNNING -> WAITING]
[Time]: 2 - 3
[Process ID]: 2, Moved from Ready Queue to Running State [READY -> RUNNING]
[Process ID]: 1, Waited for IO resources for 1 second, [Remaining IO Burst Time]: 1
[Process ID]: 2, First CPU Burst Time was executed for 1 second, [Remaining First CPU Burst Time]: 0
[Time]: 3 - 4
[Process ID]: 1, Waited for IO resources for 1 second, [Remaining IO Burst Time]: 0
[Process ID]: 1, IO waiting time finished, Moved from Waiting Queue to Ready Queue [WAITING -> READY]
[Process ID]: 2, Second CPU Burst Time was executed for 1 second, [Remaining Second CPU Burst Time]: 0
[Process ID]: 2, was terminated [RUNNING - TERMINATED]
[Time]: 4 - 5
[Process ID]: 1, Moved from Ready Queue to Running State [READY -> RUNNING]
[Process ID]: 1, Second CPU Burst Time was executed for 1 second, [Remaining Second CPU Burst Time]: 1
[Time]: 5 - 6
[Process ID]: 1, Second CPU Burst Time was executed for 1 second, [Remaining Second CPU Burst Time]: 0
[Process ID]: 1, was terminated [RUNNING - TERMINATED]
```

**FCFS-Algorithm-Analysis.log**
```
***FCFS Algorithm Analysis***

[CPU Execution Time]: 6
[CPU Utilization Percentage]: 100
[CPU Idle Time]: 0
[Throughput]: 3
[Average Turnaround Time]: 4.5
[Average Wait Time]: 4.5
[Average Response Time]: 1

```

**FCFS-Processes-Analysis.log**

`***FCFS Process Analysis***`

| Process ID | Arrival Time | Termination Time | Response Time | Turnaround Time | Waiting Time |
|---|---|---|---|---|---|
| 2 | 1 | 4 | 2 | 3 | 3 |
| 1 | 0 | 6 | 0 | 6 | 6 |
