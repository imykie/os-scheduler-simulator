#include "timestamp_topic.h"

void TimeStampTopic::AddObserver(Observer<float>* observer) {
    observers.push_back(observer);
    observer->SetID(observers.size());
}

void TimeStampTopic::RemoveObserver(Observer<float>* observer) {
    for (int i = 0; i < observers.size(); i++) {
        if (observers[i] == observer) {
            observers.erase(observers.begin() + i);
            return;
        }
    }
}

int TimeStampTopic::GetObserversSize() { return observers.size(); }

void TimeStampTopic::SetName(std::string name) { this->name = name; }

std::string TimeStampTopic::GetName() { return name; }

void TimeStampTopic::NotifyObservers() {
    float msg = GetMessage();

    for (int i = 0; i < observers.size(); i++) {
        observers[i]->Update(msg, name);
    }
}
