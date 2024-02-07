#pragma once
#include <string>
#include <vector>

#include "timestamp_interface.h"

class TimestampTopic : public Topic<float> {
   public:
    void AddObserver(Observer<float>* observer) override;
    void RemoveObserver(Observer<float>* observer) override;
    int GetObserversSize() override;
    void SetName(std::string name);
    std::string GetName();

   protected:
    void NotifyObservers() override;

   private:
    std::vector<Observer<float>*> observers;
    std::string name;
};