/*
=====================================================================
 SMART TASK MANAGEMENT SYSTEM
=====================================================================
 DSA Concepts Used:
   1. Max-Heap (priority_queue)  -> fetch the most urgent task fast
   2. Hash Map (unordered_map)   -> O(1) search of a task by ID
   3. Stack                      -> undo the last Add/Delete action
   4. Sorting (custom comparator)-> view tasks ordered by deadline
=====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------
// SECTION 1: DATA MODEL
// ---------------------------------------------------------------
struct Task {
    int id;
    string name;
    string category;
    int priority;     // 1 (low) - 5 (high/urgent)
    string deadline;  // format: YYYY-MM-DD
    bool done;
};

// Action record used for Undo (Stack)
struct Action {
    string type;   // "ADD" or "DELETE"
    Task task;
};

// ---------------------------------------------------------------
// SECTION 2: GLOBAL STORAGE STRUCTURES
// ---------------------------------------------------------------
unordered_map<int, Task> taskMap;             // id -> Task  (Hash Map)
priority_queue<pair<int,int>> priorityHeap;   // {priority, id} (Max-Heap)
stack<Action> undoStack;                      // last actions (Stack)
int nextId = 1;

// ---------------------------------------------------------------
// SECTION 3: CORE OPERATIONS
// ---------------------------------------------------------------
void addTask() {
    Task t;
    t.id = nextId++;
    cout << "Enter task name: ";
    cin.ignore();
    getline(cin, t.name);
    cout << "Enter category: ";
    getline(cin, t.category);
    cout << "Enter priority (1-5): ";
    cin >> t.priority;
    cout << "Enter deadline (YYYY-MM-DD): ";
    cin >> t.deadline;
    t.done = false;

    taskMap[t.id] = t;
    priorityHeap.push({t.priority, t.id});
    undoStack.push({"ADD", t});

    cout << "Task added with ID " << t.id << "\n";
}

void deleteTask() {
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;

    if (taskMap.find(id) == taskMap.end()) {
        cout << "Task not found.\n";
        return;
    }
    Task removed = taskMap[id];
    taskMap.erase(id);
    undoStack.push({"DELETE", removed});
    cout << "Task " << id << " deleted.\n";
    // Note: lazy deletion from heap -> checked when popping (see getNextPriorityTask)
}

void searchTaskById() {
    int id;
    cout << "Enter task ID to search: ";
    cin >> id;

    auto it = taskMap.find(id);
    if (it == taskMap.end()) {
        cout << "Task not found.\n";
        return;
    }
    Task &t = it->second;
    cout << "ID: " << t.id << " | " << t.name << " | " << t.category
         << " | Priority: " << t.priority << " | Deadline: " << t.deadline
         << " | Done: " << (t.done ? "Yes" : "No") << "\n";
}

void getNextPriorityTask() {
    // Lazy deletion: pop entries whose id no longer exists in the map
    while (!priorityHeap.empty()) {
        auto top = priorityHeap.top();
        int id = top.second;
        if (taskMap.find(id) == taskMap.end() || taskMap[id].done) {
            priorityHeap.pop();
            continue;
        }
        Task &t = taskMap[id];
        cout << "Next priority task -> ID: " << t.id << " | " << t.name
             << " | Priority: " << t.priority << " | Deadline: " << t.deadline << "\n";
        return;
    }
    cout << "No pending tasks.\n";
}

void viewAllSortedByDeadline() {
    vector<Task> tasks;
    for (auto &p : taskMap) tasks.push_back(p.second);

    sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.deadline < b.deadline; // ascending, earliest deadline first
    });

    cout << "\n----- Tasks sorted by deadline -----\n";
    for (auto &t : tasks) {
        cout << t.id << ". " << t.name << " [" << t.category << "] "
             << "P" << t.priority << " | Due: " << t.deadline
             << " | " << (t.done ? "Done" : "Pending") << "\n";
    }
    if (tasks.empty()) cout << "No tasks available.\n";
}

void undoLastAction() {
    if (undoStack.empty()) {
        cout << "Nothing to undo.\n";
        return;
    }
    Action last = undoStack.top();
    undoStack.pop();

    if (last.type == "ADD") {
        taskMap.erase(last.task.id);
        cout << "Undo: removed task " << last.task.id << " (" << last.task.name << ")\n";
    } else if (last.type == "DELETE") {
        taskMap[last.task.id] = last.task;
        priorityHeap.push({last.task.priority, last.task.id});
        cout << "Undo: restored task " << last.task.id << " (" << last.task.name << ")\n";
    }
}

void markDone() {
    int id;
    cout << "Enter task ID to mark done: ";
    cin >> id;
    if (taskMap.find(id) == taskMap.end()) {
        cout << "Task not found.\n";
        return;
    }
    taskMap[id].done = true;
    cout << "Task " << id << " marked as done.\n";
}

// ---------------------------------------------------------------
// SECTION 4: FILE PERSISTENCE
// ---------------------------------------------------------------
void saveToFile() {
    ofstream fout("tasks.txt");
    for (auto &p : taskMap) {
        Task &t = p.second;
        fout << t.id << "|" << t.name << "|" << t.category << "|"
             << t.priority << "|" << t.deadline << "|" << t.done << "\n";
    }
    fout.close();
    cout << "Tasks saved to tasks.txt\n";
}

void loadFromFile() {
    ifstream fin("tasks.txt");
    if (!fin) {
        cout << "No saved file found.\n";
        return;
    }
    taskMap.clear();
    while (!priorityHeap.empty()) priorityHeap.pop();

    string line;
    int maxId = 0;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string field;
        Task t;
        getline(ss, field, '|'); t.id = stoi(field);
        getline(ss, t.name, '|');
        getline(ss, t.category, '|');
        getline(ss, field, '|'); t.priority = stoi(field);
        getline(ss, t.deadline, '|');
        getline(ss, field, '|'); t.done = (field == "1");

        taskMap[t.id] = t;
        priorityHeap.push({t.priority, t.id});
        maxId = max(maxId, t.id);
    }
    nextId = maxId + 1;
    fin.close();
    cout << "Tasks loaded from tasks.txt\n";
}

// ---------------------------------------------------------------
// SECTION 5: MENU DRIVEN INTERFACE
// ---------------------------------------------------------------
void showMenu() {
    cout << "\n===== SMART TASK MANAGEMENT SYSTEM =====\n";
    cout << "1. Add Task\n";
    cout << "2. Delete Task\n";
    cout << "3. Search Task by ID\n";
    cout << "4. Get Next Priority Task\n";
    cout << "5. View All Tasks (sorted by deadline)\n";
    cout << "6. Mark Task as Done\n";
    cout << "7. Undo Last Action\n";
    cout << "8. Save Tasks to File\n";
    cout << "9. Load Tasks from File\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1: addTask(); break;
            case 2: deleteTask(); break;
            case 3: searchTaskById(); break;
            case 4: getNextPriorityTask(); break;
            case 5: viewAllSortedByDeadline(); break;
            case 6: markDone(); break;
            case 7: undoLastAction(); break;
            case 8: saveToFile(); break;
            case 9: loadFromFile(); break;
            case 0: cout << "Exiting. Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
