#include <iostream>
#include <vector>
#include <stdint.h>
#include <iterator>

template<class Iterator>
void myPrint(Iterator begin, Iterator end){
    for(Iterator it = begin; it != end; ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

template<class Iterator>
int64_t mergeSortM(Iterator begin, Iterator end){

    int64_t count = 0;

    int64_t length = 1;
    Iterator left_i, right_i, left_j, right_j;
    while(length <= end - begin){

        //std::cout << length << "\n";

        int64_t step = 0;
        while(true){
            if ((step+1) * length < end - begin ){
                left_i = begin + step * length;
                ++step;
                right_i = begin + step * length;
            }
            else{
                break;
            }
            left_j = begin + step * length;
            ++step;
            if (step * length <= end - begin ){
                right_j = begin + step * length;
            }
            else{
                right_j = end;
            }

            //std::cout << *left_i << ' ' << *left_j << '\n';

            std::vector<int64_t> temp;//<typename std::iterator_traits<Iterator>::type_value> temp;

            Iterator start = left_i;

            while (true){
                if (*left_i <=  *left_j){
                    temp.push_back(*left_i);
                    left_i += 1;
                    if (left_i == right_i){
                        for(Iterator it = left_j; it != right_j; ++it){
                            temp.push_back(*it);
                        }
                        break;
                    }
                }
                else {

                    count += right_i - left_i;

                    temp.push_back(*left_j);
                    left_j += 1;
                    if (left_j == right_j){
                        for(Iterator it = left_i; it != right_i; ++it){
                            temp.push_back(*it);
                        }
                        break;
                    }
                }
            }

            for(int64_t i = 0; i < temp.size(); ++i){
                *start = temp[i];
                ++start;
            }

            //myPrint(begin, end);
        }
        length *= 2;
    }

    return count;
}



int main(){
    std::vector<int64_t> line;
    int64_t temp;
    while (std::cin >> temp){
        line.push_back(temp);
    }

    std::cout << mergeSortM(line.begin(), line.end());

    //myPrint(line.begin(), line.end());

    return 0;
}
