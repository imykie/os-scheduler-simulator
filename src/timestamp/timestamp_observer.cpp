#include "timestamp_observer.h"

TimestampObserver::TimestampObserver(Timestamp *sender) {
    this->sender = sender;
    SubscribeToEvent();
}

TimestampObserver::~TimestampObserver() {
    UnsubscribeFromEvent();
    delete sender;
    sender = nullptr;
}

void TimestampObserver::Update(float delta, std::string topic_name) {
    std::ostringstream msg;
    if (!topic_name.empty()) {
        msg << "[Topic Name]: " << topic_name << ", ";
    }
    msg << "[Observer ID]: " << GetID() << ", ";
    msg << "[Received]: " << delta;
    std::cout << msg.str() << std::endl;
}

void TimestampObserver::SetID(int id) { this->id = id; }

int TimestampObserver::GetID() { return id; }

void TimestampObserver::SubscribeToEvent() {
    if (this->sender != nullptr) {
        sender->AddObserver(this);
    }
}

void TimestampObserver::UnsubscribeFromEvent() {
    if (this->sender != nullptr) {
        sender->RemoveObserver(this);
    }
}