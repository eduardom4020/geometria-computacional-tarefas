#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include <stdlib.h>
#include <chrono>

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

std::vector<int> merge(std::vector<int> left, std::vector<int> right)
{
	int i = 0;
    int j = 0;

    int left_len = left.size();
    int right_len = right.size();

	std::vector<int> merged;

	while(i < left_len && j < right_len)
	{
		if(left[i] < right[j]) {
			merged.push_back(left[i]);
            i++;
		} else {
			merged.push_back(right[j]);
            j++;
		}
	}

	while(i < left_len) {
		merged.push_back(left[i]);
        i++;
	}

	while(j < right_len) {
		merged.push_back(right[j]);
        j++;
	}

	return merged;
}

std::vector<int> mergeSort(std::vector<int> array)
{
    int len = array.size();

	if(len <= 1)
	{
		return array;
	}

	int pivot = len/2;

    std::vector<int> leftSlice(array.begin(), array.begin() + pivot);
	std::vector<int> rightSlice(array.begin() + pivot, array.end());
    
	std::vector<int> leftArray = mergeSort(leftSlice);
	std::vector<int> rightArray = mergeSort(rightSlice);
	return merge(leftArray, rightArray);
}

//TODO: Correct this to use points with x and y coordinates
bool isPolygonalLine(std::vector<int> points, std::string sortAlgorithm)
{
    std::vector<int> sortedPoints;

    if(sortAlgorithm == "selection")
    {
        sortedPoints = selectionSort(points);
    }
    else if(sortAlgorithm == "quick")
    {
        sortedPoints = points;
        quickSort(sortedPoints.data(), 0, sortedPoints.size() - 1);
    }
    else
    {
        sortedPoints = mergeSort(points);
    }

    for(int i=0; i < sortedPoints.size(); i++)
    {
        if(i > 0 && sortedPoints[i] == sortedPoints[i-1])
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char const *argv[])
{
    std::cout << "Homework 1: Sorting Algorithms" << std::endl;
    bool showDetails = argc >= 2 && std::string(argv[1]) == "detailed";

    std::vector<int> sortedV10 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> sortedV1000(1000);
    std::iota(sortedV1000.begin(), sortedV1000.end(), 0);

    std::vector<int> v10(10);
    std::generate(v10.begin(), v10.end(), std::rand);

    std::vector<int> v100(100);
    std::generate(v100.begin(), v100.end(), std::rand);

    std::vector<int> v1000(1000);
    std::generate(v1000.begin(), v1000.end(), std::rand);

//SELECTION SORT
    auto startSelectionV10 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultSelectionV10 = selectionSort(v10);
    auto endSelectionV10 = std::chrono::high_resolution_clock::now();
    auto timeSelectionV10 = std::chrono::duration_cast<std::chrono::nanoseconds>(endSelectionV10 - startSelectionV10);

    auto startSelectionV100 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultSelectionV100 = selectionSort(v100);
    auto endSelectionV100 = std::chrono::high_resolution_clock::now();
    auto timeSelectionV100 = std::chrono::duration_cast<std::chrono::nanoseconds>(endSelectionV100 - startSelectionV100);

    auto startSelectionV1000 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultSelectionV1000 = selectionSort(v1000);
    auto endSelectionV1000 = std::chrono::high_resolution_clock::now();
    auto timeSelectionV1000 = std::chrono::duration_cast<std::chrono::nanoseconds>(endSelectionV1000 - startSelectionV1000);

    auto startSelectionV10AlreadySorted = std::chrono::high_resolution_clock::now();
    std::vector<int> resultSelectionV10AlreadySorted = selectionSort(sortedV10);
    auto endSelectionV10AlreadySorted = std::chrono::high_resolution_clock::now();
    auto timeSelectionV10AlreadySorted = std::chrono::duration_cast<std::chrono::nanoseconds>(endSelectionV10AlreadySorted - startSelectionV10AlreadySorted);

//QUICK SORT
    auto startQuickV10 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultQuickV10 = v10;
    quickSort(resultQuickV10.data(), 0, resultQuickV10.size() - 1);
    auto endQuickV10 = std::chrono::high_resolution_clock::now();
    auto timeQuickV10 = std::chrono::duration_cast<std::chrono::nanoseconds>(endQuickV10 - startQuickV10);

    auto startQuickV100 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultQuickV100 = v100;
    quickSort(resultQuickV100.data(), 0, resultQuickV100.size() - 1);
    auto endQuickV100 = std::chrono::high_resolution_clock::now();
    auto timeQuickV100 = std::chrono::duration_cast<std::chrono::nanoseconds>(endQuickV100 - startQuickV100);

    auto startQuickV1000 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultQuickV1000 = v1000;
    quickSort(resultQuickV1000.data(), 0, resultQuickV1000.size() - 1);
    auto endQuickV1000 = std::chrono::high_resolution_clock::now();
    auto timeQuickV1000 = std::chrono::duration_cast<std::chrono::nanoseconds>(endQuickV1000 - startQuickV1000);

    auto startQuickV1000AlreadySorted = std::chrono::high_resolution_clock::now();
    std::vector<int> resultQuickV1000AlreadySorted = sortedV1000;
    quickSort(resultQuickV1000AlreadySorted.data(), 0, resultQuickV1000AlreadySorted.size() - 1);
    auto endQuickV1000AlreadySorted = std::chrono::high_resolution_clock::now();
    auto timeQuickV1000AlreadySorted = std::chrono::duration_cast<std::chrono::nanoseconds>(endQuickV1000AlreadySorted - startQuickV1000AlreadySorted);

//MERGE SORT
    auto startMergeV10 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultMergeV10 = mergeSort(v10);
    auto endMergeV10 = std::chrono::high_resolution_clock::now();
    auto timeMergeV10 = std::chrono::duration_cast<std::chrono::nanoseconds>(endMergeV10 - startMergeV10);

    auto startMergeV100 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultMergeV100 = mergeSort(v100);
    auto endMergeV100 = std::chrono::high_resolution_clock::now();
    auto timeMergeV100 = std::chrono::duration_cast<std::chrono::nanoseconds>(endMergeV100 - startMergeV100);

    auto startMergeV1000 = std::chrono::high_resolution_clock::now();
    std::vector<int> resultMergeV1000 = mergeSort(v1000);
    auto endMergeV1000 = std::chrono::high_resolution_clock::now();
    auto timeMergeV1000 = std::chrono::duration_cast<std::chrono::nanoseconds>(endMergeV1000 - startMergeV1000);

    auto startMergeV10AlreadySorted = std::chrono::high_resolution_clock::now();
    std::vector<int> resultMergeV10AlreadySorted = mergeSort(sortedV10);
    auto endMergeV10AlreadySorted = std::chrono::high_resolution_clock::now();
    auto timeMergeV10AlreadySorted = std::chrono::duration_cast<std::chrono::nanoseconds>(endMergeV10AlreadySorted - startMergeV10AlreadySorted);

    std::cout << "\n\nQuestion 2: SelectionSort" << std::endl;

    if(showDetails)
    {
        printValues("Sorting 10 random points:", v10);
        printValues("10 random points sorteds:", resultSelectionV10);

        printValues("Sorting 100 random points:", v100);
        printValues("100 random points sorteds:", resultSelectionV100);

        printValues("Sorting 1000 random points:", v1000);
        printValues("1000 random points sorteds:", resultSelectionV1000);

        printValues("Sorting 10 already sorted:", sortedV10);
        printValues("10 random points sorteds:", resultSelectionV10AlreadySorted);
    }

    std::cout << "\n" << "Time to sort 10 random points: " << timeSelectionV10.count() << " ns" << std::endl;
    std::cout << "Time to sort 100 random points: " << timeSelectionV100.count() << " ns" << std::endl;
    std::cout << "Time to sort 1000 random points: " << timeSelectionV1000.count() << " ns" << std::endl;
    std::cout << "Time to sort 10 already sorted points: " << timeSelectionV10AlreadySorted.count() << " ns" << std::endl;

    std::cout << "\n\nQuestion 3: QuickSort" << std::endl;

    if(showDetails)
    {
        printValues("Sorting 10 random points:", v10);
        printValues("10 random points sorteds:", resultQuickV10);

        printValues("Sorting 100 random points:", v100);
        printValues("100 random points sorteds:", resultQuickV100);

        printValues("Sorting 1000 random points:", v1000);
        printValues("1000 random points sorteds:", resultQuickV1000);

        printValues("Sorting 1000 already sorted:", sortedV1000);
        printValues("10 random points sorteds:", resultQuickV1000AlreadySorted);
    }

    std::cout << "\n" << "Time to sort 10 random points: " << timeQuickV10.count() << " ns" << std::endl;
    std::cout << "Time to sort 100 random points: " << timeQuickV100.count() << " ns" << std::endl;
    std::cout << "Time to sort 1000 random points: " << timeQuickV1000.count() << " ns" << std::endl;
    std::cout << "Time to sort 1000 already sorted points: " << timeQuickV1000AlreadySorted.count() << " ns" << std::endl;

    std::cout << "\n\nQuestion 4: MergeSort" << std::endl;

    if(showDetails)
    {
        printValues("Sorting 10 random points:", v10);
        printValues("10 random points sorteds:", resultMergeV10);

        printValues("Sorting 100 random points:", v100);
        printValues("100 random points sorteds:", resultMergeV100);

        printValues("Sorting 1000 random points:", v1000);
        printValues("1000 random points sorteds:", resultMergeV1000);

        printValues("Sorting 10 already sorted:", sortedV10);
        printValues("10 random points sorteds:", resultMergeV10AlreadySorted);
    }

    std::cout << "\n" << "Time to sort 10 random points: " << timeMergeV10.count() << " ns" << std::endl;
    std::cout << "Time to sort 100 random points: " << timeMergeV100.count() << " ns" << std::endl;
    std::cout << "Time to sort 1000 random points: " << timeMergeV1000.count() << " ns" << std::endl;
    std::cout << "Time to sort 10 already sorted points: " << timeMergeV10AlreadySorted.count() << " ns" << std::endl;

    std::cout << "\n\nQuestion 6: PolygonalLine" << std::endl;

    std::vector<int> polyLineValid = { 3, 6, 1, 20, 8, 9, 10, 4, 13 };
    std::vector<int> polyLineInvalid = { 3, 6, 1, 20, 1, 9, 10, 4, 13 }; 

    printValues("\nPoints make a polygonal line? ", polyLineValid);
    std::cout << "Reducing to Selection Sort " << (isPolygonalLine(polyLineValid, "selection") ? "Yes" : "No") << std::endl;
    std::cout << "Reducing to Quick Sort " << (isPolygonalLine(polyLineValid, "quick") ? "Yes" : "No") << std::endl;
    std::cout << "Reducing to Merge Sort " << (isPolygonalLine(polyLineValid, "merge") ? "Yes" : "No") << std::endl;

    printValues("\nPoints make a polygonal line? ", polyLineInvalid);
    std::cout << "Reducing to Selection Sort " << (isPolygonalLine(polyLineInvalid, "selection") ? "Yes" : "No") << std::endl;
    std::cout << "Reducing to Quick Sort " << (isPolygonalLine(polyLineInvalid, "quick") ? "Yes" : "No") << std::endl;
    std::cout << "Reducing to Merge Sort " << (isPolygonalLine(polyLineInvalid, "merge") ? "Yes" : "No") << std::endl;
}