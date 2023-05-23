//Yassin Younis 22101310
#include <iostream>
#include "findMedian.h"


int main() {

    double duration;
    srand((unsigned) time(NULL));
    clock_t startTime;

    int ARR_SIZE = 400000;
    int* arr_1 = new int[ARR_SIZE];
    int* arr_2 = new int[ARR_SIZE];
    int* arr_3 = new int[ARR_SIZE];

    for (int i=0; i<ARR_SIZE; i++) {
        arr_1[i] = rand()%100000; //random number between 0 and 100,000 (0 included).
        if (rand()%2) { //50% chance of a negative number
            arr_1[i] *= -1;
        }
        arr_2[i] = arr_1[i]; //copying
        arr_3[i] = arr_1[i]; //copying
    }

    startTime = clock();

    FIND_MEDIAN_1(arr_1, ARR_SIZE);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    std::cout << "FIND_MEDIAN_1 took " << duration << "ms" << std::endl;

    startTime = clock();

    FIND_MEDIAN_2(arr_2, ARR_SIZE);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    std::cout << "FIND_MEDIAN_2 took " << duration << "ms" << std::endl;

    startTime = clock();

    FIND_MEDIAN_3(arr_3, ARR_SIZE);

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    std::cout << "FIND_MEDIAN_3 took " << duration << "ms" << std::endl;

    delete [] arr_1; //deallocating...
    delete [] arr_2; //deallocating...
    delete [] arr_3; //deallocating...

    return 0;
}
