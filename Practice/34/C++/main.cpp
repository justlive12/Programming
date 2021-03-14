#include <iostream>
#include <algorithm>

using namespace std;

int* create(int length, int start_num = 0, int step = 0)
{
    int* arr = new int[length];

    for (int i = 0; i < length; i++)
    {
        arr[i] = start_num;
        start_num += step;
    }

    return arr;
}

void create(int** arr, int length, int start_num, int step)
{
    *arr = create(length, start_num, step);
}

void destroy(int** arr)
{
    if (arr == nullptr)
    {
        return;
    }

    if (*arr)
    {
        delete[] * arr;
        *arr = nullptr;
    }
}

void sort(int* arr, int length)
{
    for (int i = 0; i < length - 1; ++i)
	{
		int smallElem = i;

		for (int currentElem = i + 1; currentElem < length; ++currentElem)
		{
			if (arr[currentElem] < arr[smallElem])
				smallElem = currentElem;
		}

		swap(arr[i], arr[smallElem]);
	}
}

int* print(int* arr, int length)
{
    cout << '[';
    for (int i = 0; i < length; i++)
    {
        cout << arr[i];

        if (i < length - 1)
        {
            cout <<", ";
        }
    }

    cout << ']' << std::endl;

    return arr;
}

int main()
{
    int length, start_num, step;

    std::cin >> length >> start_num >> step;

    int* arr;

    create(&arr, length, start_num, step);
    sort(arr, length);
    print(arr, length);
    destroy(&arr);

    return 0;
}
