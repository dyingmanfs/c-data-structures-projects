# C Data Structures Projects

A collection of C programming projects focused on the implementation and practical use of fundamental **data structures and algorithms**.

The repository covers three main topics:

- Linked Lists
- Queues and Priority Queues
- AVL Trees

Each project applies a different data structure to a practical data-management or simulation problem.

## Projects

### Project 1 – Fishdom Linked List Management System

A command-line fish archive management application implemented using **linked lists**.

The application reads fish records from an external file and organizes them using a two-level linked structure:

```text
Species
   │
   ├── Fish Record
   ├── Fish Record
   └── Fish Record
   │
Next Species
```

Each species has its own linked list containing the fish records that belong to that species.

Fish records contain information such as:

- Species
- Weight
- Vertical length
- Diagonal length
- Cross length
- Height
- Fish length
- Fishing date
- City

Main functionality includes:

- Reading fish records from a file
- Creating linked lists dynamically
- Adding new fish records
- Adding new species
- Deleting fish records
- Searching fish by city
- Searching fish by month
- Displaying statistics
- Saving the updated archive back to a file

The project demonstrates dynamic memory allocation using `malloc()` and pointer-based linked data structures.

---

### Project 2 – Priority Queue Task Management Simulator

A task-distribution simulator implemented using **queues and priority queues**.

The system simulates how software-development tasks can be assigned to developers according to their priority and arrival time.

Tasks can have four priority levels:

```text
C → Critical
H → High Priority
M → Medium Priority
N → Normal
```

Priority values:

```text
Critical      → 4
High Priority → 3
Medium        → 2
Normal        → 1
```

Each task keeps information about:

- Arrival time
- Service time
- Service start time
- Assigned developer
- Priority level

Tasks are inserted into the queue according to:

1. Priority
2. Arrival time

The simulator also tracks developer availability.

A developer can work on only one task at a time.

At the end of the simulation, the application can report statistics including:

- Number of developers
- Number of completed tasks
- Number of tasks for each priority
- Tasks completed by each developer
- Total completion time
- Average waiting time
- Maximum waiting time

This project demonstrates priority-based scheduling and queue processing.

---

### Project 3 – Fish Analysis with AVL Trees

A fish data analysis application implemented using an **AVL Tree**.

Fish records are indexed according to their weight.

If multiple fish have the same weight, they are stored together in the same AVL tree node.

The system provides functionality for:

- Reading fish records
- Inserting records into an AVL tree
- Maintaining tree balance
- Displaying records in ascending weight order
- Finding the heaviest fish
- Finding the longest fish

An **in-order traversal** is used to display fish records sorted according to their weight.

The project demonstrates how a self-balancing binary search tree can be used for efficient data indexing and searching.

## Repository Structure

```text
c-data-structures-projects/
│
├── project-1-linked-list-fishdom/
│   ├── src/
│   │   └── fishdom.c
│   │
│   └── data/
│       └── fishingArchive.txt
│
├── project-2-priority-queue-simulator/
│   └── src/
│       ├── main.c
│       ├── q.c
│       └── q.h
│
├── project-3-avl-fish-analysis/
│   └── src/
│       ├── main.c
|       ├── avltree.c
│       └── avltree.h
│
├── README.md
└── .gitignore
```

## Project 1 – Linked Lists

The first project focuses on dynamic linked structures.

Two node types are used:

```text
fish_species_node
fish_info_node
```

The species nodes form one linked list, while each species points to another linked list containing its fish records.

Main concepts:

- Structures
- Pointers
- Dynamic memory allocation
- Linked-list traversal
- Insertion
- Deletion
- Searching
- File I/O

## Project 2 – Priority Queues

The second project focuses on task scheduling.

A task is inserted into the queue based on its priority while also considering its arrival time.

The simulation models multiple developers and tracks their availability.

Main concepts:

- Queues
- Priority queues
- Linked lists
- Scheduling
- Simulation
- Waiting-time calculation
- Dynamic memory

## Project 3 – AVL Trees

The third project focuses on balanced binary search trees.

The AVL tree automatically maintains its balance after insertions.

Main concepts:

- Binary Search Trees
- AVL Trees
- Tree rotations
- Tree height
- Balancing
- In-order traversal
- Searching
- Dynamic memory

## Compilation

A C compiler such as GCC can be used.

### Project 1

```bash
gcc fishdom.c -o fishdom
```

Run:

```bash
./fishdom
```

### Project 2

Example:

```bash
gcc TODO_Simulation.c -o TODO_Simulator
```

Run with command-line arguments according to the simulator configuration.

Example:

```bash
./TODO_Simulator 5 2 20 200
```

This represents:

```text
5 tasks
2 developers
20 maximum arrival time
200 maximum service time
```

### Project 3

Example:

```bash
gcc FishdomAnalysis.c -o FishdomAnalysis
```

Run:

```bash
./FishdomAnalysis
```

## Technologies

- C
- GCC
- File I/O
- Dynamic Memory Allocation
- Linked Lists
- Queues
- Priority Queues
- Binary Search Trees
- AVL Trees

## Concepts Practiced

- C structures
- Pointers
- Dynamic memory
- File processing
- Modular programming
- Linked data structures
- Queue operations
- Priority scheduling
- Tree traversal
- AVL balancing
- Algorithmic complexity

## Development Progression

The projects demonstrate increasing data-structure complexity:

```text
Project 1
Linked Lists
     ↓
Project 2
Queues & Priority Queues
     ↓
Project 3
AVL Trees
```

## Academic Context

These projects were developed as part of:

**CNG213 – Data Structures**

at **METU Northern Cyprus Campus**.

## Author

**Furkan Sağlam**

## Keywords

`C` `Data Structures` `Linked List` `Queue` `Priority Queue` `AVL Tree` `Binary Search Tree` `Pointers` `Dynamic Memory` `Algorithms`
