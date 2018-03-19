#include <iostream>
#include <vector>
using namespace std;

struct Point{
    int x;
    int y;
    Point (int x1 = 0, int y1 = 0) {
        x = x1;
        y = y1;
    }
};

Point start(100000, 100000);
Point ocX(1000000, start.y);

class pointcmp {
public:
    bool operator() (Point a, Point b){
        return (((a.x - start.x) * (b.y - start.y) - (a.y - start.y) * (b.x - start.x)) <= 0);
        /*
        Point va((a.x - start.x),(a.y - start.y));
        Point vb((b.x - start.x), (b.y - start.y));
        Point vstart((ocX.x - start.x), 0);
        double temp1 = ((-1)*(va.y * vstart.x))/
                        ((va.x * va.x + va.y * va.y) * vstart.x);
        double temp2 = ((-1)*(vb.y * vstart.x))/
                        ((vb.x * vb.x + vb.y * vb.y) * vstart.x);
        return ( temp1 < temp2);*/

    }
};

template<class Iterator, class Comparator>
void InsertionSort (Iterator begin, Iterator end, Comparator cmp){
    for(Iterator sortedEnd = begin + 1; sortedEnd != end; ++sortedEnd){
        Iterator insertPosition = begin;
        while(insertPosition != sortedEnd && (cmp( *insertPosition, *sortedEnd))){
            ++insertPosition;
        }
        if (insertPosition != sortedEnd) {
            for(Iterator swaptemp = sortedEnd; swaptemp != insertPosition ; --swaptemp ){
                swap(*swaptemp , *(swaptemp-1));
            }
        }
    }
}

template<class Iterator>
void myPrint (Iterator begin, Iterator end) {
    for(Iterator i = begin; i != end; ++i) {
        cout << i->x << ' ' << i->y << '\n';
    }
}

int main(){
    int N;
    cin >> N;
    vector <Point> points (N);
    int posstart = 0;
    for(int i = 0; i < N; i++){
        int a, b;
        cin >> a >> b;
        points[i] = Point(a , b);
            if ((a < start.x) || ((a == start.x) && (b < start.y))){
                start = points[i];
                posstart = i;
            }
        }
    swap (points[posstart], points[0]);
    pointcmp cmp;
    InsertionSort(points.begin(), points.end(), cmp);
    myPrint(points.begin(), points.end());
    return 0;
}
