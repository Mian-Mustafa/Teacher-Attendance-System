# 📘 Teacher Attendance Management System

A comprehensive **C++ project** for managing university-level teacher attendance. This system simulates a fully functional attendance monitoring and administrative tool tailored for academic institutions.

---

## 🚀 Features

### 👤 Teacher Profiles
- Name, ID, Subject, Department, Type (Full-time/Part-time)

### ⏱️ Attendance Logging
- In-Time and Out-Time tracking
- Calculates:
  - ⏰ Late Arrivals
  - 🕔 Early Departures
  - ⌛ Short and Excess Hours

### 📊 Report Generation
- Daily summary reports
- Text-based log storage

### 🧑‍💼 Admin Panel
- Add, remove, and view teachers
- Undo functionality using **Stack**

### 📥 Login Queue System
- FIFO-based teacher login queue

### 🌲 Teacher Record Lookup (BST)
- Binary Search Tree for fast teacher ID search

### 🏢 Department Management
- Department-wise view
- Graph structure (adjacency list) for department mapping

---

## 🧱 Code Architecture

### 📦 Classes
- `Person` – Base class for all users
- `Teacher` – Inherits from `Person` and `Attendance`
- `Attendance` – Handles time calculations
- `Admin` – Manages teacher records
- `Department`, `DepartmentGraph` – Department info and graph
- `ReportGenerator` – Creates daily reports

### 🔧 Data Structures Used
- 🌀 **Stack** – Undo operations  
- 📬 **Queue** – Login order tracking  
- 🌳 **Binary Search Tree (BST)** – Teacher record retrieval  
- 🔗 **Graph (Adjacency List)** – Department mapping

---

## 💾 File Structure

| File Name                  | Description                            |
|---------------------------|----------------------------------------|
| `Teacher Attendance System.cpp` | Main source file                    |
| `teachers.txt`            | Teacher database (flat file)           |
| `attendance_log.txt`      | In/Out log records                     |
| `summary_report.txt`      | Daily report generated from logs       |

---

## 🧠 Key Concepts Practiced

- Object-Oriented Programming (OOP)
- Inheritance & Polymorphism
- File I/O and Data Persistence
- Custom Stack, Queue, BST, Graph Implementations
- Date and Time Handling

---

## 🏫 Ideal For

- 🎓 University Semester Projects  
- 🧠 C++ DSA & OOP Practice  
- 💼 Software Engineering Demonstrations  
- 📁 Academic Portfolio Enhancement  

---

## 🛠️ Getting Started

### 🔗 Prerequisites
- C++ compiler (e.g., g++, MinGW, or MSVC)
- Any IDE (e.g., VS Code, Code::Blocks, or Visual Studio)

### 🧪 Run Instructions

```bash
# Clone the repository
git clone https://github.com/your-username/teacher-attendance-system.git

# Navigate into the project directory
cd teacher-attendance-system

# Compile the program (example using g++)
g++ -o AttendanceSystem "Teacher Attendance System.cpp"

# Run the compiled program
./AttendanceSystem
