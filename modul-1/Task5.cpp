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
		bool Push (int n, int idx){
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

class Stack {

    private:
		Arr arr;
		int index;

	public:
		Stack(int number) : arr(number), index(0) {
		}

		~Stack() {
		}

		bool Push (int n) {
			arr.Push(n, ++index);
		}

		bool Pop (int& n) {

			if(index <= 0) {
				return false;
			}
			else{
                //cout << index << "\n";

				n = arr.GetIndex(index--);
				arr.Resize(index);
				return true;
			}
		}
		bool Top (int& n) {

			if(index <= 0) {
				return false;
			}
			else {
				n = arr.GetIndex(index);
				return true;
			}
		}

		bool Is_empty(){
			return (index <= 0);
		}

		bool Is_full(){
			return (index == arr.Size());
		}

		int Size() {
            return arr.Size();
		}
};

int GetCharCode (char c){
    switch(c){
        case '+': {
            return 1;
        }
        case '-': {
            return 2;
        }
        case '*': {
            return 3;
        }
        case '/': {
            return 4;
        }
        case '(': {
            return 5;
        }
        case ')': {
            return 6;
        }
    }
    //cout << "Error\n";
    return -1;
}

char GetChar (int a){
    switch(a){
        case 1: {
            return '+';
        }
        case 2: {
            return '-';
        }
        case 3: {
            return '*';
        }
        case 4: {
            return '/';
        }
        case 5: {
            return '(';
        }
        case 6: {
            return ')';
        }
    }
    cout << "Error\n";
    return '\n';
}

int GetPriority (char c){
    switch(GetCharCode(c)){
        case 1:
        case 2: {
            return 1;
        }
        case 3:
        case 4: {
            return 2;
        }
        case 5:
        case 6: {
            return 0;
        }
        case 7: {
            return 3;
        }
    }
    cout << "Error\n";
    return -1;
}

int main(){

	Stack st(1);

    string s , s2;
    cin >> s;

    if(s.size() <= 1){
        cout << s;
        return 0;
    }

    for( int i = 0; i < s.size(); i++) {
        //cout << '\"' << s[i] << "\"\n\"" << s2 << "\"\n\n";


        if ((int)s[i] >= ((int)'0') && ((int)s[i] <= (int)'9')) {
            //cout << "Number\n";
            s2 = s2 + s[i];
        }
        else {

            if(s[i] == '('){
                st.Push(GetCharCode(s[i]));
                continue;
            }
            if (s[i] == ')'){
                bool flag = true;
                while (flag){

                    int rv;
                    st.Pop(rv);
                    if (GetChar(rv) != '('){
                        s2 += " ";
                        s2 += GetChar(rv);
                        s2 += " ";
                    }
                    else {
                        flag = false;
                    }
                }
                continue;
            }

            /*if( (i == 0) && (s[i] == '-') ){
                s2 = "0 -";
                continue;
            }*/
            s2 += ' ';
            if (st.Is_empty()) {
                st.Push(GetCharCode(s[i]));
            }
            else {
                int rv; //returned_value;

                st.Top(rv); // проверить на True

                while (GetPriority(s[i]) <= GetPriority(GetChar(rv))) {
                    st.Pop(rv);

                    s2 += " ";
                    s2 += GetChar(rv);
                    s2 += " ";

                    st.Top(rv);
                    if( st.Is_empty() ) {
                        break;
                    }
                }

                st.Push(GetCharCode(s[i]));

            }
        }
    }

    while(! st.Is_empty()){
        int rv;
        st.Pop(rv);
        if (GetPriority(GetChar(rv)) != 0){
            s2 += " ";
            s2 += GetChar(rv);
            s2 += " ";
        }
    }

    //cout << '[' << s2 << "]\n\n";

    int si = 0;
    Stack stP(4);
    for(int i = 1; i< s2.size(); i++){
        while (s2[si] == ' ') {
            ++si;
        }

        if (s2[i] == ' '){

        /*
            for( int k = si; k < i; ++k) {
                cout << s2[k];
            }
            cout << '\n';
            int rv;
            stP.Top(rv);
            cout << rv << "\n\n";
        */
            if (i - si == 1) {
                if(GetCharCode(s2[si]) != -1){
                    int n1, n2;
                    stP.Pop(n2);
                    stP.Pop(n1);
                    switch(s2[si]){
                        case '+':{
                            stP.Push(n1+n2);
                            break;
                        }
                        case '-':{
                            stP.Push(n1-n2);
                            break;
                        }
                        case '*':{
                            stP.Push(n1*n2);
                            break;
                        }
                        case '/':{
                            stP.Push(n1/n2);
                            break;
                        }
                    }
                    si++;
                    continue;
                }
                if (s2[si] == ' '){
                    si++;
                    continue;
                }
                stP.Push((int)s2[si] - (int)'0');
                //cout << "Temp1: " << ((int)s2[si] - (int)'0') << '\n';
                si++;
            }
            else {
                if (si >= i) {
                    continue;
                }
                int temp = 0;
                for (int j = si; j < i; j++){
                    temp *= 10;
                    temp += ((int)s2[j] - (int)'0');
                }
                //cout << "Temp2: " << temp << ' ' << si << ' ' << i << '\n';
                stP.Push(temp);
                si = i;
            }
        }
    }
    int rv;
    stP.Pop(rv);
    cout << rv;

	return 0;
}
