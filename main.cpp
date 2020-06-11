#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <stdlib.h>

void printValues(std::string title, std::vector<int> array)
{
    std::cout << "\n" << title << std::endl;

    for(auto& value : array)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

std::vector<int> selectionSort(std::vector<int> array)
{
    for(int i=0; i < array.size(); i++)
    {
        int selectedIndex = i;

        for(int j=i+1; j < array.size(); j++)
        {
            if(array[j] < array[selectedIndex])
            {
                selectedIndex = j;
            }
        }

        std::iter_swap(array.begin() + i, array.begin() + selectedIndex);
    }

    return array;
}

int partition(int* array, int startIndex, int endIndex)
{
    int index = startIndex;
    int pivotIndex = endIndex;
    int pivot = array[pivotIndex];

    for(int i=startIndex; i < endIndex; i++)
    {
        if(array[i] <= pivot)
        {
            std::swap(array[index], array[i]);
            index++;
        }
    }

    std::swap(array[index], array[endIndex]);

    return index;
}

void quickSort(int* array, int startIndex, int endIndex)
{
    int index;
    
    if(startIndex < endIndex)
    {
        index = partition(array, startIndex, endIndex);
        quickSort(array, startIndex, index-1);
        quickSort(array, index+1, endIndex);
    }
}

int main(int argc, char const *argv[])
{
    std::cout << "Homework 1: Sorting Algorithms" << std::endl;

    std::vector<int> sortedV10 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::vector<int> v10(10);
    std::generate(v10.begin(), v10.end(), std::rand);

    std::vector<int> v100(100);
    std::generate(v100.begin(), v100.end(), std::rand);

    std::vector<int> v1000(1000);
    std::generate(v1000.begin(), v1000.end(), std::rand);

    std::cout << "\nQuestion 2: SelectionSort" << std::endl;

    printValues("Sorting 10 random points:", v10);
    std::vector<int> resultSelectionV10 = selectionSort(v10);
    printValues("10 random points sorteds:", resultSelectionV10);

    printValues("Sorting 100 random points:", v100);
    std::vector<int> resultSelectionV100 = selectionSort(v100);
    printValues("100 random points sorteds:", resultSelectionV100);

    printValues("Sorting 1000 random points:", v1000);
    std::vector<int> resultSelectionV1000 = selectionSort(v1000);
    printValues("1000 random points sorteds:", resultSelectionV1000);

    printValues("Sorting 10 already sorted:", sortedV10);
    std::vector<int> resultSelectionV10AlreadySorted = selectionSort(sortedV10);
    printValues("10 random points sorteds:", resultSelectionV10AlreadySorted);

    std::cout << "\nQuestion 3: QuickSort" << std::endl;

    printValues("Sorting 10 random points:", v10);
    std::vector<int> resultQuickV10 = v10;
    quickSort(resultQuickV10.data(), 0, resultQuickV10.size() - 1);
    printValues("10 random points sorteds:", resultQuickV10);

    printValues("Sorting 100 random points:", v100);
    std::vector<int> resultQuickV100 = v100;
    quickSort(resultQuickV100.data(), 0, resultQuickV100.size() - 1);
    printValues("100 random points sorteds:", resultQuickV100);

    printValues("Sorting 1000 random points:", v1000);
    std::vector<int> resultQuickV1000 = v1000;
    quickSort(resultQuickV1000.data(), 0, resultQuickV1000.size() - 1);
    printValues("1000 random points sorteds:", resultQuickV1000);

    printValues("Sorting 10 already sorted:", sortedV10);
    std::vector<int> resultQuickV10AlreadySorted = sortedV10;
    quickSort(resultQuickV10AlreadySorted.data(), 0, resultQuickV10AlreadySorted.size() - 1);
    printValues("10 random points sorteds:", resultQuickV10AlreadySorted);
}