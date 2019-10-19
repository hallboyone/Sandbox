"""
Math 590
Project 1
Fall 2019

Partner 1: Richard Hall
Date: October 28, 2019
"""

"""
SelectionSort
"""
def SelectionSort(listToSort):
    #Find the min element n times
    n = len(listToSort)
    for idx in range(0, n):
        #Var to hold the index to the lowest value found so far. 
        min_idx = idx
        
        #Scan each of the values after the current index
        #If the value is the lowest so far, save its index
        for i in range(idx+1, n):
            if (listToSort[min_idx] > listToSort[i]):
                min_idx = i
                pass
            pass
        
        #Swap the values
        temp_var = listToSort[idx]
        listToSort[idx] = listToSort[min_idx]
        listToSort[min_idx] = temp_var
        pass
    
    return listToSort

"""
InsertionSort
"""
def InsertionSort(listToSort):
    n = len(listToSort)
    for idx in range(1, n):
        sorted_idx = idx-1
        next_val = listToSort[idx]
        while(sorted_idx >= 0) & (listToSort[sorted_idx]>next_val):
            listToSort[sorted_idx+1] = listToSort[sorted_idx]
            sorted_idx = sorted_idx - 1;
            pass
        listToSort[sorted_idx+1] = next_val
        pass
    
    return listToSort

"""
BubbleSort
"""
def BubbleSort(listToSort):
    n = len(listToSort)
    swap_made = True
    
    #Variable to keep track of the number of iterations
    itr = 0
    
    #As long as swaps are being made, iterate through the elements
    while(swap_made):
        swap_made = False
        for idx in range(1,n-itr):
            #If elements are out of order, swap them
            if(listToSort[idx]<listToSort[idx-1]):
                swap_made = True
                tmp = listToSort[idx]
                listToSort[idx]=listToSort[idx-1]
                listToSort[idx-1]=tmp
                pass
            pass
        pass
    itr = itr + 1
    pass
    return listToSort

"""
MergeSort
"""
def MergeSort(listToSort):
    n=len(listToSort)
    
    #If the list is longer than a single element, split it and recursivly solve
    if n != 1:
        list_1 = MergeSort(listToSort[0:n//2])
        list_2 = MergeSort(listToSort[n//2:n])
        
        #Get the length of each sublist and set up the indexes
        n_1 = len(list_1)
        n_2 = len(list_2)
        idx_1 = 0
        idx_2 = 0
        idx = 0
        
        #Go through each sublist, merging them into the main list
        while (idx_1<n_1) & (idx_2 <n_2):
            if list_1[idx_1] < list_2[idx_2]:
                listToSort[idx] = list_1[idx_1]
                idx_1 += 1
            else:
                listToSort[idx] = list_2[idx_2]
                idx_2 += 1
                pass
            idx += 1
            pass
        
        #Finish the first list if not done already
        while idx_1 < n_1:
            listToSort[idx] = list_1[idx_1]
            idx += 1
            idx_1 += 1
            pass
        
        #finish the second list if not done already
        while idx_2 < n_2:
            listToSort[idx] = list_2[idx_2]
            idx += 1
            idx_2 += 1
            
            pass
        pass
    return listToSort

"""
QuickSort

Sort a list with the call QuickSort(listToSort),
or additionally specify i and j.
"""
def QuickSort(listToSort, i=0, j=None):
    # Set default value for j if None.
    if j == None:
        j = len(listToSort)
    return listToSort

"""
Importing the testing code after function defs to ensure same references.
"""
from project1tests_updated import *

"""
Main function.
"""
if __name__ == "__main__":
    print('Testing Selection Sort')
    print()
    testingSuite(SelectionSort)
    print()
    print('Testing Insertion Sort')
    print()
    testingSuite(InsertionSort)
    print()
    print('Testing Bubble Sort')
    print()
    testingSuite(BubbleSort)
    print()
    print('Testing Merge Sort')
    print()
    testingSuite(MergeSort)
    print()
    print('Testing Quick Sort')
    print()
    testingSuite(QuickSort)
    print()
    print('DEFAULT measureTime')
    print()
    measureTime()
