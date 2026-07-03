# 📚 Data Structures & Algorithms Applications

A collection of menu-driven C++ console applications built to demonstrate the practical implementation of **Data Structures & Algorithms (DSA)** in solving real-world problems. Each application models a familiar scenario and leverages efficient STL containers and algorithms to provide optimized solutions.

---

# 📌 Overview

This repository consists of three independent applications that showcase how different data structures can be applied to solve practical problems efficiently.

### Included Applications

- ✅ Smart Task Management System
- ✅ Exam Ranking System
- ✅ Inventory & Billing System

---

# 🎯 Project 1: Smart Task Management System

A menu-driven C++ application that organizes daily tasks using efficient data structures for priority scheduling, instant searching, and undo operations.

## 📌 Problem Statement

Managing daily tasks requires fast searching, priority-based scheduling, and the flexibility to undo recent actions. This application simulates a task manager capable of efficiently handling these operations using advanced data structures.

## ✨ Features

- ➕ Add, update, and delete tasks
- ⚡ Retrieve the highest-priority pending task
- 🔍 Search tasks instantly using Task ID
- 📅 View all tasks sorted by priority
- ↩️ Undo the most recent operation
- 📊 Display task statistics

## 🧠 Data Structures Used

| Feature | Data Structure | Purpose |
|---------|----------------|---------|
| Priority Scheduling | Max Heap | Retrieves the highest-priority task efficiently |
| Task Search | Hash Map | Constant-time task lookup |
| Undo Operation | Stack | Reverses the most recent action |
| Task Display | Sorting | Displays tasks in organized order |

---

# 🎓 Project 2: Exam Ranking System

A C++ console application that manages student records and generates academic rankings using efficient searching and sorting algorithms.

## 📌 Problem Statement

Educational institutions require a reliable system to manage student records, generate rank lists, and identify top-performing students efficiently.

## ✨ Features

- 📝 Add student records
- 🔍 Search student details using Roll Number
- 🏆 Generate complete rank list
- ⭐ Display Top-N performers
- 📊 Grade distribution analysis
- 💾 Export ranking report

## 🧠 Data Structures Used

| Feature | Data Structure | Purpose |
|---------|----------------|---------|
| Student Search | Hash Map | O(1) average lookup |
| Rank Generation | Sorting | Orders students by marks |
| Top-N Students | Min Heap | Efficiently retrieves highest scorers |
| Grade Analysis | Hash Map | Frequency counting |

---

# 🛒 Project 3: Inventory & Billing System

A C++ console application that simulates inventory management and billing operations using multiple data structures.

## 📌 Problem Statement

Retail stores need an efficient way to manage inventory, process customer orders, generate bills, and monitor stock levels. This project models these operations using optimized data structures.

## ✨ Features

- 📦 Add and update inventory
- 🛍️ Process customer orders
- 🧾 Generate bills
- ↩️ Cancel recent billing operations
- ⚠️ Low-stock notifications
- 📊 Sales report generation

## 🧠 Data Structures Used

| Feature | Data Structure | Purpose |
|---------|----------------|---------|
| Inventory Lookup | Hash Map | Fast stock retrieval |
| Order Processing | Queue | FIFO order execution |
| Undo Billing | Stack | Reverts latest billing action |
| Low Stock Alert | Min Heap | Displays lowest stock items |
| Sales Report | Sorting | Revenue-based ranking |

---

# ⚡ Time Complexity

| Operation | Complexity |
|-----------|------------|
| Search | O(1) Average |
| Insert | O(1) / O(log n) |
| Delete | O(1) / O(log n) |
| Heap Operations | O(log n) |
| Sorting | O(n log n) |

---

# 🛠️ Technologies Used

- **C++17**
- Standard Template Library (STL)

---

# 📚 STL Components Used

- unordered_map
- priority_queue (Max Heap & Min Heap)
- queue
- stack
- vector
- algorithms
- custom comparators
- file handling

---

# 📂 Project Structure

```
Data-Structures-Algorithms-Applications/
│
├── Smart_Task_Management_System.cpp
├── Exam_Ranking_System.cpp
├── Inventory_Billing_System.cpp
├── README.md
```

---

# 🚀 How to Run

Compile any application using a C++17 compiler.

### Smart Task Management

```bash
g++ -std=c++17 Smart_Task_Management_System.cpp -o task_manager
./task_manager
```

### Exam Ranking System

```bash
g++ -std=c++17 Exam_Ranking_System.cpp -o exam_ranking
./exam_ranking
```

### Inventory & Billing System

```bash
g++ -std=c++17 Inventory_Billing_System.cpp -o inventory_billing
./inventory_billing
```

---

# 💡 Learning Outcomes

This project demonstrates practical implementation of:

- Heap-based Priority Scheduling
- Hash-based Searching
- Queue-based Processing
- Stack-based Undo Operations
- Sorting Algorithms
- Efficient Time Complexity Optimization
- Object-Oriented Programming in C++
- STL Containers and Algorithms

---

# 🎯 Project Highlights

- Developed **three independent real-world applications** using C++.
- Applied **Heaps, Hash Maps, Queues, Stacks, and Sorting** to solve practical problems.
- Optimized data retrieval and processing using efficient algorithms.
- Demonstrated practical applications of core Data Structures beyond theoretical implementations.

---

# 👨‍💻 Author

**Shailendra Meena**
