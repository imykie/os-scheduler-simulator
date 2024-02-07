#include "timestamp_observer.h"

TimeStampObserver::TimeStampObserver(TimeStamp *sender) {
    this->sender = sender;
    SubscribeToEvent();
}

TimeStampObserver::~TimeStampObserver() { UnsubscribeFromEvent(); }

void TimeStampObserver::Update(float delta, std::string topic_name) {
    std::ostringstream msg;
    if (!topic_name.empty()) {
        msg << "[Topic Name]: " << topic_name << ", ";
    }
    msg << "[Observer ID]: " << GetID() << ", ";
    msg << "[Received]: " << delta;
    std::cout << msg.str() << std::endl;
}

void TimeStampObserver::SetID(int id) { this->id = id; }

int TimeStampObserver::GetID() { return id; }

void TimeStampObserver::SubscribeToEvent() {
    if (this->sender != nullptr) {
        sender->AddObserver(this);
    }
}

void TimeStampObserver::UnsubscribeFromEvent() {
    if (this->sender != nullptr) {
        sender->RemoveObserver(this);
    }
}