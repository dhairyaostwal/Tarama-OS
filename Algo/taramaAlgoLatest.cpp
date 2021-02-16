#include <iostream>
#include <algorithm>
using namespace std;

int insideTarama[30];
int inQueue[6];
int lenInsideTarama = 0;
int extra;
int lenInQueue;
int currentstatus[30];


int minInQueue()
{
    for (int i = 0; i < lenInQueue ; i ++)
    {
        if (inQueue[i] != -1)
            return inQueue[i];
    }
}
int mincurrentstatus()
{
    for(int i=0; i<lenInsideTarama; i++)
    {
        if(currentstatus[i] != 0)
            return currentstatus[i];
    }
}
int maxInQueue()
{
    for(int i=lenInQueue-1; i>=0; i--)
    {
        if(inQueue[i] != -1)
            return inQueue[i];
    }
}
int indexofmaxInQueue()
{
    for(int i=lenInQueue-1; i>=0; i--)
    {
        if(inQueue[i] != -1)
            return i;
    }
}
int max2InQueue()
{
    int c=0;
    for(int i=lenInQueue-1; i>=0; i--)
    {
        if(inQueue[i] != -1)
        {
            c++;
            if(c == 2)
                return inQueue[i];
        }
    }
}
int indexofmax2InQueue()
{
    int c=0;
    for(int i=lenInQueue-1; i>=0; i--)
    {
        if(inQueue[i] != -1)
        {
            c++;
            if(c == 2)
                return i;
        }
    }
}
int max3InQueue()
{
    int c=0;
    for(int i=lenInQueue-1; i>=0; i--)
    {
        if(inQueue[i] != -1)
        {
            c++;
            if(c == 3)
                return inQueue[i];
        }
    }
}
void BubbleSort (int arr[], int arr1[], int n)
{
	int i, j;
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n-i-1; ++j)
		{
			// Comparing consecutive data and switching values if value at j > j+1.
			if (arr[j] > arr[j+1])
			{
				arr[j] = arr[j]+arr[j+1];
				arr[j+1] = arr[j]-arr[j + 1];
				arr[j] = arr[j]-arr[j + 1];

				arr1[j] = arr1[j]+arr1[j+1];
				arr1[j+1] = arr1[j]-arr1[j + 1];
				arr1[j] = arr1[j]-arr1[j + 1];
			}
		}
		// Value at n-i-1 will be maximum of all the values below this index.
	}
}
int noofneg()
{
    int c = 0;
    for(int i=0; i<lenInQueue; i++)
    {
        if(inQueue[i] == -1)
            c++;
    }
    return c++;
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
        currentstatus[i] = insideTarama[i];
    cout<<endl<<"Current Status: "<<endl;
    for(int i=0; i<lenInsideTarama; i++)
        cout<<currentstatus[i]<<"  ";
    cout<<endl;
    for(int i=0; i<lenInsideTarama; i++)
        sum += insideTarama[i];

    int vacancy = 30 - sum;
    cout<<"Initial Vacancy: "<<vacancy<<endl<<endl;
    int k = 0;
    int inserted;
    int k1 = 0;
    while(1)
    {
        BubbleSort(insideTarama, currentstatus, lenInsideTarama);
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

        if (mm == lenInQueue)
        {
            break;
        }


        int minW = minInQueue();

        int a = 0;
        int temp;
        for (a = 0; a < lenInsideTarama; a++)
        {
            if (vacancy < minW || vacancy == 0)
            {
                // += insideTarama[a];
                temp = mincurrentstatus();
                for(int z=0; z<lenInsideTarama; z++)
                {
                    if(currentstatus[z] -temp > 0)
                    {
                        currentstatus[z] -= temp;
                    }
                    else
                    {
                        currentstatus[z] = 0;
                    }
                    cout<<currentstatus[z]<<"  ";
                }
                cout<<endl;
                for(int z=0; z<lenInsideTarama; z++)
                {
                    if(currentstatus[z] == 0)
                    {
                        cout<<"Vacancy = "<<vacancy<<" + "<<insideTarama[z]<<"  "<<endl;
                        vacancy += insideTarama[z];
                        insideTarama[z] = 0;
                    }
                }
            }
            else
            {
                a--;
                insideTarama[a] = 0;
                break;
            }
        }

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
                if(a < 0)
                    a = 0;
                insideTarama[a] = inQueue[t];
                currentstatus[a] = inQueue[t];
                cout<<"currentstatus[a]: "<<currentstatus[a]<<endl;
                inQueue[t] = -1;
                cout<<endl<<"People inside Tarama: "<<endl;
                for(int z=0; z<lenInsideTarama; z++)
                {
                    cout<<insideTarama[z]<<"  ";
                }
                cout<<endl<<"Current status right now: "<<endl;
                for(int z=0; z<lenInsideTarama; z++)
                {
                    cout<<currentstatus[z]<<"  ";
                }
                cout<<endl;
                cout<<endl<<"Queue outside Tarama: "<<endl;
                for(int z=0; z<lenInQueue; z++)
                {
                    cout<<inQueue[z]<<"  ";
                }
                cout<<endl;
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
                currentstatus[a] = inQueue[y];
                inQueue[x] = -1;
                break;
            }
            if(vacancy <= maxInQueue() || lenInQueue - noofneg() == 1)
            {
                for(int z=lenInQueue-1; z>=0; z--)
                {
                    if(vacancy > inQueue[z] && inQueue[z] != -1)
                    {
                        cout<<"a is equal to: "<<a<<endl;
                        if(a < 0)
                            a = 0;
                        vacancy -= inQueue[z];
                        insideTarama[a] = inQueue[z];
                        currentstatus[a] = inQueue[z];
                        cout<<"Inserted: "<<inQueue[z]<<endl;
                        cout<<"New Vacancy: "<<vacancy<<endl;
                        inQueue[z] = -1;
                        break;
                    }
                }
                cout<<endl<<"People inside Tarama"<<endl;
                for(int z=0; z<lenInsideTarama; z++)
                {
                    cout<<insideTarama[z]<<"  ";
                }
                cout<<endl<<"Current status of people"<<endl;
                for(int z=0; z<lenInsideTarama; z++)
                {
                    cout<<currentstatus[z]<<"  ";
                }
                cout<<endl<<"In Queue: "<<endl;
                for(int z=0; z<lenInQueue; z++)
                {
                    cout<<inQueue[z]<<"  ";
                }
                cout<<endl;
                break;
            }
            else if(vacancy > maxInQueue() && vacancy <= maxInQueue() + max2InQueue())
            {
                cout<<"max sum: "<<maxInQueue()<<"  "<<max2InQueue()<<endl;
                if(vacancy == inQueue[x] + inQueue[y])
                {
                    vacancy = 0;
                    cout<<"New Vacancy: "<<vacancy<<endl;
                    cout<<"inserted: "<<inQueue[x]<<" and "<<inQueue[y]<<endl;
                    if (a == 0)
                    {
                        insideTarama[lenInsideTarama] = inQueue[x];
                        currentstatus[lenInsideTarama] = inQueue[x];
                        lenInsideTarama++;
                        BubbleSort(insideTarama, currentstatus, lenInsideTarama);
                    }
                    else
                    {
                        insideTarama[a-1] = inQueue[x];
                        currentstatus[a-1] = inQueue[x];
                    }
                    cout<<endl<<"a: "<<endl;
                    insideTarama[a] = inQueue[y];
                    currentstatus[a] = inQueue[y];
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
            else
            {
                vacancy = vacancy - maxInQueue() - max2InQueue();
                cout<<"Inserted: "<<maxInQueue()<<" and "<<max2InQueue()<<endl;
                cout<<"New vacancy: "<<vacancy<<endl;
                cout<<endl<<"a: "<<a<<endl;
                if (a <= 0)
                {
                    if(a < 0)
                        a = 0;
                    else
                    {
                        insideTarama[lenInsideTarama] = max2InQueue();
                        currentstatus[lenInsideTarama] = max2InQueue();
                        insideTarama[a] = maxInQueue();
                        currentstatus[a] = maxInQueue();
                        lenInsideTarama++;
                    }

                }
                else
                {
                    insideTarama[a] = max2InQueue();
                    currentstatus[a] = max2InQueue();
                    insideTarama[a-1] = maxInQueue();
                    currentstatus[a-1] = maxInQueue();
                }
                inQueue[indexofmax2InQueue()] = -1;
                inQueue[indexofmaxInQueue()] = -1;
                BubbleSort(insideTarama, currentstatus, lenInsideTarama);
                cout<<endl<<"People inside Tarama: "<<endl;
                for(int z=0; z<lenInsideTarama; z++)
                {
                    cout<<insideTarama[z]<<"  ";
                }
                cout<<endl<<"Current status right now: "<<endl;
                for(int z=0; z<lenInsideTarama; z++)
                {
                    cout<<currentstatus[z]<<"  ";
                }
                cout<<endl;
                break;
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
