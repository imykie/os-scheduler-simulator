  # Operating System Scheduler Simulator
  <p><strong>The objective of this project is to simulate the scheduling procedures utilized by operating systems in a comprehensive manner. Through the implementation of various scheduling algorithms, users can analyze and assess their performance across different scenarios. The project seeks to enhance understanding of scheduling concepts and enable comparison of the efficacy of different algorithms.</strong></p>

## Table of Contents
- [Features](#features)
- [Project Structure](#project-structure)

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