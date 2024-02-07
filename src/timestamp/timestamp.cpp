#include "timestamp.h"

Timestamp::Timestamp() { time = 0; }
Timestamp::Timestamp(std::string topic_name) {
    time = 0;
    this->SetName(topic_name);
}

float Timestamp::GetCurrentTime() { return time; }

void Timestamp::IncreaseTime(float delta) {
    time += delta;
    lastTimeIncreased = delta;
    this->NotifyObservers();
}

float Timestamp::GetMessage() { return lastTimeIncreased; }