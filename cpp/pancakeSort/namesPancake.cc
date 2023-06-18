#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

long int compairsons, swaps = 0;

void printVector(vector<string> nameVector){
    int l = nameVector.size();
    printf("[");
    for (int i = 0; i < l; i++){
      cout << nameVector[i] << ", ";
    }
    printf("]");
}
void flip(vector<string>& nameVector, int maxInd){
    int left = 0;
    while(left < maxInd){
        compairsons++;
        swap(nameVector[left], nameVector[maxInd]);
        swaps++;
        maxInd--;
        left++;
    }
}

int maxIndex(const vector<string>& nameVector, int virtualLen) {
    int index = 0;
    for (int i = 0; i < virtualLen; i++){
        compairsons++;
        if(nameVector[i] > nameVector[index]){
            compairsons++;
            index = i;
        }
    }
    return index;
}

void pancakeSort(vector<string>& nameVector){
    int l = nameVector.size();
    while (l >= 1) {
      compairsons++;
      int maxInd = maxIndex(nameVector, l);
      if(maxInd != l - 1){
        compairsons++;
        if(maxInd != 0){
          compairsons++;
          flip(nameVector, maxInd);
        }
        flip(nameVector, l-1);
      }
      l-=1;
    }
}


FILE *in, *out;
int main(){
    in = fopen("../../data/nomes 1.txt", "r");
    out = fopen("./namesPancakes.csv", "w");
    fclose(out);
    out = fopen("./namesPancakes.csv", "a");
    vector<string> namesVector;

    fprintf(out, "amount,time,compairs,swaps\n");

    int i = 0;
    int j = 0;
    while (i < 1000) {
        j = 0;
        while (j <= 999){
          std::string name;
          char buffer[256];
          fscanf(in, "%s\n", buffer);
          name = string(buffer);
          namesVector.push_back(name);
          j++;
        }
        clock_t start, end;
        start = clock();
        pancakeSort(namesVector);
        end = clock();

        double elapsed = (end - start) / (double) CLOCKS_PER_SEC * 1000;
        // printVector(numberVector);
        cout << namesVector.size() << endl;
        fprintf(out, "%lu,%f,%li,%li\n",namesVector.size(), elapsed, compairsons,swaps);
        i += 1000;
        printVector(namesVector);
        rewind(in);
        compairsons = 0;
        swaps = 0;
    }
    fclose(in);
    fclose(out);
}
