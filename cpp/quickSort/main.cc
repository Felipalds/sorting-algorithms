#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

template <typename T>
void vprint(std::vector<T> x)
{
    std::cout << "[";
    for (int i = 0; i < x.size(); i++)
    {
        std::cout << x[i] << ' ';
    }
    std::cout << "]\n";
}

template <typename T>
void quick_sort(std::vector<T> &array, int low, int high, int *details)
{
    int i = low, j = high - 1;
    T pivot, aux;
    pivot = array[(i + j) / 2];
    while (i <= j)
    {
        details[0]++;
        while (array[i] < pivot && i < high)
        {
            details[0] += 3;
            i++;
        }

        while (array[j] > pivot && j > low)
        {
            details[0] += 3;
            j--;
        }

        if (i <= j)
        {
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
            i++;
            j--;
            details[1]++;
        }
        details[0]++;
    }
    if (j > low)
    {
        details[0]++;
        quick_sort(array, low, j + 1, details);
        quick_sort(array, i, high, details);
    }
}

template <typename T, typename D>
void quick_sort(std::vector<T> &array, std::vector<D> &arrayX, int low, int high, int *details)
{
    int i = low, j = high - 1;
    T pivot, aux;
    D pivotX, auxX;
    pivot = array[(i + j) / 2];
    pivotX = arrayX[(i + j) / 2];
    while (i <= j)
    {
        details[0]++;
        while (array[i] < pivot || (array[i] == pivot && arrayX[i] < pivotX) && i < high)
        {
            details[0] += 7;
            i++;
        }

        while (array[j] > pivot || (array[j] == pivot && arrayX[j] > pivotX) && j > low)
        {
            details[0] += 7;
            j--;
        }

        if (i <= j)
        {
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
            auxX = arrayX[i];
            arrayX[i] = arrayX[j];
            arrayX[j] = auxX;
            i++;
            j--;
            details[1] += 2;
        }
        details[0]++;
    }
    if (j > low)
    {
        details[0]++;
        quick_sort(array, arrayX, low, j + 1, details);
    }
    if (i < high)
    {
        details[0]++;
        quick_sort(array, arrayX, i, high, details);
    }
}

template <typename T, typename D>
int *dquick_sort(std::vector<T> &array, std::vector<D> &arrayX)
{
    int *results = (int *)calloc(2, sizeof(int));
    quick_sort(array, arrayX, 0, array.size(), results);
    return results;
}

template <typename T>
int *dquick_sort(std::vector<T> &array)
{
    int *results = (int *)calloc(2, sizeof(int));
    quick_sort(array, 0, array.size(), results);
    return results;
}

clock_t numbers_test(int times, int **results = NULL)
{
    std::ifstream numbers_file("../../data/numeros 1.txt");
    std::vector<int> numbers_array;
    for (int i = 0; i < times; i++)
    {
        std::string number;
        getline(numbers_file, number);
        numbers_array.push_back(stoi(number));
    }
    clock_t start, end;
    start = clock();
    (*results) = dquick_sort(numbers_array);
    end = clock();
    numbers_file.close();
    return (end - start);
}

clock_t names_test(int times, int **results = NULL)
{
    std::ifstream names_file("../../data/nomes 1.txt");
    std::vector<std::string> names;
    for (int i = 0; i < times; i++)
    {
        std::string name;
        getline(names_file, name);
        names.push_back(name);
    }
    clock_t start, end;
    start = clock();
    (*results) = dquick_sort(names);
    end = clock();
    names_file.close();
    return (end - start);
}

clock_t persons_test(int times, int **results)
{
    std::vector<std::string> persons;
    std::vector<int> numbers;
    std::ifstream people_file("../../data/pessoa 1.txt");
    std::string word;
    for (int i = 0; i < times; i++)
    {
        if (i % 2 == 0)
        {
            people_file >> word;
            numbers.push_back(std::stoi(word));
        }
        else
        {
            getline(people_file, word);
            persons.push_back(word);
        }
    }
    clock_t start, end;
    start = clock();
    (*results) = dquick_sort(numbers, persons);
    for (int i = 0; i < 100; i++)
    {
        std::cout << numbers[i] << ' ' << persons[i] << '\n';
    }
    end = clock();
    people_file.close();
    return (end - start);
}

void matrix_to_csv(std::string file_path, std::vector<std::vector<std::string>> string_matrix, std::vector<std::string> columns)
{
    std::ofstream csv_file(file_path);
    for (int i = 0; i < columns.size() - 1; i++)
    {
        csv_file << columns[i] << ',';
    }
    csv_file << columns[columns.size() - 1] << '\n';
    for (int i = 0; i < string_matrix.size(); i++)
    {
        for (int j = 0; j < string_matrix[0].size() - 1; j++)
        {
            csv_file << string_matrix[i][j] << ',';
        }
        csv_file << string_matrix[i][string_matrix[0].size() - 1] << '\n';
    }
    csv_file.close();
}

const std::vector<std::string> COLUMNS{"time", "amount", "compairs", "swaps"};

int main()
{
    // Números
    std::vector<std::string> registers, comparisons, swaps, times_elapsed;
    std::vector<std::vector<std::string>> data;
    for (int i = 1000; i <= 100000; i = i + 1000)
    {
        int *results = nullptr;
        double elapsed = numbers_test(i, &results) / (double)CLOCKS_PER_SEC;
        std::cout << "Registers: " << i << '\n';
        std::cout << "Comparisons: " << results[0] << '\n';
        std::cout << "Swaps: " << results[1] << '\n';
        std::cout << "Time Elapsed (Seconds): " << elapsed << "s\n\n";
        std::vector<std::string> line;
        line.push_back(std::to_string(elapsed));
        line.push_back(std::to_string(i));
        line.push_back(std::to_string(results[0]));
        line.push_back(std::to_string(results[1]));
        data.push_back(line);
    }
    matrix_to_csv("qsort_numbers.csv", data, COLUMNS);
    data.clear();
    // Nomes
    for (int i = 1000; i <= 100000; i = i + 1000)
    {
        int *results = nullptr;
        double elapsed = names_test(i, &results) / (double)CLOCKS_PER_SEC;
        std::cout << "Iterations: " << i << '\n';
        std::cout << "Comparisons: " << results[0] << '\n';
        std::cout << "Swaps: " << results[1] << '\n';
        std::cout << "Time Elapsed (Seconds): " << elapsed << "s\n\n";
        std::vector<std::string> line;
        line.push_back(std::to_string(elapsed));
        line.push_back(std::to_string(i));
        line.push_back(std::to_string(results[0]));
        line.push_back(std::to_string(results[1]));
        data.push_back(line);
    }
    matrix_to_csv("qsort_names.csv", data, COLUMNS);
    // Pessoas
    data.clear();
    for (int i = 1000; i <= 100000; i = i + 1000)
    {
        int *results = nullptr;
        double elapsed = persons_test(i, &results) / (double)CLOCKS_PER_SEC;
        std::cout << "Iterations: " << i << '\n';
        std::cout << "Comparisons: " << results[0] << '\n';
        std::cout << "Swaps: " << results[1] << '\n';
        std::cout << "Time Elapsed (Seconds): " << elapsed << "s\n\n";
        std::vector<std::string> line;
        line.push_back(std::to_string(elapsed));
        line.push_back(std::to_string(i));
        line.push_back(std::to_string(results[0]));
        line.push_back(std::to_string(results[1]));
        data.push_back(line);
    }
    matrix_to_csv("qsort_pessoas.csv", data, COLUMNS);
    return 0;
}
