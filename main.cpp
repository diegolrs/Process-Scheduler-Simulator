#include <iostream>
#include <string>
#include "Queue/Queue.hpp"

using namespace std;

int main()
{
    Queue<int> *q = new Queue<int>();

    for(int i = 0; i <= 50; i++)
        q->Enqueue(i);

    for(int i = 0; i <= 50; i++)
        cout << q->Dequeue() << " ";

    return 0;
}