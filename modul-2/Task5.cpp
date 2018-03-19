#include <iostream>
#include <vector>

const int bitesInByte = 8;

int pow2(int exp) {
    int answer = 2;
    --exp;
    while(exp > 0) {
        answer *= 2;
        --exp;
    }
    return answer;
}

int getRCategoryValue (int64_t value ,int rCategory ){
    while(rCategory > 0){
        value /= pow2(bitesInByte);
        --rCategory;
    }
    return value % pow2(bitesInByte);
}

template<class Iterator>
void countingSort(Iterator begin, Iterator end, int rCategory){
    int maxValueInByte = pow2(bitesInByte); //(2^8 чисел в байте)
    std::vector<int> countingArray(maxValueInByte, 0);
    for (Iterator it = begin; it !=end; ++it){
        countingArray[getRCategoryValue(*it, rCategory)]++ ;
    }
    int sum = 0;
    for(int i = 0; i< countingArray.size(); ++i){
        int temp = countingArray[i];
        countingArray[i] = sum;
        sum += temp;
    }
    std::vector<int64_t> resultArray(end - begin);// как взять тип?
    for(Iterator it = begin; it != end; ++it){
        resultArray[countingArray[getRCategoryValue(*it, rCategory)]++]= *it;
    }
    Iterator start = begin;
    for(int i = 0; i < resultArray.size(); ++i){
        *start = resultArray[i];
        ++start;
    }
}

template <class Iterator>
void myPrint(Iterator begin, Iterator end){
    for (Iterator it = begin; it != end; ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

template <class Iterator>
void LSD(Iterator begin, Iterator end){
    for (int rCategory = 0; rCategory < sizeof(int64_t); ++rCategory){
        countingSort(begin, end, rCategory);
        //myPrint(begin, end);
    }
}

int main(){
    int n;
    int64_t temp;
    std::cin >> n;
    std::vector<int64_t> values;
    for( int i = 0; i < n; ++i){
        std::cin >> temp;
        values.push_back(temp);
    }

    LSD(values.begin(), values.end());

    myPrint(values.begin(), values.end());
    return 0;
}
