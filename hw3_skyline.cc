#include <iostream>
#include <vector>

using namespace std;

struct Building {
  float startx;
  float height;
  float endx;
};

struct Skyline {
  // Each pair is (x, y) from left to right.
  // Use the push_back function to insert a pair to the back of the vector.
  vector<pair<float, float> > points;
};


void PrintSkyline(const Skyline& sk) {
  for (pair<float, float> p : sk.points) {
    cout << p.first << "," << p.second << endl;
  }
}

// Q5. 10 points
// Write a function to merge two skylines together and return merged skyline.
Skyline MergeSkylines(const Skyline& sk1, const Skyline& sk2) {
  vector<pair<float, float> >::const_iterator sk1it = sk1.points.begin();
  vector<pair<float, float> >::const_iterator sk2it = sk2.points.begin();
  Skyline final;
  float currenth, newh=0;
  pair<float, float> current;
    while (sk1it!=sk1.points.end() && sk2it!=sk2.points.end()) {
        if (sk1it->first < sk2it->first) {
            currenth=sk1it->second;
            float heightbefore=current.second;
            current.first = sk1it->first;
            current.second = max(currenth, newh);
            if(current.second!=heightbefore){//if  point is already included
                final.points.push_back(current);
            }
            sk1it++;
          }
          else if (sk1it->first==sk2it->first) {
            current.first = sk1it->first;
            currenth=sk1it->second;
            newh=sk2it->second;
            current.second = max(currenth, newh);
            final.points.push_back(current);
            sk1it++;
            sk2it++;
          }
          else {
            newh = sk2it->second;
            float heightbefore=current.second;
            current.first = sk2it->first;
            current.second = max(currenth, newh);
            if(current.second!=heightbefore){//if  point is already included
                final.points.push_back(current);
              }
            sk2it++;
        }
    }
    while (sk1it!=sk1.points.end()) {//checking if there are leftover buildings
        final.points.push_back(*sk1it);
        sk1it++;
    }
    while (sk2it!=sk2.points.end()) {
        final.points.push_back(*sk2it);
        sk2it++;
    }
    return final;
}

// Q6. 5 points
// Write a recursive function MakeSkyline.
// A Building array is given as argument, as well as the start and end index
// Make a skyline that includes buildings arr[start] to arr[end] inclusive.
// Recursive case: If there is more than one Building, call MakeSkyline
//                 on left and right half of Buildings. Then call MergeSkylines
//                 to merge the two skylines and return the merged final.points.
// Base case: If there is only one Building, make a skyline and return.
Skyline MakeSkyline(Building arr[], int start, int end) {
  if (start==end){
    Skyline initial;
    pair<float,float> firstpair;
    firstpair.first=arr[start].startx;
    firstpair.second=arr[start].height;
    initial.points.push_back(firstpair);
    pair<float,float> nextpair;
    nextpair.first=arr[start].endx;
    nextpair.second=0;
    initial.points.push_back(nextpair);
    return initial;
  }
  int mid=(start+end)/2;
  Skyline firstsky=MakeSkyline(arr, start, mid);
  Skyline secondsky=MakeSkyline(arr, mid+1, end);

  return MergeSkylines(firstsky,secondsky);

}

int main() {
  Building buildings[7];

  buildings[0].startx = 6.0;
  buildings[0].height = 15.0;
  buildings[0].endx = 8.5;

  buildings[1].startx = 5.0;
  buildings[1].height = 21.8;
  buildings[1].endx = 9.0;

  buildings[2].startx = 20.0;
  buildings[2].height = 5.0;
  buildings[2].endx = 22.0;

  buildings[3].startx = 21.0;
  buildings[3].height = 3.0;
  buildings[3].endx = 23.0;

  buildings[4].startx = 19.0;
  buildings[4].height = 2.0;
  buildings[4].endx = 24.0;

  buildings[5].startx = 23.5;
  buildings[5].height = 80.0;
  buildings[5].endx = 30.0;

  buildings[6].startx = 5.5;
  buildings[6].height = 19.0;
  buildings[6].endx = 10.0;

  Skyline sk = MakeSkyline(buildings, 0, 6);
  PrintSkyline(sk);

  return 0;
}

/*
Sample output:
5,21.8
10,0
19,2
20,5
23.5,80
30,0
*/
