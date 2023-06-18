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
std::vector<T> concatenate(std::vector<T> x, std::vector<T> y)
{
    for (int i = 0; i < y.size(); i++)
    {
        x.push_back(y[i]);
    }
    return x;
}

template <typename T>
void quick_sort(std::vector<T> &array, int *details)
{
    std::vector<T> great_array;
    std::vector<T> equal_array;
    std::vector<T> lesser_array;
    if (array.size() > 1)
    {
        T pivot = array[0];
        for (int i = 0; i < array.size(); i++)
        {
            if (array[i] < pivot)
            {
                lesser_array.push_back(array[i]);
            }
            else if (array[i] == pivot)
            {
                details[0]++;
                equal_array.push_back(array[i]);
            }
            else
            {
                details[1]++;
                great_array.push_back(array[i]);
            }
        }
        quick_sort(lesser_array, details);
        quick_sort(great_array, details);
        std::vector<T> new_array = concatenate(concatenate(lesser_array, equal_array), great_array);
        array.swap(new_array);
    }
}

template <typename T, typename D>
void quick_sort(std::vector<T> &array, std::vector<D> &arrayX, int *details)
{
    if (array.size() != arrayX.size())
    {
        std::cout << "Error during co-sort.\n";
        exit(1);
    }
    std::vector<T> great_array;
    std::vector<T> equal_array;
    std::vector<T> lesser_array;
    std::vector<D> great_arrayX;
    std::vector<D> equal_arrayX;
    std::vector<D> lesser_arrayX;
    if (array.size() > 1)
    {
        T pivot = array[0];
        for (int i = 0; i < array.size(); i++)
        {
            if (array[i] < pivot)
            {
                details[0]++;
                details[1]++;
                lesser_array.push_back(array[i]);
                lesser_arrayX.push_back(arrayX[i]);
            }
            else if (array[i] == pivot)
            {
                details[0]++;
                if (arrayX[i] < arrayX[0])
                {
                    details[0]++;
                    details[1]++;
                    lesser_array.push_back(array[i]);
                    lesser_arrayX.push_back(arrayX[i]);
                }
                else if (arrayX[i] > arrayX[0])
                {
                    details[0]++;
                    details[1]++;
                    great_array.push_back(array[i]);
                    great_arrayX.push_back(arrayX[i]);
                }
                else
                {
                    equal_array.push_back(array[i]);
                    equal_arrayX.push_back(arrayX[i]);
                }
            }
            else
            {
                details[1]++;
                great_array.push_back(array[i]);
                great_arrayX.push_back(arrayX[i]);
            }
        }
        quick_sort(lesser_array, lesser_arrayX, details);
        quick_sort(great_array, great_arrayX, details);
        std::vector<T> new_array = concatenate(concatenate(lesser_array, equal_array), great_array);
        std::vector<D> new_arrayX = concatenate(concatenate(lesser_arrayX, equal_arrayX), great_arrayX);
        array.swap(new_array);
        arrayX.swap(new_arrayX);
    }
}

template <typename T, typename D>
int *dquick_sort(std::vector<T> &array, std::vector<D> &arrayX)
{
    int *results = (int*) calloc(2, sizeof(int));
    quick_sort(array, arrayX, results);
    return results;
}

template <typename T>
int *dquick_sort(std::vector<T> &array)
{
    int *results = (int*) calloc(2, sizeof(int));
    quick_sort(array, results);
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
    end = clock();
    people_file.close();
    return (end - start);
}

void matrix_to_csv(std::string file_path, std::vector<std::vector<std::string>> string_matrix, std::vector<std::string> columns)
{
    std::ofstream csv_file(file_path);
    for (int i = 0; i < columns.size()-1; i++)
    {
        csv_file << columns[i] << ',';
    }
    csv_file << columns[columns.size()-1] << '\n';
    for (int i = 0; i < string_matrix.size(); i++)
    {
        for (int j = 0; j < string_matrix[0].size()-1; j++)
        {
            csv_file << string_matrix[i][j] << ',';
        }
        csv_file << string_matrix[i][string_matrix[0].size()-1] << '\n';
    }
    csv_file.close();
}

const std::vector<std::string> COLUMNS{"time","amount","compairs","swaps"}; 

int main()
{
    
    // Números
    std::vector<std::string> registers, comparisons, swaps, times_elapsed;
    std::vector<std::vector<std::string>> data;
    for (int i = 1000; i <= 100000; i = i + 1000)
    {
        int *results = nullptr;
        double elapsed = numbers_test(i, &results) / (double) CLOCKS_PER_SEC;
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
        double elapsed = names_test(i, &results) / (double) CLOCKS_PER_SEC;
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
        double elapsed = persons_test(i, &results) / (double) CLOCKS_PER_SEC;
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
