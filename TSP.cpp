#include <bits/stdc++.h>
using namespace std;
vector<int> cities;
vector<int> finalOrder;
int arr[20]; // arr is the array that stores the City order
int numOfCities;
int dist[20][20];
class TSP
{
public:
    int points[20][2];
    int numcities;

    int CalculateDistance(int x1, int y1, int x2, int y2)
    {
        //return int(sqrt(pow(x1-x2,2)+pow(y1-y2,2)) + 0.5 );
        return int(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
    }
    void input_pos()
    {
        cout << "enter no of cities";
        cin >> numcities;
        int i = 0;
        cout << "Enter cordinates of points" << endl;
        while (i < numcities)
        {
            cin >> points[i][0] >> points[i][1];
            i++;
        }
    }
    void dist_graph()
    {
        for (int i = 0; i < 20; i++)
        {
            dist[i][i] = 0;
            for (int j = i + 1; j < 4; j++)
            {

                dist[i][j] = CalculateDistance(points[i][0], points[i][1], points[j][0], points[j][1]);
                dist[j][i] = dist[i][j];
                // cout<<"calculating of "<<points[i][0]<<" "<<points[i][1]<<" ; "<<points[j][0]<<" "<<points[j][1]<< " is"<<dist[i][j]<<endl;
            }
        }
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }
};
int getTourLength()
{
    vector<int>::iterator it = cities.begin();

    it = cities.begin();
    int pcity1 = *it, ncity;

    int tourLength = dist[0][pcity1];
    for (it = cities.begin() + 1; it != cities.end(); it++)
    {
        ncity = *it;
        tourLength += dist[pcity1][ncity];

        pcity1 = ncity;
    }

    tourLength += dist[pcity1][0]; //adding the distance back to the source path
    return tourLength;
}
int get_initial_tour_length()
{
    //cout << " findint innitial permutation" << endl;
    for (int i = 0; i < numOfCities; i++)
        arr[i] = i;
    cities.clear();
    for (int i = 0; i < numOfCities; i++)
    {
        cities.push_back(arr[i]);
        finalOrder.push_back(arr[i]);
    }

    vector<int>::iterator itr;
    // cout << " initial permutaion is:" << endl;
    // for (itr = cities.begin(); itr != cities.end(); itr++)
    // {
    //     cout << (*itr) << " " << endl;
    // }
    int TourLength = getTourLength();
    return TourLength;
}
double getProbability(int difference, double temperature) //This function finds the probability of how bad the new solution is
{
    return exp(-1 * difference / temperature);
}
// void swap2(int i, int j)
// {
//     vector<int>::iterator it = cities.begin();
//     int temp = *(it + i);
//     *(it + i) = *(it + j);
//     *(it + j) = temp;
// }
int main()
{
    TSP obj;
    vector<int>::iterator it2;
    obj.input_pos();
    obj.dist_graph();
    // for(int i=0;i<20;i++)
    // {
    //     for(int j=0;j<20;j++)
    //     {
    //         cout<<dist[i][j]<<" ";        }
    //         cout<<endl;
    // }
    numOfCities = obj.numcities;
    int tourlength = get_initial_tour_length();
    int Tm = 1000;

    int iter_max = 1000;
    for (int i = 1; i < iter_max; i++)
    {
        random_shuffle(cities.begin(), cities.end());
        // vector<int> pos;
        // pos.push_back(0);
        // pos.push_back(0);
        // while (pos[0] == pos[1])
        // {
        //     //cout << "inside while loop" << endl;
        //     pos[0] = rand() % numOfCities;
        //     pos[1] = rand() % numOfCities;
        // }
        // ///cout << " pos[0] is" << pos[0] << " pos[1] is" << pos[1] << endl;
        // sort(pos.begin(), pos.end());
        // swap2(pos[0], pos[1]);
        // vector<int>::iterator itr;
        // itr = cities.begin();
        // random_shuffle(itr + pos[0], itr + pos[1]);
int newTourLength = getTourLength();

        //cout << "prev tour lenght is" << tourlength << " new  tour lenght is " << newTourLength << endl;
        int E = tourlength - newTourLength;
        // cout << " E is" << E << endl;
        int T = Tm / i;
        if (E < 0 or (E > 0 and (getProbability(E, T) > rand() % 2)))
        {
            finalOrder.clear();
            for (it2 = cities.begin(); it2 != cities.end(); it2++)
            {
                finalOrder.push_back(*it2);
            }
        }
        // vector<int>::iterator itrt;
        // cout << "Final order is" << endl;
        // for (itrt = finalOrder.begin(); itrt != finalOrder.end(); itrt++)
        // {
        //     cout << *itrt << " ";
        // }

        tourlength = newTourLength;

        //random_shuffle(cities.begin(), cities.end());
    }

    vector<int>::iterator itrt, itr1;
    itr1 = finalOrder.begin();
    cout << "Final order of Travel would be " << endl;
    for (itrt = finalOrder.begin(); itrt != finalOrder.end(); itrt++)
    {
        cout << *itrt << " ->";
    }
    cout << *itr1;
}