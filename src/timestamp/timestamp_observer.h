#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "timestamp.h"
#include "timestamp_interface.h"

class TimeStampObserver : public Observer<float> {
   public:
    TimeStampObserver(TimeStamp* sender);
    ~TimeStampObserver();
    void Update(float delta, std::string topic_name) override;
    void SetID(int id) override;
    int GetID() override;
    void UnsubscribeFromEvent();

   protected:
    TimeStamp* sender;

   private:
    void SubscribeToEvent();
};