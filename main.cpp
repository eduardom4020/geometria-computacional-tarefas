#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <stdlib.h>

void printValues(std::string title, std::vector<int> vector)
{
    std::cout << "\n" << title << std::endl;

    for(auto& value : vector)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

std::vector<int> selectionSort(std::vector<int> vector)
{
    for(int i=0; i < vector.size(); i++)
    {
        int selectedIndex = i;

        for(int j=i+1; j < vector.size(); j++)
        {
            if(vector[j] < vector[selectedIndex])
            {
                selectedIndex = j;
            }
        }

        iter_swap(vector.begin() + i, vector.begin() + selectedIndex);
    }

    return vector;
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

    std::cout << "Question 2: SelectionSort" << std::endl;

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
}