#include<cassert>
#include<iostream>

using namespace std;


class Arr {

private:
    int* arr;
    int Max;

public:
    Arr(int _Max = 32) : Max(_Max) {
        arr = new int[Max];
    }
    bool Add (int n, int idx){
        if( idx < 0) {
            return false;
        }
        while(idx >= Max){
            int* tempArr = arr;
            int MaxOld = Max;
            Max *=2;
            arr = new int[Max];
            for(int i=0; i< MaxOld; i++){
                arr[i] = tempArr[i];
            }
            delete [] tempArr;
        }

        arr[idx]=n;
        return true;
    }

    int GetIndex(int idx) {
        return arr[idx];
    }

    int Size() {
        return Max;
    }

    void Resize( int n ) {
        if( n == 0 ) {
            return;
        }
        while( n*2 + 1 < Max){
            int* arr2 = arr ;
            Max /=2;
            arr = new int[Max];
            for(int i=0; i< Max; i++){
                arr[i] = arr2[i];
            }
            delete [] arr2;
            if( Max <= 1) {
                break;
            }
        }
    }

    ~Arr () {
        delete [] arr;
    }
 };

class Heap {
private:
    Arr arr;
    int index;
    int arrsize;

public:
    Heap(int number) : arr(number), index(0), arrsize(number) {
    }

    ~Heap() {
    }

    bool Is_empty(){
        return (index <= 0);
    }

    bool Is_full(){
        return (index == arr.Size());
    }

    int Size() {
        return index;
    }

    void Swap(int ind1, int ind2){
        int a = arr.GetIndex(ind1);
        arr.Add(arr.GetIndex(ind2), ind1);
        arr.Add(a, ind2);
    }

    void SiftDown (int i){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int least = i;
        if ((left < index) &&( arr.GetIndex(left) < arr.GetIndex(i))){
            least = left;
        }
        //cout << "if1\n";
        if (right < index && arr.GetIndex(right) < arr.GetIndex(least)){
            least = right;
        }
        //cout << "if2\n";
        if (least != i ){
            Swap(i, least);
            //arr.Print();
            SiftDown (least);
        }
    }

    void ReadArr (){

        int temp;
        for (int i = 0 ; i < arrsize; i++){
            cin >> temp;
            arr.Add(temp, i);
        }

        index = arrsize;

        BuildHeap();
    }

    void BuildHeap(){
        for( int i = (index-2) / 2; i >= 0; --i ){
            SiftDown(i);
        }
    }

    void ShiftUp (int ind){
        while( ind > 0){
            int parent = ( ind - 1 ) / 2;
            if ( arr.GetIndex(ind) >= arr.GetIndex(parent) )
                return;
            Swap( ind, parent );
            ind = parent;
        }
    }

    void Add(int element){
        arr.Add(element, index++);
        ShiftUp ( index-1 );
    }

    int ExtraMin (){
        assert( !Is_empty() );
        int result = arr.GetIndex(0);
        arr.Add(arr.GetIndex(index-1), 0);
        index--;
        if ( !Is_empty() ){
            SiftDown (0);
        }

        //cout << "res " << result << "\n";
        return result;
    }
};

int main(){
    int n;
    cin >> n;
    Heap Numb(n);

    Numb.ReadArr();

    int sum = 0;
    int res = 0;
    while(Numb.Size() != 1){
        int a1 , a2;
        a1=Numb.ExtraMin();
        a2=Numb.ExtraMin();
        sum = a1 + a2;
        res += sum;
        Numb.Add(sum);
    }

    cout << res;
    return 0;
}
