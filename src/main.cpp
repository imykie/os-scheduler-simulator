#include <iostream>
#include "data_structures/process.h"

using namespace std;

int main() {
    Process p = Process(1, 1, 1, 1, 1);
    cout << p.ToString() << endl;
    return 0;
}