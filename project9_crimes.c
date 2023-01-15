/* Purpose: This program will sort states by rate of all violent crimes in descending order. */
/* Author: Kayla Homatas */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 1000
#define MAX_STATE_LEN 150
#define MAX_STATES 100

/* Declaring a structure for a state. The structure's members will include the state_name, population, assault rate, murder rate, rape rate, and violent robbery rate, all of which are per 100,000 population. */
struct state {
    char state_name[MAX_STATE_LEN + 1];
    int population;
    double assault_rate;
    double murder_rate;
    double rape_rate;
    double violent_robbery_rate;
};

/* Function prototype for the comparison function that will be used in the quicksort function. */
int compare_total_rates(const void *p, const void *q);

int main(void) {
  /* Declaring string variables for the names of the input and output file. The program then asks the user for the name of the input file and stores it in file_name. */
  char file_name[MAX_NAME + 1], file_name2[MAX_NAME + 8];
  printf("Enter the file name: ");
  scanf("%s", file_name);  

  /* Declaring file pointers for the input and output file. The program then opens the input file in reading mode. If there is an error while opening the file, the program will print an error message and exit the program. */
  FILE *pFile, *pFile2;
  pFile = fopen(file_name, "r");
  if (pFile == NULL) {
    printf("Error opening file\n");
    return 1;
  }
  
  /* Creating the name of the output file by adding "sorted_" as a prefix to the name of the input file. */
  strcpy(file_name2, "sorted_");
  strcat(file_name2, file_name);

  /* Opening the output file in writing mode. If there is an error while opening the file, the program will print an error message and exit the program. */
  pFile2 = fopen(file_name2, "w");
  if (pFile2 == NULL) {
    printf("Error opening file\n");
    return 1;
  }
  
  /* Initializing the number of states in the input file n to be 0. Also creating an array of state structures. */    
  int n = 0;
  struct state list[MAX_STATES];

  /* This while loop scans the entire input file and stores each field of data from the csv file into the corresponding member of the state structure. Every state becomes an element in the array of state structures. n is incremented after each iteration to count how many states are in the input file. */
  while (!feof(pFile)&&!ferror(pFile)) {
    fscanf(pFile, "%[^,], %d, %lf, %lf, %lf, %lf\n", list[n].state_name, &list[n].population, &list[n].assault_rate, &list[n].murder_rate, &list[n].rape_rate, &list[n].violent_robbery_rate); 
    n++;
  }
  
  /* Calling the quicksort function to sort the array of state structures. Passes in the array of unsorted states, the length of the array "n", the size of each state structure in bytes, and a pointer to the compare_total_rates function. */
  qsort(list, n, sizeof(struct state), compare_total_rates);
  
  /* This for loop iterates through each element in the newly sorted array of state structures and prints it to the output file in the same format as the input file. Each double is formatted to one decimal place. */
  int i;
  for (i = 0; i < n; i++) {
    fprintf(pFile2, "%s, %d, %.1lf, %.1lf, %.1lf, %.1lf\n", list[i].state_name, list[i].population, list[i].assault_rate, list[i].murder_rate, list[i].rape_rate, list[i].violent_robbery_rate); 
  }
 
  /* The program prints the name of the sorted output file to the user. */
  printf("Output file name: %s\n", file_name2);

  /* Closing the files before exiting the program. */
  fclose(pFile);
  fclose(pFile2);

  return 0;
}

/**********************************************************************************
 * compare_total_rates: Compares the total rates of violent crimes of two states. *
 *                      The function has two parameters: two constant generic     *
 *                      pointers that point to places in memory. The function     *
 *                      returns an integer based on the result of the comparison  * 
 *                      of the total rates of violent crime of the two states.    *
 *********************************************************************************/
int compare_total_rates(const void *p, const void *q) {

  /* Assigning the parameters p and q to variables of type struct state. */
  const struct state *p1 = p;
  const struct state *q1 = q;

  /* Calculating the total rate of violent crimes for each state parameter. */
  double total_rate_p1 = p1->assault_rate + p1->murder_rate + p1->rape_rate + p1->violent_robbery_rate;
  double total_rate_q1 = q1->assault_rate + q1->murder_rate + q1->rape_rate + q1->violent_robbery_rate;  

  /* Comparing the parameters: returns 1 if the total rate of p2 is greater than p1, 0 if they are equal, and -1 if p2 is less than p1. This will sort the states in order of highest to lowest total rates. */
  if (total_rate_p1 < total_rate_q1) {
    return 1;
  }
  else if (total_rate_p1 == total_rate_q1) {
    return 0;
  }
  else {
    return -1;
  }

}
