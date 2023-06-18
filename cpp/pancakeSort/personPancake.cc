
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

long int compairsons, swaps = 0;

typedef struct Person {
    string name;
    int id;
} Person;

void printVector(vector<Person> personVector){
    int l = personVector.size();
    printf("[");
    for (int i = 0; i < l; i++){
      cout << personVector[i].id << " "<< personVector[i].name << ", ";
    }
    printf("]");
}
void flip(vector<Person>& personVector, int maxInd){
    int left = 0;
    while(left < maxInd){
        compairsons++;
        swap(personVector[left], personVector[maxInd]);
        swaps++;
        maxInd--;
        left++;
    }
}

int maxIndex(const vector<Person>& personVector, int virtualLen) {
    int index = 0;
    for (int i = 0; i < virtualLen; i++){
        compairsons++;
        if(personVector[i].id > personVector[index].id){
            compairsons++;
            index = i;
        }
    }
    return index;
}

void pancakeSort(vector<Person>& personVector){
    int l = personVector.size();
    while (l >= 1) {
      compairsons++;
      int maxInd = maxIndex(personVector, l);
      if(maxInd != l - 1){
        compairsons++;
        if(maxInd != 0){
          compairsons++;
          flip(personVector, maxInd);
        }
        flip(personVector, l-1);
      }
      l-=1;
    }
}


FILE *in, *out;
int main(){
    out = fopen("./personsPancakes.csv", "w");
    ifstream peopleFile("../../data/pessoa 1.txt");
    fclose(out);
    out = fopen("./personsPancakes.csv", "a");
    vector<Person> personsVector;

    fprintf(out, "amount,time,compairs,swaps\n");

    int i = 0;
    int j = 0;

    string word;
    while (i < 1000) {
        j = 0;
        while (j <= 1000){
          getline(peopleFile, word);
          cout << word[0] << endl ;
          j++;
        }
        clock_t start, end;
        start = clock();
        end = clock();

        double elapsed = (end - start) / (double) CLOCKS_PER_SEC * 1000;
        peopleFile.clear();
        cout << personsVector.size() << endl;
        fprintf(out, "%lu,%f,%li,%li\n",personsVector.size(), elapsed, compairsons,swaps);
        i += 1000;
        // printVector(personsVector);
        compairsons = 0;
        swaps = 0;
    }
    fclose(in);
    fclose(out);
}
