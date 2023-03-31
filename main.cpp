#include <iostream>
#include <string>
#include "Queue/Queue.hpp"
#include "Process/Process.hpp"

using namespace std;

int main()
{
    Queue<int> *q = new Queue<int>();
    Process *p = new Process();

    cout << p->GetEnteringTime();

    return 0;
}