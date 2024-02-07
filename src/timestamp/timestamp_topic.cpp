#include "timestamp_topic.h"

void TimestampTopic::AddObserver(Observer<float>* observer) {
    observers.push_back(observer);
    observer->SetID(observers.size());
}

void TimestampTopic::RemoveObserver(Observer<float>* observer) {
    for (int i = 0; i < observers.size(); i++) {
        if (observers[i] == observer) {
            observers.erase(observers.begin() + i);
            return;
        }
    }
}

int TimestampTopic::GetObserversSize() { return observers.size(); }

void TimestampTopic::SetName(std::string name) { this->name = name; }

std::string TimestampTopic::GetName() { return name; }

void TimestampTopic::NotifyObservers() {
    float msg = GetMessage();

    for (int i = 0; i < observers.size(); i++) {
        observers[i]->Update(msg, name);
    }
}
