#include <stdio.h>

void insertionSort(int a[],int n) {
    for(int i=1;i<n;i++) {
        int temp = a[i];
        int j = i-1;
        
        while(j>=0 && a[j]> temp) 
        //while(j>=0 && a[j] < temp) => for descending 
        {
            a[j+1] = a[j];
            j--;
        }
        
        a[j+1] = temp;
    }
    /*
    TIME COMPLEXITY
    WORST CASE = O(N^2)
    BEST CASE = O(N)
*/
}

void selectionSort(int a[],int n) {
    for(int i=0;i<n-1;i++) {
        int min = i;

        for(int j=i+1;j<n;j++) {
            if(a[j] < a[min])
                min=j;    
        }

        if(min!=i) {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }

     /*
    TIME COMPLEXITY
    WORST CASE = BEST CASE = O(N^2)
*/
}

// QUICK SORT

int partition (int arr[],int low,int high) {
    int pivot = arr[high];
    int i = low-1;

    for(int j=low;j<high;j++) {
        if(arr[j]<pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return i+1;
}

void quickSort(int arr[],int low,int high) {
    if(low<high) {
        int pi = partition(arr,low,high);
        quickSort(arr,pi,low-1);
        quickSort(arr,pi+1,high);
    }
}

// MERGE SORT

void merge(int arr[],int left,int mid, int right) {
    int n1 = mid-left+1;
    int n2 = right - mid;
    
    int L[n1], R[n2];

    for(int i=0;i<n1;i++)
        L[i] = arr[left+i];

    for(int i=0;i<n2;i++)
        R[i] = arr[mid+1+i];
    
    int i=0,j=0,k=left;

    while(i<n1 && j<n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1) {
        arr[k] = L[i];
        i++;k++;
    }
    while(j<n2) {
        arr[k] = R[j];
        j++;k++;
    }

}

void mergeSort(int arr[],int left,int right) {
    if(left<right) {
        int mid = left+(right-left)/2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}

/* HEAP SORT */
void heapify(int arr[],int n,int i) {
    int largest = i;

    int left = 2*i+1;
    int right = 2*i+2;

    while(left < n && arr[left] > arr[largest])
        largest = left;

    while(right < n && arr[right] > arr[largest])
        largest = right;

    if(largest!=i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr,n,largest);
    }
}

void heapSort(int arr[],int n) {
    for(int i = n/2 -1;i>=0;i--)
        heapify(arr,n,i);

    for(int i =n-1;i>=0;i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr,n,0);
    }
}

void main() {
    int arr[20],n;
    printf("Enter the no.of elts\n");
    scanf("%i",&n);
    printf("Enter the elts\n");
    for(int i=0;i<n;i++) 
        scanf("%i",&arr[i]);
    
    insertionSort(arr,n);
    selectionSort(arr,n);
        
    printf("Sorted\n");
    for(int i=0;i<n;i++) 
        printf("%i\t",arr[i]);
}