#include <iostream>
#include <vector>
#include <istream>
#include <ostream>

class Segment {
public:
    int start;
    int fin;

    const bool operator < (const Segment& other) {
        return (start < other.start);
    }

    Segment& operator = (const Segment& other) {
        start = other.start;
        fin = other.fin;
        return *this;
    }

    friend std::istream& operator>> ( std::istream& in, Segment& other){
        in >> other.start >> other.fin;
        return in;
    }

    friend std::ostream& operator<< ( std::ostream& out, Segment& other){
        out << '[' << other.start << ';' << other.fin << ']';
        return out;
    }

};

template<class Data>
class Task {

public:

    int getSolve(){

        int n;
        std::cin >> n;
        if (n <= 0){
            return 0;
        }
        readData(n);

//        for(int i = 0; i < n; ++i) {
//            std::cout << data[i] << '\n';
//        }

        int sum = 0;
        int left = data[data.size() - 1].start;
        int right = data[data.size() - 1].fin;
        if (data.size() == 1){
            return right - left;
        }

        for (int i = data.size() - 2; i >= 0; --i){
            if (data[i].start <= right){
                if (data[i].fin > right){
                    right = data[i].fin;
                }
            }
            else{
                //std::cout << sum << ' ' << left << ' ' << right << '\n';
                sum += right - left;
                right = data[i].fin;
                left = data[i].start;
            }
        }
    	sum += right - left;
        return sum;
    }

private:

    std::vector<Data> data;
    int size;

    void readData(int n){

        Data temp;
        for (int i = 0 ; i < n; ++i){
            std::cin >> temp;
            data.push_back(temp);
        }

        size = n;

        buildHeap();
        sort();
    }

    void swap(int ind1, int ind2){
        Data temp = data[ind1];
        data[ind1] = data[ind2];
        data[ind2] = temp;
    }

    void siftDown (int index){
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int least = index;
        if ((left < size) && (data[left] < data[index])){
            least = left;
        }
        //std::cout << "if1\n";
        if ((right < size) && (data[right] < data[least])){
            least = right;
        }

        //std::cout << "if2\n";
        //std::cout << least << ' ' << left << ' ' << right << ' ' << index << '\n';
        //std::cout << data[left] << ' ' << data[right] << ' ' << data[index] << '\n';
        if (least != index ){
            swap(index, least);
            siftDown (least);
        }
    }

    void buildHeap(){
        for( int i = (size-2) / 2; i >= 0; --i ){
            siftDown(i);
        }
    }

    void swapMinAndLast(){
        swap(0, size-1);
        --size;
        if (size > 1){
            siftDown(0);
        }
    }

    void sort(){
        for (int i= 0; i < data.size() - 1; ++i){
            swapMinAndLast();
        }
    }
};

int main() {

    Task<Segment> task;
    std::cout << task.getSolve();

    return 0;
}
