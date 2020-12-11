#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef vector<int> new_vector;
typedef vector<vector<int>> new_matrix;


void print_vector(new_vector arr) {
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;
}


bool is_sorted(new_vector arr, bool direction = true) {
    
    int arr_len = arr.size();
    if (direction){
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


new_vector BozoSort(new_vector arr, bool direction = true) {
    int arr_len = arr.size();
    while (!is_sorted(arr, direction)) {

        int first = rand() % arr_len;
        int second = rand() % arr_len;
        swap(arr[first], arr[second]);
        
    }
    return arr;
}

new_vector BozoSort(new_matrix arr, bool direction = true) {
    new_vector one_dimensional_matrix;
    for (new_vector i : arr) {
        for (int j : i) {
            one_dimensional_matrix.push_back(j);
        }
    }
    return BozoSort(one_dimensional_matrix, direction);
}


new_vector BozoSort(int first, int second, int third, bool direction = true) {
    new_vector three_elements;
    three_elements = { first, second, third };
    return BozoSort(three_elements, direction);
}


int main()
{
    setlocale(LC_ALL, "ru");

    int n;
    cout << "Введите число из которого можно извлечь квадратный корень: ";
    cin >> n;
    new_matrix matrix;
    new_vector vector;
    new_vector temporarily;

    cout << "Введите элементы массива через пробел: ";
    for (int i = 1; i <= n; i++)
    {
        int num;
        cin >> num;
        temporarily.push_back(num);
        vector.push_back(num);
        if (i % int(std::sqrt(n)) == 0)
        {
            matrix.push_back(temporarily);
            temporarily.clear();
        }
    }

    
    print_vector(BozoSort(vector, true));
    print_vector(BozoSort(vector, false));
    print_vector(BozoSort(matrix, true));
    print_vector(BozoSort(matrix, false));
    print_vector(BozoSort(vector[0], vector[1], vector[2], true));
    print_vector(BozoSort(vector[0], vector[1], vector[2], false));
}

