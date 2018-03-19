#include<iostream>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <time.h>

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
            i++;
        }
        while(!cmp(*j, *pivot) && (j != i)){
            j--;
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
    for (Iterator temp = begin; temp != end; temp++){
        std::cout << *temp << ' ';
    }
    std::cout << '\n';
}

template<class Iterator>
int QuicksortK(Iterator begin, Iterator end, int k) {
    intcmp cmp;

    while ( begin + 1 < end) {

        //myPrint(begin, end);

        Iterator part = Partition (begin, end, cmp);
        //myPrint(begin, end);

        //std::cout << *part << ' ' << k << '\n';

        if( part - begin == k) {
            return *part;
        }
        if( part - begin < k ) {
            k -= (part - begin + 1);
            begin = part + 1;
        } else {
            end = part;
        }

        //std::cout << "--------\n";
    }

    return *begin;
}

int main(){

    srand( time(NULL) );

    std::vector<int> forQSort;
    int n, k ,temp;
    std::cin>> n >> k;
    for (int i =0; i<n; i++){
          std::cin >> temp;
          forQSort.push_back(temp);
    }

    int value = QuicksortK(forQSort.begin(), forQSort.end(), k);

    //myPrint(forQSort.begin(), forQSort.end());

    std::cout << value;

    return 0;
}
