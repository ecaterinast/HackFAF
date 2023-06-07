
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>



int* create_array(int n)
{
    srand(time(NULL));
    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        array[i] = rand() % 100;
    }
    return array;
}

void print_array(int* array, int n)
{
    {
        for (int i = 0; i < n; i++)
            printf("Pozitia %d: %d\n", i, *(array + i));
    }
}

void free_array(int* array)
{
    free(array);
}

void merge(int *tab, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = tab[l + i];
    for (j = 0; j < n2; j++)
        R[j] = tab[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            tab[k] = L[i];
            i++;
        }
        else
        {
            tab[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        tab[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        tab[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *tab, int l, int r)
{
if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(tab, l, m);
        mergeSort(tab, m+1, r);
        merge(tab, l, m, r);
    }
}

void quick_sort(int* array, int n)
{
    if (n < 2)
    {
        return;
    }
    int mid = array[n / 2];
    int* left = array;
    int* right = array + n - 1;
    while (left <= right)
    {
        if (*left < mid)
        {
            left++;
        }
        else if (*right > mid)
        {
            right--;
        }
        else
        {
            int t = *left;
            *left = *right;
            *right = t;
            left++;
            right--;
        }
    }
    quick_sort(array, right - array + 1);
    quick_sort(left, array + n - left);
}

int menu()
{
    int error_input_found = 0;
menu_start:
    system("cls");
    printf("Meniu\n");
    printf("1)Initializeaza tabloul \n");
    printf("2)Afiseaza tabloul \n");
    printf("3)Merge Sort \n");
    printf("4)Quick sort \n");
    printf("5)Eliberarea memoriei tabloului \n");
    printf("0)Inchide programul \n");

    int command = 10;
    if (error_input_found)
    {
        printf("\nAlegeti o optiune de mai sus!\n");
    }
    printf("\nSelectati commanda: ");
    scanf("%d",&command);

    if ((command > 5) || (command < 0))
    {
        error_input_found = 1;
        goto menu_start;
    }
    return command;
}

int main()
{
    int n, i;
    int* ptr = 0;
    int* array;
    int command = 10;
    while (command)
    {
        command = menu();
        if (command == 1)
        {
            printf("Dati numarul de elemente:\n");
            scanf("%d",&n);;
            ptr = create_array(n);
        }
        switch (command)
        {
        case 2:
        {
            if (ptr == NULL)
            {
                printf("Tabloul este NULL\n");
            }
            else
            {
                print_array(ptr, n);
            }
            break;
        }
        case 3:
        {
            clock_t start = clock();
            mergeSort(ptr, 0, n-1);
            clock_t end = clock();
            float time_t = (float)(end - start) / CLOCKS_PER_SEC;
            printf("%f", time_t);
            break;
        }
        case 4:
        {
            clock_t start = clock();
            quick_sort(ptr, n);
            clock_t end = clock();
            float time_t = (float)(end - start) / CLOCKS_PER_SEC;
            printf("%f", time_t);
            break;
        }
        case 5:
        {
            free(ptr);
            printf("Memoria a fost eliberata cu succes!\n");
            ptr = NULL;
            break;
        }
        }
        printf("\nTastati orice buton pentru a continua\n");
        getch();
    }
    return 0;
}