#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

// Abstract class Observer, which defines the interface for observers
class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(const std::string& message) = 0; // Method for receiving messages
};

// Class Subject, which contains a list of observers and methods for managing them
class Subject {
public:
    // Method for adding an observer
    void Attach(std::shared_ptr<Observer> new_observer) {
        observers.push_back(new_observer);
        std::cout << "Attached an observer.\n";
    }

    // Method for removing an observer
    void Detach(std::shared_ptr<Observer> detached_observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), detached_observer), observers.end());
        std::cout << "Detached an observer.\n";
    }

    // Method for notifying all observers
    void Notify(const std::string& message) {
        std::cout << "Notifying observers...\n";
        for (const auto& observer : observers) {
            observer->Update(message);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers; // List of observers
};

// Concrete observer class that implements the Update method
class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const std::string& new_name) : name(new_name) {}

    // Method for receiving messages from the subject
    void Update(const std::string& message) override {
        std::cout << "Observer " << name << " received message: " << message << std::endl;
    }

private:
    std::string name; // Observer's name
};

int main() {
    Subject subject; // Create a subject

    // Create observers
    auto observer1 = std::make_shared<ConcreteObserver>("Observer1");
    auto observer2 = std::make_shared<ConcreteObserver>("Observer2");

    // Add observers to the subject
    subject.Attach(observer1);
    subject.Attach(observer2);

    // Notify observers
    subject.Notify("First Message");

    // Remove one observer
    subject.Detach(observer2);

    // Notify observers again
    subject.Notify("Second Message");

    return 0;
}