#include<iostream>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <time.h>

const int CONST_FOR_QS =100;

template <class Iterator, class Comparator>
Iterator Partition (Iterator begin, Iterator end, Comparator cmp){

    if (begin == end || (begin+1) == end){
        return begin;
    }

    int size = (end - begin);
    int index = rand() % size;
    //std::cout << "[ " << size << " , " << index << " ]\n";

    Iterator pivot = begin + index;

    Iterator last = (end-1);
    typename std::iterator_traits<Iterator>::value_type swapValue = *last;
    *last = *pivot;
    *pivot = swapValue;

    pivot = end - 1;

    Iterator i = begin;
    Iterator j = (pivot - 1);
    while ( i < j){
        while(cmp(*i, *pivot) && (i != j)){
            ++i;
        }
        while(!cmp(*j, *pivot) && (j != i)){
            --j;
        }
        if (i != j){
            typename std::iterator_traits<Iterator>::value_type swapValue = *i;
            *i = *j;
            *j = swapValue;
        }
    }

    if (cmp(*pivot, *i)){
        typename std::iterator_traits<Iterator>::value_type swapValue = *i;
        *i = *pivot;
        *pivot = swapValue;
        return i;
    }

    if ((i+1 == pivot) && (*i < *pivot)){
        return pivot;
    }

    return i;
}

class intcmp {
public:
    bool operator() (int a, int b){
        return a < b;
    }
};

template <class Iterator>
void myPrint(Iterator begin, Iterator end){
    for (Iterator temp = begin; temp != end; ++temp){
        std::cout << *temp << ' ';
    }
    std::cout << '\n';
}

template<class Iterator, class Comparator>
void InsertionSort (Iterator begin, Iterator end, Comparator cmp){
    for(Iterator sortedEnd = begin + 1; sortedEnd != end; ++sortedEnd){
        Iterator insertPosition = begin;
        while(insertPosition != sortedEnd && (cmp( *insertPosition, *sortedEnd))){
            ++insertPosition;
        }
        if (insertPosition != sortedEnd) {
            for(Iterator swaptemp = sortedEnd; swaptemp != insertPosition ; --swaptemp ){
                std::swap(*swaptemp , *(swaptemp-1));
            }
        }
    }
}

template<class Iterator>
void Quicksort(Iterator begin, Iterator end) {
    intcmp cmp;

    while ( begin + 1 < end) {

        if((end - begin) < CONST_FOR_QS){
            InsertionSort(begin, end, cmp);
            break;
        }

        Iterator part = Partition (begin, end, cmp);

        //std::cout << *part << '\n';
        //myPrint(begin, end);

        if ((end - part) < (part - begin)){
            Quicksort(part + 1, end);
            end = part;
        }
        else {
            Quicksort(begin, part);
            begin = part + 1;
        }
    }
}


using std::cin;
int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::vector<int>forQS;

    int k ,temp;
    while(cin >> temp){
        forQS.push_back(temp);
    }
    //forQS.pop_back();
    Quicksort(forQS.begin(), forQS.end());

    //myPrint(forQSort.begin(), forQSort.end());

    for(int i = 9; i < forQS.size(); i += 10){
        //if(( i % 10 == 0) && (i != 0)){
           //std::cout << ' '; }
        std::cout << forQS[i] << ' ';
    }

    return 0;
}
