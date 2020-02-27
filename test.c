#include <stdio.h>
#include <stdlib.h>

void push(int *arr, int i, int value, int *CurrentCapacity, int *MaxCapacity)
{
    if (*CurrentCapacity > *MaxCapacity)
    {
        realloc(arr, sizeof(arr) * 2);
        *MaxCapacity = sizeof(arr) * 2;
    }
    arr[i] = value;
    *CurrentCapacity = *CurrentCapacity + 1;
}


int main()
{   
    int CurrentCapacity = 0;
    int MaxCapacity = 2;
    int *arr = malloc(MaxCapacity * sizeof(int));

    push(arr, 0, 1, &CurrentCapacity, &MaxCapacity);
    push(arr, 1, 2, &CurrentCapacity, &MaxCapacity);
    push(arr, 2, 3, &CurrentCapacity, &MaxCapacity);

    printf("Table Max capacity: %d\n", MaxCapacity); // Current capacity: 2

    push(arr, 3, 4, &CurrentCapacity, &MaxCapacity);
    push(arr, 4, 5, &CurrentCapacity, &MaxCapacity);
    push(arr, 5, 6, &CurrentCapacity, &MaxCapacity);

    printf("Table Max capacity: %d\n", MaxCapacity); // Current capacity: 16
}
