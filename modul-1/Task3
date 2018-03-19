#include <iostream>
using namespace std;
int main(){
    int m, n;
	cin >> n >> m;
	int arrFirst[10000];
	for(int i = 0; i < n; i++){
		cin >> arrFirst[i];
	}
	int arrSecond[10000];
	for(int i = 0; i < m; i++){
		cin >> arrSecond[i];
	}
	int i = 0;
	int j = 0;
	while((i < m) && (j < n)){
		if( j <= n-1){
        while (arrSecond[i] > arrFirst[j]){
            j++;
        	}
		}
		if ((j <= n-1) && ( i <= m-1)){
			if (arrSecond[i] == arrFirst[j]){
				cout << arrFirst[j] << ' ';
				i++;
				j++;
		    }
		}
		if (i <= m-1){
        while( arrSecond[i] < arrFirst[j]){
        	i++;
        	}
		 }
	}
}
