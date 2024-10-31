#include <iostream>
#include <string>
using namespace std;

template<typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node() : data(0), next(nullptr) {}
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insertAtEnd(T const element) {
        Node* nod = new Node(element);
        if (head == nullptr) {
            head = nod;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nod;
    }

    void print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << "\t";
            temp = temp->next;
        }
        cout << endl;
    }

    bool search(T const element) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == element) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    T middleValue() {
        if (head == nullptr)
            throw runtime_error("List is empty");
        Node* rabbit = head;
        Node* tortise = head;
        while (rabbit != nullptr && rabbit->next != nullptr) {
            rabbit = rabbit->next->next;
            tortise = tortise->next;
        }
        return tortise->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    bool deleteAll(T const value) {
        if (head == nullptr) return false;

        bool deleted = false;
        Node* temp;

        // Remove nodes at the beginning with matching value
        while (head != nullptr && head->data == value) {
            temp = head;
            head = head->next;
            delete temp;
            deleted = true;
        }

        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == value) {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
                deleted = true;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }

        return deleted;
    }

    void sort() {
        if (head == nullptr || head->next == nullptr) return;
        Node* sorted = head;
        for (; sorted->next != nullptr; sorted = sorted->next) {
            Node* min = sorted;
            for (Node* curr = sorted->next; curr != nullptr; curr = curr->next) {
                if (curr->data < min->data) {
                    min = curr;
                }
            }
            if (min != sorted) {
                T temp = sorted->data;
                sorted->data = min->data;
                min->data = temp;
            }
        }
    }
};

class ToDoApp {
private:
    LinkedList<string> tasks;

public:
    void displayMenu() {
        cout << "\n=== To-Do App Menu ===" << endl;
        cout << "1. Add a Task" << endl;
        cout << "2. Delete a Task" << endl;
        cout << "3. Display All Tasks" << endl;
        cout << "4. Search for a Task" << endl;
        cout << "5. Reverse Task List" << endl;
        cout << "6. Delete All Tasks with Specific Content" << endl;
        cout << "7. Sort Tasks" << endl;
        cout << "8. Display Middle Task" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void addTask() {
        cout << "Enter task to add: ";
        string task;
        cin.ignore();
        getline(cin, task);
        tasks.insertAtEnd(task);
        cout << "Task added successfully.\n";
    }

    void deleteTask() {
        cout << "Enter task to delete: ";
        string task;
        cin.ignore();
        getline(cin, task);
        if (tasks.deleteAll(task)) {
            cout << "Task deleted successfully.\n";
        }
        else {
            cout << "Task not found.\n";
        }
    }

    void displayTasks() {
        cout << "Current Tasks:" << endl;
        tasks.print();
    }

    void searchTask() {
        cout << "Enter task to search for: ";
        string task;
        cin.ignore();
        getline(cin, task);
        if (tasks.search(task)) {
            cout << "Task found." << endl;
        }
        else {
            cout << "Task not found." << endl;
        }
    }

    void reverseTasks() {
        tasks.reverse();
        cout << "Tasks reversed successfully.\n";
    }

    void deleteSpecificTasks() {
        cout << "Enter the content of tasks to delete: ";
        string content;
        cin.ignore();
        getline(cin, content);
        if (tasks.deleteAll(content)) {
            cout << "Tasks with content \"" << content << "\" deleted.\n";
        }
        else {
            cout << "No tasks found with content \"" << content << "\".\n";
        }
    }

    void sortTasks() {
        tasks.sort();
        cout << "Tasks sorted successfully.\n";
    }

    void displayMiddleTask() {
        try {
            cout << "Middle Task: " << tasks.middleValue() << endl;
        }
        catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }

    void run() {
        int choice;
        do {
            displayMenu();
            cin >> choice;

            switch (choice) {
            case 1: addTask(); break;
            case 2: deleteTask(); break;
            case 3: displayTasks(); break;
            case 4: searchTask(); break;
            case 5: reverseTasks(); break;
            case 6: deleteSpecificTasks(); break;
            case 7: sortTasks(); break;
            case 8: displayMiddleTask(); break;
            case 9: cout << "Exiting To-Do App. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 9);
    }
};

int main() {
    ToDoApp app;
    app.run();
    return 0;
}
