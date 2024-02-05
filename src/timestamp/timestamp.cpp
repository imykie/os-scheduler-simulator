#include "timestamp.h"

TimeStamp::TimeStamp() { time = 0; }
TimeStamp::TimeStamp(std::string topic_name) {
    time = 0;
    this->SetName(topic_name);
}

float TimeStamp::GetCurrentTime() { return time; }

void TimeStamp::IncreaseTime(float delta) {
    time += delta;
    lastTimeIncreased = delta;
    this->NotifyObservers();
}

float TimeStamp::GetMessage() { return lastTimeIncreased; }