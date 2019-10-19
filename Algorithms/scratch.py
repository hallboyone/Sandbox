
listToSort = [3, 4, 3, 7, -98, 13.4, 6, 1, 4, 1000000, 0]
#listToSort = [0]
print(listToSort)

# for idx in range(0, len(list)):
#     min_idx = idx
#     for i in range(idx+1, len(list)):
#         if (list[min_idx] > list[i]):
#             min_idx = i
#             pass
#         pass
#     temp_var = list[idx]
#     list[idx] = list[min_idx]
#     list[min_idx] = temp_var
#     print(list)
#     pass

# n = len(listToSort)
# for idx in range(1, n):
#     sorted_idx = idx-1
#     next_val = listToSort[idx]
#     while(sorted_idx >= 0) & (listToSort[sorted_idx]>next_val):
#         listToSort[sorted_idx+1] = listToSort[sorted_idx]
#         sorted_idx = sorted_idx - 1;
#         pass
#     listToSort[sorted_idx+1] = next_val
#     print(listToSort)
#     pass

# n = len(listToSort)
# swap_made = True
# itr = 0
# while(swap_made):
#     swap_made = False
#     for idx in range(1,n-itr):
#         if(listToSort[idx]<listToSort[idx-1]):
#             swap_made = True
#             tmp = listToSort[idx]
#             listToSort[idx]=listToSort[idx-1]
#             listToSort[idx-1]=tmp
#             print(listToSort)
#             pass
#         pass
#     pass



# def merge_sort(cur_list):
#     n=len(cur_list)
    
#     #If the list is longer than a single element, split it and recursivly solve
#     if n != 1:
#         list_1 = merge_sort(cur_list[0:n//2])
#         list_2 = merge_sort(cur_list[n//2:n])
        
#         #Get the length of each sublist and set up the indexes
#         n_1 = len(list_1)
#         n_2 = len(list_2)
#         idx_1 = 0
#         idx_2 = 0
#         idx = 0
        
#         #Go through each sublist, merging them into the main list
#         while (idx_1<n_1) & (idx_2 <n_2):
#             if list_1[idx_1] < list_2[idx_2]:
#                cur_list[idx] = list_1[idx_1]
#                idx_1 += 1
#             else:
#                 cur_list[idx] = list_2[idx_2]
#                 idx_2 += 1
#                 pass
#             idx += 1
#             pass
        
#         #Finish the first list if not done already
#         while idx_1 < n_1:
#             cur_list[idx] = list_1[idx_1]
#             idx += 1
#             idx_1 += 1
#             pass
        
#         #finish the second list if not done already
#         while idx_2 < n_2:
#             cur_list[idx] = list_2[idx_2]
#             idx += 1
#             idx_2 += 1
            
#             pass
#         pass
    
#     return cur_list

# merge_sort(listToSort);

def QuickSort(listToSort, i=0, j=None):
    # Set default value for j if None.
    if j == None:
        j = len(listToSort)
        pass

    if i!=j:
        #Compute the median value of the values at i, j, and (j-i)//2
        #Swap to the back of the list
        val_first = listToSort[i]
        val_mid = listToSort[(j-i)//2]
        val_last = listToSort[j-1]
        if val_first <= val_mid <= val_last:
            pivot = val_mid
            listToSort[(j-i)//2] = val_last
            listToSort[j-1] = pivot
        elif val_first <= val_last <= val_mid:
            pivot = val_last
        else:
            pivot = val_first
            listToSort[i] = val_last
            listToSort[j-1] = pivot
            pass
        
        #Partition the list
        idx_small = i
        idx_pivot = j-1
        while idx_small < idx_pivot:
            if listToSort[idx_small] > pivot:
                listToSort[idx_pivot] = listToSort[idx_small]
                listToSort[idx_small] = listToSort[idx_pivot -1]
                listToSort[idx_pivot - 1] = pivot
                idx_pivot -= 1
            else:
                idx_small += 1
                pass
            
            pass
        print(listToSort)
        listToSort = QuickSort(listToSort, i, idx_pivot)
        listToSort = QuickSort(listToSort, idx_pivot + 1, j)
        pass
    return listToSort

QuickSort(listToSort)
