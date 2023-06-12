#include <iostream>

void print_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';
}

int *extend_array(int *array, int size, int value = 0)
{
    int new_size = size+1;
    array = (int*) realloc(array, new_size*sizeof(int));
    if (!array)
    {
        std::cout << "Erro na realocação...\n";
        exit(1);
    }
    array[size] = value;
    return array;
}

int *concatenate_array(int *array, int *concatenate, int size_a, int size_b) 
{
    int new_size = size_a+size_b;
    array = (int*) realloc(array, new_size*sizeof(int));
    if (!array)
    {
        std::cout << "Erro na realocação...\n";
        exit(1);
    }
    for (int i = size_a; i < new_size; i++)
    {
        array[i] = concatenate[i-size_a];
    }
    return array;
}

int *quick_sort(int *array, int size)
{
    int g_size = 0, e_size = 0, l_size = 0;
    int *greater = new int[g_size];
    int *equal = new int[e_size];
    int *lesser = new int[l_size];
    if (size > 1)
    {
        int pivot = array[0];
        for (int i = 0; i < size; i++)
        {
            if (array[i] < pivot)
            {
                lesser = extend_array(lesser, l_size++, array[i]);
                print_array(lesser, l_size);
            }
            else if (array[i] == pivot) 
            {
                equal = extend_array(equal, e_size++, array[i]);
                print_array(equal, e_size);
            }
            else if (array[i] > pivot)
            {
                greater = extend_array(greater, g_size++, array[i]);
                print_array(greater, g_size);
            }
        }
        delete array;
        return concatenate_array(concatenate_array(quick_sort(lesser, l_size), equal, l_size, e_size), quick_sort(greater, g_size), l_size+e_size, g_size);
    } 
    return array;
}

int main()
{
    int *array = new int[10] {1, 25, 3, 8, 0, -3, 5, 10, 100, 20};
    print_array(array, 10);
    int *array_b = new int[2] {42, 69};
    if (!array)
    {
        std::cout << "Erro na alocação...\n";
        exit(1);
    }
    // for (int i = 0; i < 100; i++)
    // {
    //     array = extend_array(array, 10+i, i);
    // }
    // print_array(array, 110);
    //
    // array = extend_array(array, 10, 77);
    // std::cout << array[10] << '\n';
    // array = concatenate_array(array, array_b, 11, 2);
    // std::cout << array[11] << ' ' << array[12] << '\n';
    //
    array = quick_sort(array, 10);
    print_array(array, 10);
}