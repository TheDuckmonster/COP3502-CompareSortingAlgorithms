#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;



// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r)
{
	//initialize temp array and allocate memory
	int* tempArray = (int*) malloc((r-l+1)*sizeof(int));
	extraMemoryAllocated += (r - l + 1)*sizeof(int);

	//Merge sorted lists into temp array
	int indexL = l;
	int indexR = m+1;
	for (int i = 0; i <= r-l; i++)
	{
		if (indexL > m) //indicates that the left array is empty
		{
			tempArray[i] = pData[indexR];
			indexR++;
		}
		else if (indexR > r) //indicates that the right array is empty
		{
			tempArray[i] = pData[indexL];
			indexL++;
		}
		else
		{
			if (pData[indexL] < pData[indexR]) //insert left array value if smaller than right array value
			{
				tempArray[i] = pData[indexL];
				indexL++;
			}
			else //otherwise insert right array value
			{
				tempArray[i] = pData[indexR];
				indexR++;
			}
		}
	}

	//replace values in original array with temp array values
	for (int i = l; i <= r; i++)
	{
		pData[i] = tempArray[i-l];
	}

	free(tempArray);
}


void mergeSort(int pData[], int l, int r)
{
	if (l < r) //if l >= r, then the list is already sorted
	{
		int m = (l + r)/2;
		mergeSort(pData, l, m); //left side
		mergeSort(pData,m+1,r); //right side
		merge(pData, l, m, r); //merge sorted sides
	}
	
}


// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	for (int i = 1; i < n; i++)
	{
		int temp = pData[i]; //value to be sorted
		int j = 0;
		for (j = i; j > 0; j--)
		{
			if (pData[j-1] > temp) //Shift values to the right until temp is the smallest value
			{
				pData[j] = pData[j-1];
			}
			else break;
		}
		//insert temp
		pData[j] = temp;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < n-i-1; j++)
		{
			if (pData[j] > pData[j+1]) //Swap adjacent numbers if latter is larger
			{
				int temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		//Initialize temporary variables for lowest array value and its index
		int temp = pData[i];
		int index = i;
		for (int j = i+1; j < n; j++)
		{
			if (temp > pData[j]) //assigns lowest array value to temp (and the array position to index)
			{
				temp = pData[j];
				index = j;
			}
		}
		//Swap lowest discovered value with current array position
		pData[index] = pData[i];
		pData[i] = temp;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		int* tempData = (int*) malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for (int i = 0; i < dataSz; i++)
		{
			fscanf(inFile, "%d", &tempData[i]);
		}
		*ppData = tempData;
	}



	fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}