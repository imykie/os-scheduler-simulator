#pragma once
#include <string>

#include "timestamp_topic.h"

class TimeStamp : public TimeStampTopic {
   public:
    TimeStamp();
    TimeStamp(std::string topic_name);
    void IncreaseTime(float delta);
    float GetCurrentTime();
    float GetMessage() override;

   private:
    float time;
    float lastTimeIncreased;
};