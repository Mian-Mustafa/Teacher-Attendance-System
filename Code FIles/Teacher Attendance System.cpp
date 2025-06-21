#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

// Utility functions for time conversion
int timeToMinutes(const char* timeStr) {
    int hours, minutes;
    if (sscanf(timeStr, "%d:%d", &hours, &minutes) != 2) return 0;
    return hours * 60 + minutes;
}

void minutesToTime(int totalMinutes, char* buffer) {
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    sprintf(buffer, "%02d:%02d", hours, minutes);
}

// 1. Class: Person
class Person {
protected:
    char* name;
    int id;

public:
    Person() : name(nullptr), id(0) {}
    
    Person(const char* n, int i) : id(i) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    
    virtual ~Person() {
        delete[] name;
    }
    
    void getPersonalInfo() {
        char buffer[100];
        cout << "Enter name: ";
        cin.ignore();
        cin.getline(buffer, 100);
        delete[] name;
        name = new char[strlen(buffer) + 1];
        strcpy(name, buffer);
        
        cout << "Enter ID: ";
        cin >> id;
    }
    
    void displayPersonalInfo() const {
        cout << "Name: " << name << "\nID: " << id << endl;
    }
    
    int getID() const { return id; }
    const char* getName() const { return name; }
};

// 2. Class: TimeRecord
class TimeRecord {
protected:
    char inTime[6];  // HH:MM format
    char outTime[6]; // HH:MM format

public:
    TimeRecord() {
        inTime[0] = '\0';
        outTime[0] = '\0';
    }
    
    void setInTime(const char* time) { 
        strncpy(inTime, time, 5); 
        inTime[5] = '\0';
    }
    
    void setOutTime(const char* time) { 
        strncpy(outTime, time, 5); 
        outTime[5] = '\0';
    }
    
    const char* getInTime() const { return inTime; }
    const char* getOutTime() const { return outTime; }
};

// 3. Class: Attendance
class Attendance : public TimeRecord {
protected:
    int lateInMinutes;
    int earlyGoMinutes;
    int shortHours;
    int excessHours;

public:
    Attendance() : lateInMinutes(0), earlyGoMinutes(0), shortHours(0), excessHours(0) {}
    
    void calculateLateIn(const char* standardTime = "09:00") {
        if (strlen(inTime) == 0) return;
        int standard = timeToMinutes(standardTime);
        int actual = timeToMinutes(inTime);
        lateInMinutes = (actual > standard) ? (actual - standard) : 0;
    }
    
    void calculateEarlyGo(const char* standardTime = "17:00") {
        if (strlen(outTime) == 0) return;
        int standard = timeToMinutes(standardTime);
        int actual = timeToMinutes(outTime);
        earlyGoMinutes = (actual < standard) ? (standard - actual) : 0;
    }
    
    void calculateShortAndExcessHours() {
        if (strlen(inTime) == 0 || strlen(outTime) == 0) return;
        int totalMinutes = timeToMinutes(outTime) - timeToMinutes(inTime);
        int standardHours = 8 * 60;  // 8 hours
        
        if (totalMinutes < standardHours) {
            shortHours = standardHours - totalMinutes;
            excessHours = 0;
        } else {
            shortHours = 0;
            excessHours = totalMinutes - standardHours;
        }
    }
    
    void displayAttendanceReport() const {
        cout << "In-Time: " << inTime << "\nOut-Time: " << outTime
             << "\nLate Arrival: " << lateInMinutes << " min\nEarly Departure: " 
             << earlyGoMinutes << " min\nShort Hours: " << shortHours/60 
             << "h " << shortHours%60 << "min\nExtra Hours: " << excessHours/60 
             << "h " << excessHours%60 << "min" << endl;
    }
};

// 4. Class: Teacher
class Teacher : public Person, public Attendance {
private:
    char* subject;
    char* department;
    char* type;  // Permanent, Visiting, Administrative

public:
    Teacher() : Person(), subject(nullptr), department(nullptr), type(nullptr) {}
    
    Teacher(const char* n, int i, const char* sub, const char* dept, const char* t = "Permanent")
        : Person(n, i) {
        subject = new char[strlen(sub) + 1];
        strcpy(subject, sub);
        department = new char[strlen(dept) + 1];
        strcpy(department, dept);
        type = new char[strlen(t) + 1];
        strcpy(type, t);
    }
    
    ~Teacher() {
        delete[] subject;
        delete[] department;
        delete[] type;
    }
    
    Teacher(const Teacher& other) : Person(other), Attendance(other) {
        subject = new char[strlen(other.subject) + 1];
        strcpy(subject, other.subject);
        department = new char[strlen(other.department) + 1];
        strcpy(department, other.department);
        type = new char[strlen(other.type) + 1];
        strcpy(type, other.type);
    }
    
    Teacher& operator=(const Teacher& other) {
        if (this != &other) {
            Person::operator=(other);
            Attendance::operator=(other);
            
            delete[] subject;
            delete[] department;
            delete[] type;
            
            subject = new char[strlen(other.subject) + 1];
            strcpy(subject, other.subject);
            department = new char[strlen(other.department) + 1];
            strcpy(department, other.department);
            type = new char[strlen(other.type) + 1];
            strcpy(type, other.type);
        }
        return *this;
    }
    
    void getTeacherDetails() {
        getPersonalInfo();
        
        char buffer[100];
        cout << "Enter subject: ";
        cin.ignore();
        cin.getline(buffer, 100);
        delete[] subject;
        subject = new char[strlen(buffer) + 1];
        strcpy(subject, buffer);
        
        cout << "Enter department: ";
        cin.getline(buffer, 100);
        delete[] department;
        department = new char[strlen(buffer) + 1];
        strcpy(department, buffer);
        
        cout << "Enter type (Permanent/Visiting/Administrative): ";
        cin.getline(buffer, 100);
        delete[] type;
        type = new char[strlen(buffer) + 1];
        strcpy(type, buffer);
    }
    
    void displayTeacherInfo() const {
        displayPersonalInfo();
        cout << "Subject: " << subject << "\nDepartment: " << department 
             << "\nType: " << type << endl;
        displayAttendanceReport();
    }
    
    void logAttendance() {
        char in[6], out[6];
        cout << "Enter in-time (HH:MM): ";
        cin >> in;
        cout << "Enter out-time (HH:MM): ";
        cin >> out;
        setInTime(in);
        setOutTime(out);
        calculateLateIn();
        calculateEarlyGo();
        calculateShortAndExcessHours();
        
        ofstream log("attendance_log.txt", ios::app);
        if (log.is_open()) {
            log << id << "," << in << "," << out << "\n";
            log.close();
        }
    }
    
    const char* getSubject() const { return subject; }
    const char* getDepartment() const { return department; }
    const char* getType() const { return type; }
};

// Custom Stack implementation for undo functionality
class ActionStack {
private:
    struct ActionNode {
        char* action;
        ActionNode* next;
        
        ActionNode(const char* act) {
            action = new char[strlen(act) + 1];
            strcpy(action, act);
            next = nullptr;
        }
        
        ~ActionNode() {
            delete[] action;
        }
    };
    
    ActionNode* top;

public:
    ActionStack() : top(nullptr) {}
    
    ~ActionStack() {
        while (top) {
            ActionNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    void push(const char* action) {
        ActionNode* newNode = new ActionNode(action);
        newNode->next = top;
        top = newNode;
    }
    
    bool pop(char* action) {
        if (!top) return false;
        
        ActionNode* temp = top;
        top = top->next;
        strcpy(action, temp->action);
        delete temp;
        return true;
    }
    
    bool isEmpty() const {
        return top == nullptr;
    }
};

// Custom Queue implementation for login management
class LoginQueue {
private:
    struct QueueNode {
        int teacherID;
        QueueNode* next;
        
        QueueNode(int id) : teacherID(id), next(nullptr) {}
    };
    
    QueueNode* front;
    QueueNode* rear;

public:
    LoginQueue() : front(nullptr), rear(nullptr) {}
    
    ~LoginQueue() {
        while (front) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
    
    void enqueue(int id) {
        QueueNode* newNode = new QueueNode(id);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    bool dequeue(int& id) {
        if (!front) return false;
        
        QueueNode* temp = front;
        id = temp->teacherID;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return true;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
};

// BST Implementation for Teacher Management
class TeacherBST {
private:
    struct BSTNode {
        int id;
        Teacher* teacher;
        BSTNode* left;
        BSTNode* right;
        
        BSTNode(int i, Teacher* t) : id(i), teacher(t), left(nullptr), right(nullptr) {}
    };
    
    BSTNode* root;
    
    BSTNode* insertRec(BSTNode* node, int id, Teacher* t) {
        if (!node) return new BSTNode(id, t);
        
        if (id < node->id) 
            node->left = insertRec(node->left, id, t);
        else 
            node->right = insertRec(node->right, id, t);
        
        return node;
    }
    
    Teacher* searchRec(BSTNode* node, int id) const {
        if (!node) return nullptr;
        
        if (id == node->id) 
            return node->teacher;
        else if (id < node->id)
            return searchRec(node->left, id);
        else
            return searchRec(node->right, id);
    }
    
    void clearRec(BSTNode* node) {
        if (node) {
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }
    }

public:
    TeacherBST() : root(nullptr) {}
    
    ~TeacherBST() {
        clearRec(root);
    }
    
    void insert(int id, Teacher* t) {
        root = insertRec(root, id, t);
    }
    
    Teacher* search(int id) const {
        return searchRec(root, id);
    }
};

// 5. Class: Admin
class Admin : public Person {
private:
    char* role;
    ActionStack actionStack;

public:
    Admin() : Person(), role(nullptr) {}
    
    Admin(const char* n, int i, const char* r) : Person(n, i) {
        role = new char[strlen(r) + 1];
        strcpy(role, r);
    }
    
    ~Admin() {
        delete[] role;
    }
    
    void manageTeachers(Teacher* teachers, int& count, int maxCount, TeacherBST& bst) {
        int choice;
        do {
            cout << "\nTeacher Management\n";
            cout << "1. Add Teacher\n2. Remove Teacher\n3. View All Teachers\n4. Undo Last Action\n0. Exit\nChoice: ";
            cin >> choice;
            
            if (choice == 1) {
                if (count >= maxCount) {
                    cout << "Maximum teacher capacity reached!" << endl;
                    continue;
                }
                
                teachers[count].getTeacherDetails();
                bst.insert(teachers[count].getID(), &teachers[count]);
                
                char action[100];
                sprintf(action, "Added teacher: %d", teachers[count].getID());
                actionStack.push(action);
                count++;
                
                saveTeachersToFile(teachers, count);
                cout << "Teacher added successfully!" << endl;
            } 
            else if (choice == 2) {
                if (count == 0) {
                    cout << "No teachers to remove!" << endl;
                    continue;
                }
                
                cout << "Enter teacher ID to remove: ";
                int id;
                cin >> id;
                
                int index = -1;
                for (int i = 0; i < count; i++) {
                    if (teachers[i].getID() == id) {
                        index = i;
                        break;
                    }
                }
                
                if (index == -1) {
                    cout << "Teacher not found!" << endl;
                } else {
                    for (int i = index; i < count - 1; i++) {
                        teachers[i] = teachers[i + 1];
                    }
                    count--;
                    
                    char action[100];
                    sprintf(action, "Removed teacher: %d", id);
                    actionStack.push(action);
                    
                    saveTeachersToFile(teachers, count);
                    cout << "Teacher removed successfully!" << endl;
                }
            } 
            else if (choice == 3) {
                if (count == 0) {
                    cout << "No teachers available!" << endl;
                } else {
                    cout << "\n--- All Teachers ---\n";
                    for (int i = 0; i < count; i++) {
                        teachers[i].displayTeacherInfo();
                        cout << "------------------------\n";
                    }
                }
            } 
            else if (choice == 4) {
                char action[100];
                if (actionStack.pop(action)) {
                    cout << "Undid action: " << action << endl;
                } else {
                    cout << "No actions to undo!" << endl;
                }
            }
        } while (choice != 0);
    }
    
    void viewReports() {
        ifstream report("summary_report.txt");
        if (report.is_open()) {
            cout << "\n--- Attendance Reports ---\n";
            char line[200];
            while (report.getline(line, sizeof(line))) {
                cout << line << endl;
            }
            report.close();
        } else {
            cout << "No reports available!" << endl;
        }
    }

private:
    void saveTeachersToFile(Teacher* teachers, int count) {
        ofstream file("teachers.txt");
        if (file.is_open()) {
            for (int i = 0; i < count; i++) {
                file << teachers[i].getID() << "," 
                     << teachers[i].getName() << ","
                     << teachers[i].getSubject() << ","
                     << teachers[i].getDepartment() << ","
                     << teachers[i].getType() << "\n";
            }
            file.close();
        }
    }
};

// 6. Class: Department
class Department : protected Teacher {
private:
    char* departmentName;
    int numberOfTeachers;

public:
    Department() : departmentName(nullptr), numberOfTeachers(0) {}
    
    ~Department() {
        delete[] departmentName;
    }
    
    void setDepartmentInfo(const char* name, int count) {
        delete[] departmentName;
        departmentName = new char[strlen(name) + 1];
        strcpy(departmentName, name);
        numberOfTeachers = count;
    }
    
    void displayDepartmentInfo() const {
        cout << "Department: " << departmentName 
             << "\nNumber of Teachers: " << numberOfTeachers << endl;
    }
};

// 7. Class: ReportGenerator
class ReportGenerator : public Teacher {
private:
    Teacher* teachers;
    int teacherCount;
    int maxTeachers;
    char* reportDate;

public:
    ReportGenerator(int max = 3) : maxTeachers(max), teacherCount(0) {
        teachers = new Teacher[maxTeachers];
        time_t now = time(0);
        char* dt = ctime(&now);
        reportDate = new char[strlen(dt) + 1];
        strcpy(reportDate, dt);
    }
    
    ~ReportGenerator() {
        delete[] teachers;
        delete[] reportDate;
    }
    
    void inputTeachers() {
        if (teacherCount >= maxTeachers) {
            cout << "Maximum teacher capacity reached!" << endl;
            return;
        }
        
        teachers[teacherCount].getTeacherDetails();
        teacherCount++;
        cout << "Teacher added to report!" << endl;
    }
    
    void generateDailyReport() {
        ofstream report("summary_report.txt");
        if (report.is_open()) {
            report << "Daily Attendance Report - " << reportDate;
            report << "=======================================\n";
            
            for (int i = 0; i < teacherCount; i++) {
                report << "Teacher ID: " << teachers[i].getID() 
                       << "\nName: " << teachers[i].getName() 
                       << "\nSubject: " << teachers[i].getSubject()
                       << "\nDepartment: " << teachers[i].getDepartment()
                       << "\nType: " << teachers[i].getType()
                       << "\n\n";
            }
            report.close();
            cout << "Report generated successfully!" << endl;
        } else {
            cout << "Failed to generate report!" << endl;
        }
    }
};

// Graph implementation for department mapping
class DepartmentGraph {
private:
    struct GraphNode {
        char* department;
        GraphNode** connections;
        int connectionCount;
        int capacity;
        
        GraphNode(const char* dept) {
            department = new char[strlen(dept) + 1];
            strcpy(department, dept);
            capacity = 5;
            connections = new GraphNode*[capacity];
            connectionCount = 0;
        }
        
        ~GraphNode() {
            delete[] department;
            delete[] connections;
        }
        
        void addConnection(GraphNode* node) {
            if (connectionCount == capacity) {
                capacity *= 2;
                GraphNode** newConnections = new GraphNode*[capacity];
                for (int i = 0; i < connectionCount; i++) {
                    newConnections[i] = connections[i];
                }
                delete[] connections;
                connections = newConnections;
            }
            connections[connectionCount++] = node;
        }
    };
    
    GraphNode** departments;
    int departmentCount;
    int capacity;

public:
    DepartmentGraph() : departments(nullptr), departmentCount(0), capacity(10) {
        departments = new GraphNode*[capacity];
    }
    
    ~DepartmentGraph() {
        for (int i = 0; i < departmentCount; i++) {
            delete departments[i];
        }
        delete[] departments;
    }
    
    void addDepartment(const char* name) {
        if (departmentCount == capacity) {
            capacity *= 2;
            GraphNode** newDepartments = new GraphNode*[capacity];
            for (int i = 0; i < departmentCount; i++) {
                newDepartments[i] = departments[i];
            }
            delete[] departments;
            departments = newDepartments;
        }
        departments[departmentCount++] = new GraphNode(name);
    }
    
    void printDepartments() const {
        if (departmentCount == 0) {
            cout << "No departments available!" << endl;
            return;
        }
        
        cout << "\n--- Department List ---\n";
        for (int i = 0; i < departmentCount; i++) {
            cout << (i+1) << ". " << departments[i]->department << endl;
        }
    }
};

// Main Application
int main() {
    const int MAX_TEACHERS = 100;
    Teacher teachers[MAX_TEACHERS];
    int teacherCount = 0;
    
    TeacherBST teacherBST;
    LoginQueue loginQueue;
    DepartmentGraph deptGraph;
    
    // Initialize departments
    deptGraph.addDepartment("Computer Science");
    deptGraph.addDepartment("Mathematics");
    deptGraph.addDepartment("Physics");
    deptGraph.addDepartment("Electrical Engineering");
    deptGraph.addDepartment("Business Administration");
    
    // Create admin
    Admin admin("Admin", 1, "Head");
    
    // Create report generator
    ReportGenerator reportGen;
    
    // Create department
    Department csDept;
    csDept.setDepartmentInfo("Computer Science", 15);
    
    int choice;
    do {
        cout << "\nUniversity Attendance Management System\n";
        cout << "1. Teacher Login\n2. Admin Login\n3. Generate Reports\n";
        cout << "4. View Department Info\n5. View Departments\n0. Exit\nChoice: ";
        cin >> choice;
        
        if (choice == 1) {
            int id;
            cout << "Enter your ID: ";
            cin >> id;
            loginQueue.enqueue(id);
            
            cout << "Login request queued. Processing...\n";
            while (!loginQueue.isEmpty()) {
                int currentId;
                loginQueue.dequeue(currentId);
                Teacher* t = teacherBST.search(currentId);
                if (t) {
                    t->logAttendance();
                } else {
                    cout << "Error: Teacher ID " << currentId << " not found!\n";
                }
            }
        } 
        else if (choice == 2) {
            admin.manageTeachers(teachers, teacherCount, MAX_TEACHERS, teacherBST);
        } 
        else if (choice == 3) {
            int reportChoice;
            cout << "\nReport Generation\n";
            cout << "1. Add Teacher to Report\n2. Generate Daily Report\n0. Back\nChoice: ";
            cin >> reportChoice;
            
            if (reportChoice == 1) {
                reportGen.inputTeachers();
            } else if (reportChoice == 2) {
                reportGen.generateDailyReport();
            }
        } 
        else if (choice == 4) {
            csDept.displayDepartmentInfo();
        } 
        else if (choice == 5) {
            deptGraph.printDepartments();
        }
    } while (choice != 0);
    
    cout << "System shutdown. Goodbye!" << endl;
    return 0;
}