# 🚆 Train Coach Management Simulator

A highly efficient, console-based Train Coach Management Simulator developed in **C programming language** using the **Doubly Linked List** data structure. The project simulates train coach management by allowing users to dynamically add, insert, delete, search, and organize coaches while maintaining coach details such as coach number, coach type, and passenger capacity.

## 📌 Project Overview

The Train Coach Management Simulator is a Data Structures and Algorithms (DSA) mini-project designed to demonstrate the practical implementation of a Doubly Linked List.

Each train coach is represented as a node containing:
- **Coach Number:** Unique identification number of the coach.
- **Coach Type:** AC, Sleeper, or General.
- **Passenger Capacity:** Maximum passenger capacity of the coach.
- **Previous Pointer:** Address of the previous coach.
- **Next Pointer:** Address of the next coach.

The coaches are connected in both forward and backward directions, making insertion, deletion, and traversal operations efficient.

## ✨ Features

- **Add Coach:** Add a new coach at the end of the train.
- **Insert Coach:** Insert a coach at any valid position.
- **Delete Coach:** Remove a coach using its unique coach number.
- **Search Coach:** Search for a specific coach and display its details.
- **Forward Traversal:** Display all coaches from beginning to end.
- **Backward Traversal:** Display all coaches from end to beginning.
- **Total Passenger Capacity:** Calculate the combined capacity of all coaches.
- **Count Coaches:** Display the total number of coaches.
- **Duplicate Prevention:** Prevent duplicate coach numbers.
- **Input Validation:** Validate coach numbers, types, capacities, and positions.
- **Dynamic Memory Management:** Allocate and release memory using `malloc()` and `free()`.

## 🛠️ Technologies Used

- **Programming Language:** C
- **Data Structure:** Doubly Linked List
- **Compiler:** GCC (MinGW)
- **IDE:** Visual Studio Code

## 🧠 Data Structure Used

### Doubly Linked List

A Doubly Linked List is a linear data structure in which each node contains three parts:

1. Data
2. Pointer to the previous node (`prev`)
3. Pointer to the next node (`next`)

### Structure Representation

```text
NULL
  |
  v
+---------+     +---------+     +---------+
| Coach 1 | <-> | Coach 2 | <-> | Coach 3 |
+---------+     +---------+     +---------+
                                      |
                                      v
                                     NULL
```

### Node Structure

```c
struct Coach {
    int coachNo;
    char type[30];
    int capacity;

    struct Coach *prev;
    struct Coach *next;
};
```

- `head` points to the first coach.
- `tail` points to the last coach.
- `prev` connects to the previous coach.
- `next` connects to the next coach.

## 📂 Project Structure

```text
Train-Coach-Management-Simulator/
│
├── main.c
│
├── README.md
│
└── .gitignore
```

## ⚙️ Installation and Execution

### Step 1: Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/Train-Coach-Management-Simulator.git
```

### Step 2: Navigate to the Project Directory

```bash
cd Train-Coach-Management-Simulator
```

### Step 3: Compile the Program

```bash
gcc main.c -o train.exe
```

### Step 4: Run the Program

**Windows:**
```bash
.\train.exe
```

**Linux:**
```bash
gcc main.c -o train
./train
```

## 🖥️ Program Menu

```text
==================================
    TRAIN COACH MANAGEMENT SYSTEM
==================================
1. Add Coach
2. Insert Coach at Position
3. Delete Coach
4. Search Coach
5. Display Train (Forward)
6. Display Train (Backward)
7. Total Passenger Capacity
8. Count Total Coaches
9. Exit
==================================
Enter Your Choice:
```

## ⏱️ Time Complexity Analysis

| Operation | Time Complexity |
|---|---|
| Add Coach at End | O(1) |
| Insert Coach at Position | O(n) |
| Delete Coach by Number | O(n) |
| Search Coach | O(n) |
| Forward Traversal | O(n) |
| Backward Traversal | O(n) |
| Calculate Total Capacity | O(n) |
| Count Coaches | O(n) |
| Check Duplicate Coach | O(n) |

Here, `n` represents the total number of coaches in the train.

## 🎯 Learning Objectives

Through this project, I learned and implemented:

- Practical implementation of Doubly Linked Lists.
- Dynamic memory allocation using `malloc()`.
- Memory deallocation using `free()`.
- Pointer manipulation and node connections.
- Insertion and deletion operations.
- Forward and backward traversal.
- Searching and data validation.
- Time complexity analysis of DSA operations.

## 🚀 Future Enhancements

- Implement file handling to save train information permanently.
- Add passenger booking and seat allocation.
- Add coach modification functionality.
- Develop a graphical user interface (GUI).
- Generate train management reports.

## 👥 Team Members

This project was collaboratively developed by a team of three members as part of our Data Structures and Algorithms (DSA) Mini Project.

| S.No.| Team Member       | GitHub Profile                         |
|:----:|-------------------|----------------------------------------|
| 1    | Amritanshu Pandey | (https://github.com/amritanshu1010)    |
| 2    | Amrit Singh       | [GitHub](https://github.com/USERNAME2) |
| 3    | Amanul Haque      | [GitHub](https://github.com/USERNAME3) |

## 🤝 Team Contributions

All three team members collaborated on project planning, Doubly Linked List implementation, coding, testing, and documentation.

---

**Developed by a team of 3 as a Data Structures and Algorithms Mini Project.**

⭐ If you find this project useful, don't forget to give it a star!
