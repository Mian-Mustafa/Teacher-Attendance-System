📘 Teacher Attendance Management System
This is a comprehensive C++ project for managing university-level teacher attendance. It is designed to simulate a fully functional attendance monitoring and administrative tool for academic institutions.

🚀 Features
👤 Teacher Profiles (Name, ID, Subject, Department, Type)

⏱️ Attendance Logging (In-Time, Out-Time)

🕒 Time Calculations:

Late arrivals

Early departures

Short and excess hours

📊 Report Generation:

Daily summary reports

Text-based log storage

🧑‍💼 Admin Panel:

Add, remove, and view teachers

Undo functionality via stack

📂 Persistent Storage:

Logs (attendance_log.txt)

Teacher database (teachers.txt)

Attendance reports (summary_report.txt)

📥 Login Queue System (FIFO)

🌲 Teacher BST (Binary Search Tree):

Fast retrieval of teacher records by ID

🏢 Department Management:

View department information

Simulated department graph (adjacency-based)

🧱 Code Structure
Object-Oriented Design:
Person – Base class for all users.

Teacher – Derived from Person and Attendance.

Attendance – Handles all time-related calculations.

Admin – Manages teacher database and actions.

Department, DepartmentGraph – For department metadata.

ReportGenerator – For generating daily reports.

Data Structures Used:
Stack – For undo actions

Queue – For teacher login queue

Binary Search Tree – For optimized teacher lookup

Graph – For department mapping

💾 File Details
Teacher Attendance System.cpp – Main project source file.

attendance_log.txt – Stores individual log entries.

summary_report.txt – Daily report generated via ReportGenerator.

teachers.txt – Flat-file storage of teacher information.
🧠 Concepts Practiced
Object-Oriented Programming (OOP)

File Handling

Time and Date manipulation

Custom data structures (Stack, Queue, BST, Graph)

Inheritance & Polymorphism

🏫 Ideal For
University semester projects

C++ practice for data structures and OOP

Demonstration in software engineering or professional practices
