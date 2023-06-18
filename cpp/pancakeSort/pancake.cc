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
    out = fopen("./numberPancakes.csv", "w");
    fclose(out);
    out = fopen("./numberPancakes.csv", "a");
    vector<int> numberVector;

    fprintf(out, "amount,time,compairs,swaps\n");

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
        clock_t start, end;
        start = clock();
        pancakeSort(numberVector);
        end = clock();

        double elapsed = (end - start) / (double) CLOCKS_PER_SEC * 1000;
        // printVector(numberVector);
        cout << numberVector.size() << endl;
        fprintf(out, "%lu,%f,%li,%li\n",numberVector.size(), elapsed, compairsons,swaps);
        i += 1000;
        rewind(in);
        compairsons = 0;
        swaps = 0;
    }
    fclose(in);
    fclose(out);
}
