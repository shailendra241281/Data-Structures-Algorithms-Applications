/*
=====================================================================
 EXAM / RESULT MANAGEMENT & RANKING SYSTEM
=====================================================================
 DSA Concepts Used:
   1. Hash Map (unordered_map)     -> O(1) search of a student by roll no.
   2. Sorting (custom comparator)  -> generate rank list by total marks
   3. Min-Heap (priority_queue)    -> efficiently maintain Top-N toppers
   4. Hashing (unordered_map)      -> grade distribution frequency count
=====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int NUM_SUBJECTS = 5;

// ---------------------------------------------------------------
// SECTION 1: DATA MODEL
// ---------------------------------------------------------------
struct Student {
    int roll;
    string name;
    int marks[NUM_SUBJECTS];
    int total;
    double percentage;
    char grade;
};

// ---------------------------------------------------------------
// SECTION 2: GLOBAL STORAGE
// ---------------------------------------------------------------
unordered_map<int, Student> studentMap;   // roll -> Student (Hash Map)

// ---------------------------------------------------------------
// SECTION 3: HELPER FUNCTIONS
// ---------------------------------------------------------------
char computeGrade(double percentage) {
    if (percentage >= 90) return 'A';
    if (percentage >= 75) return 'B';
    if (percentage >= 60) return 'C';
    if (percentage >= 40) return 'D';
    return 'F';
}

// ---------------------------------------------------------------
// SECTION 4: CORE OPERATIONS
// ---------------------------------------------------------------
void addStudent() {
    Student s;
    cout << "Enter roll number: ";
    cin >> s.roll;

    if (studentMap.find(s.roll) != studentMap.end()) {
        cout << "Student with this roll number already exists.\n";
        return;
    }

    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, s.name);

    s.total = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        cout << "Enter marks for subject " << (i + 1) << " (out of 100): ";
        cin >> s.marks[i];
        s.total += s.marks[i];
    }
    s.percentage = (double)s.total / (NUM_SUBJECTS * 100) * 100.0;
    s.grade = computeGrade(s.percentage);

    studentMap[s.roll] = s;
    cout << "Student added. Total: " << s.total
         << " | Percentage: " << fixed << setprecision(2) << s.percentage
         << "% | Grade: " << s.grade << "\n";
}

void searchStudentByRoll() {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;

    auto it = studentMap.find(roll);
    if (it == studentMap.end()) {
        cout << "Student not found.\n";
        return;
    }
    Student &s = it->second;
    cout << "Roll: " << s.roll << " | Name: " << s.name
         << " | Total: " << s.total
         << " | Percentage: " << fixed << setprecision(2) << s.percentage
         << "% | Grade: " << s.grade << "\n";
}

void viewRankList() {
    vector<Student> students;
    for (auto &p : studentMap) students.push_back(p.second);

    // Sorting: rank by total marks descending, ties broken by name
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        if (a.total != b.total) return a.total > b.total;
        return a.name < b.name;
    });

    cout << "\n----- RANK LIST -----\n";
    int rank = 1;
    for (auto &s : students) {
        cout << "Rank " << rank++ << ": " << s.name << " (Roll " << s.roll
             << ") - Total: " << s.total
             << " | " << fixed << setprecision(2) << s.percentage
             << "% | Grade: " << s.grade << "\n";
    }
    if (students.empty()) cout << "No student records available.\n";
}

void topNToppers() {
    int n;
    cout << "Enter N (number of toppers to display): ";
    cin >> n;

    // Min-Heap of size N: keeps the N highest totals seen so far
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;

    for (auto &p : studentMap) {
        int total = p.second.total;
        int roll = p.second.roll;
        minHeap.push({total, roll});
        if ((int)minHeap.size() > n) minHeap.pop(); // remove smallest, keep top N
    }

    vector<pair<int,int>> toppers;
    while (!minHeap.empty()) {
        toppers.push_back(minHeap.top());
        minHeap.pop();
    }
    // reverse to show highest first
    reverse(toppers.begin(), toppers.end());

    cout << "\n----- TOP " << n << " TOPPERS -----\n";
    int pos = 1;
    for (auto &pr : toppers) {
        Student &s = studentMap[pr.second];
        cout << pos++ << ". " << s.name << " (Roll " << s.roll
             << ") - Total: " << s.total << "\n";
    }
    if (toppers.empty()) cout << "No student records available.\n";
}

void gradeDistribution() {
    unordered_map<char, int> gradeCount;  // grade -> frequency (Hashing)
    for (auto &p : studentMap) {
        gradeCount[p.second.grade]++;
    }

    cout << "\n----- GRADE DISTRIBUTION -----\n";
    vector<char> order = {'A', 'B', 'C', 'D', 'F'};
    for (char g : order) {
        cout << "Grade " << g << ": " << gradeCount[g] << " student(s)\n";
    }
}

// ---------------------------------------------------------------
// SECTION 5: FILE EXPORT
// ---------------------------------------------------------------
void exportRankListToFile() {
    vector<Student> students;
    for (auto &p : studentMap) students.push_back(p.second);

    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.total > b.total;
    });

    ofstream fout("rank_list.txt");
    fout << "Rank,Roll,Name,Total,Percentage,Grade\n";
    int rank = 1;
    for (auto &s : students) {
        fout << rank++ << "," << s.roll << "," << s.name << "," << s.total << ","
             << fixed << setprecision(2) << s.percentage << "," << s.grade << "\n";
    }
    fout.close();
    cout << "Rank list exported to rank_list.txt\n";
}

// ---------------------------------------------------------------
// SECTION 6: MENU DRIVEN INTERFACE
// ---------------------------------------------------------------
void showMenu() {
    cout << "\n===== EXAM / RESULT RANKING SYSTEM =====\n";
    cout << "1. Add Student Record\n";
    cout << "2. Search Student by Roll Number\n";
    cout << "3. View Rank List\n";
    cout << "4. View Top-N Toppers\n";
    cout << "5. View Grade Distribution\n";
    cout << "6. Export Rank List to File\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudentByRoll(); break;
            case 3: viewRankList(); break;
            case 4: topNToppers(); break;
            case 5: gradeDistribution(); break;
            case 6: exportRankListToFile(); break;
            case 0: cout << "Exiting. Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
