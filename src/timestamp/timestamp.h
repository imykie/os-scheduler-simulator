#pragma once
#include <string>

#include "Timestamp_topic.h"

class Timestamp : public TimestampTopic {
   public:
    Timestamp();
    Timestamp(std::string topic_name);
    void IncreaseTime(float delta);
    float GetCurrentTime();
    float GetMessage() override;

   private:
    float time;
    float lastTimeIncreased;
};