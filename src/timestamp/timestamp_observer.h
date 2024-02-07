#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "timestamp.h"
#include "timestamp_interface.h"

class TimestampObserver : public Observer<float> {
   public:
    TimestampObserver(Timestamp* sender);
    ~TimestampObserver();
    void Update(float delta, std::string topic_name) override;
    void SetID(int id) override;
    int GetID() override;
    void UnsubscribeFromEvent();

   protected:
    Timestamp* sender;

   private:
    void SubscribeToEvent();
};