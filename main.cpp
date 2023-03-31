#include <iostream>
#include <string>
#include "Queue/Queue.hpp"
#include "Process/Process.hpp"

using namespace std;

int main()
{
    Queue<int> *q = new Queue<int>();
    Process *p = new Process(5, 50);

    cout << p->GetEnteringTime();
    cout << p->GetDurationTime();

    return 0;
}