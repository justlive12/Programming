#include "BozoSort.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
template<class T>
using new_vector = vector<T>;
template<class T>
using new_matrix = vector<vector<T>>;


template<class T>
void print_vector(new_vector<T> arr) {
    for (T i : arr) {
        cout << i << " ";
    }
    cout << endl;
}


template<class T>
bool is_sorted(new_vector<T> arr, bool direction = true) {

    int arr_len = arr.size();
    if (direction) {
        for (int i = 1; i < arr_len; i++) {

            if (arr[i - 1] > arr[i]) {
                return false;
            }

        }
    }
    else {
        for (int i = 1; i < arr_len; i++) {

            if (arr[i - 1] < arr[i]) {
                return false;
            }

        }
    }
    return true;

}


template<class T>
new_vector<T> BozoSort(new_vector<T> arr, bool direction = true) {
    int arr_len = arr.size();
    while (!is_sorted(arr, direction)) {

        int first = rand() % arr_len;
        int second = rand() % arr_len;
        swap(arr[first], arr[second]);

    }
    return arr;
}


template<class T>
new_vector<T> BozoSort(new_matrix<T> arr, bool direction = true) {
    new_vector<T> one_dimensional_matrix;
    for (new_vector<T> i : arr) {
        for (T j : i) {
            one_dimensional_matrix.push_back(j);
        }
    }
    return BozoSort(one_dimensional_matrix, direction);
}


template<class T>
new_vector<T> BozoSort(T first, T second, T third, bool direction = true) {
    new_vector<T> three_elements;
    three_elements = { first, second, third };
    return BozoSort(three_elements, direction);
}


template<class T>
pair<new_vector<T>, new_matrix<T>> get_user_info()
{
    int leng;
    cout << "¬ведите число из которого можно извлечь квадратный корень: ";
    cin >> leng;
    new_matrix<T> matrix;
    new_vector<T> vector;
    new_vector<T> temporarily;

    cout << "¬ведите элементы массива через пробел: ";
    for (int i = 1; i <= leng; i++)
    {
        T element;
        cin >> element;
        temporarily.push_back(element);
        vector.push_back(element);
        if (i % int(sqrt(leng)) == 0)
        {
            matrix.push_back(temporarily);
            temporarily.clear();
        }
    }
    return { vector, matrix };
}