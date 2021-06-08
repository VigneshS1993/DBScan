#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

struct Point{
float x;
float y;
int clusterID = -1;
};

vector<int> uniqueElements(vector<Point>&vectPoint)                  // To calculate the unique clusterIDs
{
    vector<Point>::iterator it1, it2;
    vector<int> uniqueClusterID;
    vector<int>::iterator i1;
    int countNum = 0;
    uniqueClusterID.push_back(vectPoint[0].clusterID);
    for(it1 = vectPoint.begin(); it1 != vectPoint.end(); ++it1)
    {
       if (uniqueClusterID.size() > 0)
        {
            for(i1 = uniqueClusterID.begin(); i1 != uniqueClusterID.end(); ++i1)
            {
                if((*i1) == (*it1).clusterID)
                {
                    ++countNum;
                }
            }
            if (countNum == 0)
            {
                uniqueClusterID.push_back((*it1).clusterID);
            }
            else{
                countNum = 0;
            }
        }
        else{
            uniqueClusterID.push_back((*i1));
        }
    }
    return uniqueClusterID;
}

float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}
void dbscan(vector<Point>&vectPoint, float epsilon)
{
    vector<Point>::iterator it1, it2;
    int clusterID = 0, countCP = 0;

    for(it1 = vectPoint.begin(); it1 != vectPoint.end(); ++it1)
    {
        if((*it1).clusterID == (-1))
        {
            ++clusterID;
            for(it2 = vectPoint.begin(); it2 != vectPoint.end(); ++it2)
            {
                if(it2 != it1)
                {
                    if(distance((*it1).x, (*it1).y, (*it2).x, (*it2).y) < epsilon)
                    {
                        (*it1).clusterID = clusterID;
                        (*it2).clusterID = clusterID;
                         ++countCP;
                    }
                }
                /*else
                {
                    //cout << "The iterator has clashed with itself and the position is "<<(*it1).x<<" "<<(*it1).y<<" " <<(*it2).x<<" "<<(*it2).y<<'\n';
                    cout << "The iterator has clashed with itself and the position is "<<(&(*it1))<<" "<<(&(*it2))<<endl;
                }*/
            }
            if(countCP == 0)
            {
                --clusterID;
            }
            countCP = 0;
        }
        else
        {
            for(it2 = vectPoint.begin(); it2 != vectPoint.end(); ++it2)
            {
             if(it2 != it1)
               {
                   if(distance((*it1).x, (*it1).y, (*it2).x, (*it2).y) < epsilon)
                   {
                        (*it2).clusterID = (*it1).clusterID;
                   }
               }
             /*else
                {
                    //cout << "The iterator has clashed with itself and the position is "<<(*it1).x<<" "<<(*it1).y<<" " <<(*it2).x<<" "<<(*it2).y<<'\n';
                    cout << "The iterator has clashed with itself and the position is "<<(&(*it1))<<" "<<(&(*it2))<<endl;
                }*/
            }
        }
    }
    vector<int> uniqueClusterID = uniqueElements(vectPoint);
    vector<Point> vecMeanpoint;
    //cout << "The unique cluster IDs are : ";
    float xMean = 0.0, yMean = 0.0, zMean= 0.0;
    int length = 0;
    for (int i = 0; i < uniqueClusterID.size(); ++i)
    {
        for (int j = 0; j < vectPoint.size(); ++j)
        {
            if(vectPoint[j].clusterID != (-1))
            {
                if(vectPoint[j].clusterID == uniqueClusterID[i])
                {
                xMean += vectPoint[i].x;
                yMean += vectPoint[i].y;
                ++length;
                }
            }
            if(vectPoint[j].clusterID == (-1))
            {
                vecMeanpoint.push_back({vectPoint[j].x, vectPoint[j].y, vectPoint[j].clusterID});
            }
        }
        xMean /= length;
        yMean /= length;
        if(uniqueClusterID[i] != (-1))
        {
            vecMeanpoint.push_back({xMean, yMean, uniqueClusterID[i]});
        }
        xMean = 0.0;
        yMean = 0.0;
        zMean = 0.0;
        length = 0;
    }
    for (int i = 0;i < vecMeanpoint.size(); ++i)
    {
        cout<<" The elements in the vector are "<<vecMeanpoint[i].x<<" "<<vecMeanpoint[i].y<<" "<<vecMeanpoint[i].clusterID<<endl;
    }
}
void vector_initialization(vector<float>&x, vector<float>&y)
{
    vector<Point> vectPoint;
    if (x.size() == y.size())
    {
        for (int i = 0; i < x.size(); ++i)
        {
            vectPoint.push_back({x[i], y[i]});
            //cout << "The points of the vector are : x, y, z being " << vectPoint[i].x <<" "<< vectPoint[i].y <<" \n";
        }
    }
    float epsilon = 0.001;
    dbscan(vectPoint, epsilon);
}
int main()
{
    vector<float> x, y;
    float xCord[56] = {19.111841, 19.137815, 19.119677, 19.119677, 19.119677, 19.120217, 19.120217, 19.119677, 19.119677, 19.119677, 19.111342, 19.111342,  19.11186, 19.11186, 19.119677, 19.119677, 19.119677, 19.137815, 19.11538, 19.11538, 19.116168, 19.119677, 19.137815, 19.137815, 19.112955, 19.112955, 19.112955, 19.119677, 19.119677, 19.11538, 19.119677, 19.119677, 19.119677, 19.119677, 19.119677, 19.11186, 19.111841, 19.131674, 19.119677, 19.11186, 19.11186, 19.111841, 19.111841, 19.111841, 19.11538, 19.116625, 19.115671, 19.119677, 19.119677, 19.119677, 19.116183, 19.113827, 19.119677, 19.1141, 19.107491, 19.119677};
    float yCord[56] = {72.910729, 72.908387, 72.914085, 72.905081, 72.905081, 72.905081, 72.907121, 72.907121, 72.905081, 72.905081, 72.905081, 72.908387,  72.911346, 72.911346, 72.905081, 72.905081, 72.905081, 72.914085, 72.909144, 72.909144, 72.909573, 72.905081, 72.914085, 72.914085, 72.910102, 72.910102, 72.910102, 72.905081, 72.905081, 72.909144, 72.905081, 72.905081, 72.905081, 72.905081, 72.905081, 72.911346, 72.910729, 72.91851, 72.905081, 72.911346, 72.911346, 72.910729, 72.910729, 72.910729, 72.909144, 72.909185, 72.908985, 72.905081, 72.905081, 72.905081, 72.909646, 72.893833, 72.905081, 72.894985, 72.90176, 72.905081};
    for (int i = 0; i < (sizeof(xCord))/4; ++i)
    {
        x.push_back(xCord[i]);
        y.push_back(yCord[i]);
    }
    vector_initialization(x, y);
    return 0;
}
