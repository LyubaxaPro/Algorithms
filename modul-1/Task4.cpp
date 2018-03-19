#include <iostream>
#include <cassert>

using namespace std;

class Dequeue {

private:
    short* dequeue;
    int head;
    int tail;
    int Size;

    int getIndexNext( int index){
        return (index + 1) % Size;
    }
    int getIndexPrev( int index){
        return ( index + Size - 1) % Size;
    }
    void Resize (){
        if ( getIndexNext(tail) == head){
            short* temp = new short [Size * 2];
            if (tail < head){
                for (int i = head ;i < Size; i++ ){
                    temp[i] = dequeue[i];
                }
                for (int i = 0; i < tail; i++){
                    temp [i + Size] = dequeue[i];
                }
                tail += Size;
            }
            else{
                for (int i = 0; i < Size; i++){
                    temp[i] = dequeue[i];
                }
            }
            Size *= 2;
            delete [] dequeue;
            dequeue = temp;
        }
    }

public:
    Dequeue() {
        Size = 32;
        head = 0;
        tail = 1;
        dequeue = new short [Size];
    }

    ~Dequeue (){
        delete [] dequeue;
    }

    void PushFront(short a){
        Resize();
        dequeue[head] = a;
        head = getIndexPrev(head);
    }

    bool PopFront(short& a){
        if (tail == getIndexNext(head)){
            return false;
        }
        else{
            head = getIndexNext(head);
            a = dequeue[head];
            return true;
        }
    }

    void PushBack(short a){
        Resize();
        dequeue[tail] = a;
        tail = getIndexNext(tail);
    }

    bool PopBack(short& a){
        if (tail == getIndexNext(head)){
            return false;
        }
        else {
            tail = getIndexPrev(tail);
            a = dequeue[tail];
            return true;
        }
    }
};

int main(){
    Dequeue deq;

    int n,operand;
    short k;
    cin >> n;
    bool flag = true;
    for (int i = 0; i< n; i++){
        cin >> operand >> k;
        if( !flag ) {
            continue;
        }
        switch(operand){
            case 1:{
                deq.PushFront(k);
                break;
            }
            case 2:{
                short temp;
                if (deq.PopFront(temp)){
                    if (k != temp){
                        flag = false;
                    }
                }
                else {
                    if (k != -1){
                        flag = false;
                    }
                }
                break;
            }
            case 3:{
                deq.PushBack(k);
                break;
            }
            case 4:{
                short temp;
                if (deq.PopBack(temp)){
                    if (k != temp){
                        flag = false;
                    }
                }
                else {
                    if (k != -1){
                        flag = false;
                    }
                }
                break;
            }
        }
    }

    cout << (flag ? "YES\n" : "NO\n");

    return 0;
}
