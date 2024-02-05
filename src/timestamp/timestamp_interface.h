#pragma once

template <typename T>
class Observer {
   public:
    virtual void Update(T delta, std::string topic_name) = 0;
    virtual void SetID(int id) = 0;
    virtual int GetID() = 0;

   protected:
    int id;
};

template <typename T>
class Topic {
   public:
    virtual void AddObserver(Observer<T> *observer) = 0;
    virtual void RemoveObserver(Observer<T> *observer) = 0;
    virtual int GetObserversSize() = 0;

   protected:
    virtual T GetMessage() = 0;
    virtual void NotifyObservers() = 0;
};