#include <iostream>
#include <algorithm>
using namespace std;

int insideTarama[30];
int inQueue[6];
int lenInsideTarama = 0;
int extra;
int lenInQueue;


int minInQueue()
{
    for (int i = 0; i < lenInQueue ; i ++)
    {
        if (inQueue[i] != -1)
            return inQueue[i];
    }
}

int taramaEmpty()
{
    int count = 0;
    int capacity = 30;
    for (int i = 0; i < 30; i++)
    {
        if(capacity > 0)
        {
            cin >> insideTarama[i];
            cout << "Available Capacity = " << capacity - insideTarama[i] << endl;
            capacity -= insideTarama[i];
            if(capacity <= 0)
            {
                cout<<"Sorry, Tarama is full, adding you Queue. "<<endl;

                if (capacity < 0)
                {
                    extra = insideTarama[i];
                    insideTarama[i] = {};
                }
                else
                {
                    extra = 0;
                    lenInsideTarama++;
                }
                break;
            }
            else
            {
                extra = 0;
                lenInsideTarama++;
            }
            if (insideTarama[i] > 10)
            {
                cout << "Sorry: Tarama doesn't allow groups above 10, please visit in smaller groups.";
                return -1;
            }
            if (insideTarama[i] == 10)
            {
                count++;
                if (count > 1)
                {
                    cout << "Sorry: Tarama doesn't allow only single group with 10, please visit in smaller groups.";
                    return -1;
                }
            }
        }
        else
        {

            cout<<"Now it is complete";
            break;
        }
    }

    sort(insideTarama, insideTarama + lenInsideTarama);
    cout << "\nEnjoy your meal" << endl;
    return 0;
}

int inputCheck()
{

    int count = 0;
    if(extra != 0)
    {
        lenInQueue = 6;
        inQueue[0] = extra;
        for (int i = 1; i < 6; i++)
        {
            cin >> inQueue[i];
            if (inQueue[i] > 10)
            {
                cout << "Sorry: Tarama doesn't allow groups above 10, please visit in smaller groups.";
                return -1;
            }
            if (inQueue[i] == 10)
            {
                count++;
                if (count > 1)
                {
                    cout << "Sorry: Tarama doesn't allow only single group with 10, please visit in smaller groups.";
                    return -1;
                }
            }
        }
    }
        else
        {
            lenInQueue = 5;
            for (int i = 0; i < 5; i++)
            {
                cin >> inQueue[i];
                if (inQueue[i] > 10)
                {
                    cout << "Sorry: Tarama doesn't allow groups above 10, please visit in smaller groups.";
                    return -1;
                }
                if (inQueue[i] == 10)
                {
                    count++;
                    if (count > 1)
                    {
                        cout << "Sorry: Tarama doesn't allow only single group with 10, please visit in smaller groups.";
                        return -1;
                    }
                }
            }
        }
    sort(inQueue, inQueue + lenInQueue);
    cout << "\nPlease wait patiently we shall optimize your waiting time" << endl;
    return 0;
}

void scheduleCheck()
{
    for(int i=0; i<lenInsideTarama; i++)
        cout<<insideTarama[i]<<" ";
    cout<<endl;
    for(int i=0; i<lenInQueue; i++)
        cout<<inQueue[i]<<" ";
    cout<<endl;
    int sum = 0;

    for(int i=0; i<lenInsideTarama; i++)
        sum += insideTarama[i];

    int vacancy = 30 - sum;
    cout<<"Initial Vacancy: "<<vacancy<<endl<<endl;
    int k = 0;
    int inserted;
    int k1 = 0;
    while(k1 <= lenInQueue)
    {
        sort(insideTarama, insideTarama + lenInsideTarama);
        for(int p=0; p < lenInQueue; p++)
            cout<<inQueue[p]<<"  ";
        cout<<endl;
        for(int p=0; p<lenInsideTarama; p++)
            cout<<insideTarama[p]<<"  ";
        cout<<endl;
        int mm = 0;
        for (mm = 0; mm < lenInQueue; mm++)
            if (inQueue[mm] != -1)
                break;

        if (mm == lenInQueue) // All waitingList processed
            break;

        int minW = minInQueue();
        cout<<"minW = "<<minW<<endl;

        int a = 0;
        for (a = 0; a < lenInsideTarama; a++)
        {
            if (vacancy < minW || vacancy == 0)
            {
                vacancy += insideTarama[a];
            }
            else
            {
                a--;
                insideTarama[a] = 0;
                break;
            }
        }

        cout<<"a: "<<a<<endl;
        cout<<"Vacancy: "<<vacancy<<endl;
        int x = 0;
        int y = lenInQueue-1;

        // Check if vacancy exactly matches any element of inQueue
        int t = 0;
        for(t = 0; t < lenInQueue; t++)
        {
            if(vacancy == inQueue[t])
            {
                vacancy = 0;
                cout<<"inserted: "<<inQueue[t]<<endl;
                cout<<"New vacancy: "<<vacancy<<endl;
                inserted = inQueue[t];
                inQueue[t] = -1;
                insideTarama[a] = inserted;
                break;
            }
        }

        if (t < lenInQueue) // vacancy exactly matched with an element of inQueue
            continue;

        while(x <= y)
        {
            if (inQueue[x] == -1)
                x++;

            if (inQueue[y] == -1)
                y--;

            if(x == y)
            {
                vacancy -= inQueue[x];
                cout<<"inserted: "<<inQueue[x]<<endl;
                cout<<"New Vacancy: "<<vacancy<<endl;
                insideTarama[a] = inQueue[y];
                inQueue[x] = -1;
                break;
            }

            if(vacancy == inQueue[x] + inQueue[y])
            {
                vacancy = 0;
                cout<<"New Vacancy: "<<vacancy<<endl;
                cout<<"inserted: "<<inQueue[x]<<" and "<<inQueue[y]<<endl;
                if (a == 0)
                {
                    insideTarama[lenInsideTarama] = inQueue[x];
                    lenInsideTarama++;
                    sort(insideTarama, insideTarama + lenInsideTarama);
                }
                else
                    insideTarama[a-1] = inQueue[x];

                insideTarama[a] = inQueue[y];
                inQueue[x] = -1;
                inQueue[y] = -1;
                break;
            }
            else if(vacancy > inQueue[x] + inQueue[y])
            {
                x++;
            }
            else if(vacancy < inQueue[x] + inQueue[y])
            {
                y--;
            }
        }
        k1++;
    }
}


int main()
{
    // Max Capacity : 30
    cout << "\nWelcome to Tarama!\nLet's fill the empty restaurant" << endl;

    // Assuming time unit(Burst Time) = 1
    if (taramaEmpty() != -1)
    {
        cout << "\nWelcome to Tarama!\nLet's start the waiting queue" << endl;
        if (inputCheck() != -1)
            scheduleCheck();
    }

    return 0;
}
