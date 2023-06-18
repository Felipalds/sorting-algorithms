#include <chrono>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

long int compairsons, swaps = 0;

void printVector(vector<int> numVector){
    int l = numVector.size();
    printf("[");
    for (int i = 0; i < l; i++){
      printf("%d, ", numVector[i]);
    }
    printf("]");
}
void flip(vector<int>& numVector, int maxInd){
    int left = 0;
    while(left < maxInd){
        compairsons++;
        swap(numVector[left], numVector[maxInd]);
        swaps++;
        maxInd--;
        left++;
    }
}

int maxIndex(const vector<int>& numVector, int virtualLen) {
    int index = 0;
    for (int i = 0; i < virtualLen; i++){
        compairsons++;
        if(numVector[i] > numVector[index]){
            compairsons++;
            index = i;
        }
    }
    return index;
}

void pancakeSort(vector<int>& numVector){
    int l = numVector.size();
    while (l >= 1) {
      compairsons++;
      int maxInd = maxIndex(numVector, l);
      if(maxInd != l - 1){
        compairsons++;
        if(maxInd != 0){
          compairsons++;
          flip(numVector, maxInd);
        }
        flip(numVector, l-1);
      }
      l-=1;
    }
}


FILE *in, *out;
int main(){
    in = fopen("../../data/numeros 1.txt", "r");
    out = fopen("./numberPancakes.csv", "w+");

    vector<int> numberVector;

    int i = 0;
    int j = 0;
    while (i < 100000) {
        j = 0;
        while (j <= 999){
          int num;
          fscanf(in, "%d\n", &num);
          numberVector.push_back(num);
          j++;
        }
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        pancakeSort(numberVector);
        // printVector(numberVector);
        cout << numberVector.size() << endl;
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        cout << "compairsons = " << compairsons << endl;
        cout << "swaps = " << swaps << endl;
        i += 1000;
        rewind(in);
        compairsons = 0;
        swaps = 0;
    }
}
