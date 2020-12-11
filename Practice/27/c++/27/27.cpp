#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> new_vector;

void print_vector(new_vector arr) {
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    new_vector vector;

    int n;
    cout << "Введите количество сигналов: ";
    cin >> n;

    int element;
    cout << "Введите сигналы через пробел: ";
    cin >> element;
    vector.push_back(element);
    cout << vector[0] << endl;

    for (int i = 1; i < n; i++) {
        cin >> element;
        
        int j = 0;
        for (j = 0; j < vector.size(); j++) {
            if (element > vector[j]) {
                vector.insert(vector.begin() + j, element);
                break;
            }
        }

        if (j == 5 or j == vector.size()){
            vector.push_back(element);
        }

        if (vector.size() > 5){
            vector.erase(vector.begin());
        }

        print_vector(vector);
    }
}