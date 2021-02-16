#include <iostream>
#include <algorithm>
using namespace std;

int fullyEmpty[5];
int waitingLine[5];

void taramaEmpty()
{

    int count = 0;
    int capacity = 30;
    for (int i = 0; i < 5; i++)
    {
        cin >> fullyEmpty[i];
        cout << "Capacity now = " << capacity - fullyEmpty[i] << endl;
        capacity -= fullyEmpty[i];
        if (fullyEmpty[i] > 10)
        {
            cout << "Invalid: Max 10 members in a group only";
            break;
        }
        if (fullyEmpty[i] == 10)
        {
            count++;
            if (count > 1)
            {
                cout << "Invalid: Only once 10 member group can occur";
                break;
            }
        }
    }
    cout << "\nEnjoy your meal" << endl;
}

void inputCheck()
{

    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        cin >> waitingLine[i];
        if (waitingLine[i] > 10)
        {
            cout << "Invalid: Max 10 members in a group only";
            break;
        }
        if (waitingLine[i] == 10)
        {
            count++;
            if (count > 1)
            {
                cout << "Invalid: Only once 10 member group can occur";
                break;
            }
        }
    }
    cout << "\nPlease wait patiently we shall optimise your waiting time" << endl;
}

void scheduleCheck()
{
    // cout << "\nTiming Schedule:\n1. 30 - 5 = 25\n2. 25 - 10 = 15\n3. 15 - 2 = 13\n4. 13 - 5 = 8\n5. 8 - 8 = 0\n";
    int capacity = 30;
    for (int i = 0; i < 5; i++)
    {
        int vacant = fullyEmpty[i];
        cout << "Vacancy = " << vacant << endl;
        capacity -= fullyEmpty[i];
        cout << "Capacity = " << capacity << endl
             << endl;
        for (int i = 0; i < 5; i++)
        {
            if (waitingLine[i] <= vacant && waitingLine[i] > 0)
            {
                capacity += waitingLine[i];
                cout << "Inserted = " << waitingLine[i] << endl;
                waitingLine[i] = -1;
            }
        }
    }
}

int main()
{
    // Max Capacity : 30
    cout << "\nWelcome to Tarama!\nLet's fill the empty restaurant" << endl;

    // Assuming time unit(Burst Time) = 1
    taramaEmpty();
    cout << "\nWelcome to Tarama!\nLet's start the waiting line" << endl;
    inputCheck();

    sort(fullyEmpty, fullyEmpty + 5);
    scheduleCheck();
    return 0;
}