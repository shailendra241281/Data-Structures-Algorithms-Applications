/*
=====================================================================
 INVENTORY & BILLING SYSTEM
=====================================================================
 DSA Concepts Used:
   1. Hash Map (unordered_map)   -> O(1) stock lookup by SKU
   2. Queue                      -> orders processed in FIFO order
   3. Stack                      -> cancel the last billed item
   4. Min-Heap (priority_queue)  -> low-stock alert (smallest qty first)
   5. Sorting (custom comparator)-> sales report ranked by revenue
=====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------
// SECTION 1: DATA MODEL
// ---------------------------------------------------------------
struct Item {
    string sku;
    string name;
    double price;
    int quantity;
    int unitsSold;
};

struct Order {
    string sku;
    int qty;
};

struct BillLine {
    string sku;
    string name;
    int qty;
    double lineTotal;
};

// ---------------------------------------------------------------
// SECTION 2: GLOBAL STORAGE
// ---------------------------------------------------------------
unordered_map<string, Item> inventory;   // sku -> Item (Hash Map)
queue<Order> orderQueue;                 // pending orders (Queue - FIFO)
stack<BillLine> currentBillStack;        // items in the active bill (Stack)
double currentBillTotal = 0.0;

// ---------------------------------------------------------------
// SECTION 3: CORE OPERATIONS
// ---------------------------------------------------------------
void addOrUpdateStock() {
    Item it;
    cout << "Enter SKU: ";
    cin >> it.sku;

    if (inventory.find(it.sku) != inventory.end()) {
        // update existing stock
        cout << "Item exists. Enter quantity to add: ";
        int addQty;
        cin >> addQty;
        inventory[it.sku].quantity += addQty;
        cout << "Stock updated. New quantity: " << inventory[it.sku].quantity << "\n";
        return;
    }

    cin.ignore();
    cout << "Enter item name: ";
    getline(cin, it.name);
    cout << "Enter price: ";
    cin >> it.price;
    cout << "Enter quantity: ";
    cin >> it.quantity;
    it.unitsSold = 0;

    inventory[it.sku] = it;
    cout << "Item added to inventory.\n";
}

void placeOrder() {
    Order o;
    cout << "Enter SKU to order: ";
    cin >> o.sku;
    cout << "Enter quantity: ";
    cin >> o.qty;

    if (inventory.find(o.sku) == inventory.end()) {
        cout << "SKU not found in inventory.\n";
        return;
    }
    orderQueue.push(o);
    cout << "Order placed and added to processing queue.\n";
}

void processNextOrder() {
    if (orderQueue.empty()) {
        cout << "No pending orders.\n";
        return;
    }
    Order o = orderQueue.front();
    orderQueue.pop();

    auto it = inventory.find(o.sku);
    if (it == inventory.end()) {
        cout << "Item no longer exists in inventory. Skipping order.\n";
        return;
    }
    Item &item = it->second;
    if (item.quantity < o.qty) {
        cout << "Insufficient stock for " << item.name
             << ". Available: " << item.quantity << ". Order skipped.\n";
        return;
    }

    item.quantity -= o.qty;
    item.unitsSold += o.qty;
    double lineTotal = item.price * o.qty;
    currentBillTotal += lineTotal;

    BillLine bl{item.sku, item.name, o.qty, lineTotal};
    currentBillStack.push(bl);

    cout << "Processed: " << o.qty << " x " << item.name
         << " = " << fixed << setprecision(2) << lineTotal << "\n";
    cout << "Running bill total: " << currentBillTotal << "\n";
}

void cancelLastBilledItem() {
    if (currentBillStack.empty()) {
        cout << "No billed items to cancel.\n";
        return;
    }
    BillLine last = currentBillStack.top();
    currentBillStack.pop();

    // restore stock
    auto it = inventory.find(last.sku);
    if (it != inventory.end()) {
        it->second.quantity += last.qty;
        it->second.unitsSold -= last.qty;
    }
    currentBillTotal -= last.lineTotal;

    cout << "Cancelled: " << last.qty << " x " << last.name
         << ". Bill total now: " << fixed << setprecision(2) << currentBillTotal << "\n";
}

void printCurrentBill() {
    if (currentBillStack.empty()) {
        cout << "No items billed yet.\n";
        return;
    }
    // copy stack to display without destroying it
    stack<BillLine> temp = currentBillStack;
    vector<BillLine> lines;
    while (!temp.empty()) {
        lines.push_back(temp.top());
        temp.pop();
    }
    reverse(lines.begin(), lines.end());

    cout << "\n----- CURRENT BILL -----\n";
    for (auto &bl : lines) {
        cout << bl.name << " x" << bl.qty << " = "
             << fixed << setprecision(2) << bl.lineTotal << "\n";
    }
    cout << "TOTAL: " << fixed << setprecision(2) << currentBillTotal << "\n";
}

void lowStockAlert() {
    int threshold;
    cout << "Enter low-stock threshold: ";
    cin >> threshold;

    // Min-Heap: {quantity, sku-index} smallest quantity surfaces first
    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> minHeap;

    for (auto &p : inventory) {
        minHeap.push({p.second.quantity, p.second.sku});
    }

    cout << "\n----- LOW STOCK ALERT (below " << threshold << ") -----\n";
    bool any = false;
    while (!minHeap.empty()) {
        auto top = minHeap.top();
        minHeap.pop();
        if (top.first >= threshold) break; // rest are all higher, min-heap sorted ascending
        Item &item = inventory[top.second];
        cout << item.name << " (SKU " << item.sku << ") - Qty left: " << item.quantity << "\n";
        any = true;
    }
    if (!any) cout << "All items are sufficiently stocked.\n";
}

void salesReportByRevenue() {
    vector<Item> items;
    for (auto &p : inventory) items.push_back(p.second);

    // Sorting: rank items by revenue generated (price * unitsSold), descending
    sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        return (a.price * a.unitsSold) > (b.price * b.unitsSold);
    });

    cout << "\n----- SALES REPORT (by revenue) -----\n";
    for (auto &it : items) {
        double revenue = it.price * it.unitsSold;
        cout << it.name << " - Units sold: " << it.unitsSold
             << " | Revenue: " << fixed << setprecision(2) << revenue << "\n";
    }
    if (items.empty()) cout << "No inventory data available.\n";
}

// ---------------------------------------------------------------
// SECTION 4: MENU DRIVEN INTERFACE
// ---------------------------------------------------------------
void showMenu() {
    cout << "\n===== INVENTORY & BILLING SYSTEM =====\n";
    cout << "1. Add / Update Stock\n";
    cout << "2. Place Order\n";
    cout << "3. Process Next Order (from queue)\n";
    cout << "4. Cancel Last Billed Item\n";
    cout << "5. Print Current Bill\n";
    cout << "6. Low Stock Alert\n";
    cout << "7. Sales Report (by revenue)\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1: addOrUpdateStock(); break;
            case 2: placeOrder(); break;
            case 3: processNextOrder(); break;
            case 4: cancelLastBilledItem(); break;
            case 5: printCurrentBill(); break;
            case 6: lowStockAlert(); break;
            case 7: salesReportByRevenue(); break;
            case 0: cout << "Exiting. Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
