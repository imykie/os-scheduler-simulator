#include <iostream>

#include "data_structures/process.h"
#include "data_structures/queue.h"

using namespace std;

int main() {
    Process p = Process(1, 1, 1, 1, 1);
    cout << p.ToString() << endl;

    Queue<int> *q = new Queue<int>();
    q->Enqueue(1);
    q->Enqueue(2);
    cout << q->Peek() << endl;
    q->Dequeue();
    q->Enqueue(3);
    q->Enqueue(4);
    cout << q->Length() << endl;
    cout << q->Peek() << endl;
    q->Dequeue();
    cout << q->Length() << endl;

    return 0;
}