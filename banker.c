/**
 * CS143A - Fall 2015
 * HW #6
 * @author: Kevin Carlisle
 *          ID# 82682616
 *
 * Banker Algorithm
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( int argc, char* arvg[] )
{
	int numP = -1; // Num Processes
	int numR = -1; // Num Resoucres

	scanf("%d", &numP);
	scanf("%d", &numR);

	// Simple Error Check
	if ( numP < 1 || numR < 1) {
		perror("Processes Or Resources < 1\n");
		exit(1); }

	// Dynamically Allocate 
	int* maxVector   = calloc( numR, sizeof(int));        // Max Vector
	int* avaVector   = calloc( numR, sizeof(int));        // Available Vector
	int* stateVector = calloc( numP, sizeof(int));        // States
	int* currentM    = calloc( numP * numR, sizeof(int)); // Current Matrix
	int* maxM        = calloc( numP * numR, sizeof(int)); // Max Matrix
	int* needM       = calloc( numP * numR, sizeof(int)); // Need Matrix



	// Read Input -----------------------------------------------------------
	// Fill Vector
	int i;
	for(i = 0; i < numR; ++i)
	{
		scanf("%d", &maxVector[i]);
	}
	
	// Fill Current Matrix
	int j;
	for(i=0; i < numP; i++) {
  		for(j=0; j < numR; j++) {
	    	scanf("%d", &currentM[i*numR +j]);
  		}
	}

	// Fill Max Matrix
	for(i=0; i < numP; i++) {
  		for(j=0; j < numR; j++) {
	    	scanf("%d", &maxM[i*numR +j]);
  		}
	}

	// Fill State Vector -> Initially 0
	for(i = 0; i < numP; ++i) {
		stateVector[i] = 0;
	}
	// Fill Avalable Vector -> Initially 0
	for(i = 0; i < numR; ++i) {
		avaVector[i] = maxVector[i];
	}

	// Calculations -----------------------------------------------
	// Set Need Matrix
	for(i=0; i < numP; i++) {
  		for(j=0; j < numR; j++) {
	    	 needM[i*numR +j] = maxM[i*numR +j] - currentM[i*numR +j];
  		}
	}

	/*
	printf("Ava Vector\n");
	for( i = 0; i < numR; ++i)
	{
		printf(" %d", avaVector[i]);
	}
	printf("\n");
	*/

	// Set available vector -> current available resources
	for(i=0; i < numP; ++i) {
		for(j = 0; j < numR; ++j) {
			avaVector[j] -= currentM[i*numR + j];
		}
	}

	/*
	printf("Ava Vector\n");
	for( i = 0; i < numR; ++i)
	{
		printf(" %d", avaVector[i]);
	}
	printf("\n");
	*/


	// Algorithm do while true
	int flag = 0;
	do 
	{
		flag = 0;
		// Run Algorithm until all jobs are complete
		// Or no jobs process in a loop
		for( i = 0; i < numP; ++i) {
			if ( stateVector[i] == 0 ) {
				// If state hasnt finished 
				// Check if state can be complete
				// If so update state vector
				// & avaVector & currentM 
				// & needM
				int localFlag = 1;
				// Check if state can complete
				for ( j = 0; j < numR; j++ ) {
					//printf("[%d] -> need[%d] - ava[%d] = [%d] \n", (i*numR)+j, needM[i*numR + j], avaVector[j], avaVector[j] - needM[i*numR + j]  < 0 );
					if ( avaVector[j] - needM[i*numR + j] < 0) {
						localFlag = 0;
						//printf("FALSE-> i: %d j: %d\n", i, j);
					}
					//else { printf("TRUE-> i: %d j: %d\n", i, j); }
				}
				if ( localFlag == 1 ) {
					printf("%d ", i);
					// Update State Vector
					stateVector[i] = 1;
					// Update avaVector & needM & usedM
					for ( j = 0; j < numR; ++j) {
						// Free resources from needM and usedM
						avaVector[j] += ( needM[i*numR + j] + currentM[i*numR + j]);
						// Set needM to 0
						needM[i*numR + j] = 0;
						// Set usedM to 0
						currentM[i*numR + j] = 0;
					}
					// Set Global flag to true;
					flag = 1;
				}
			}
		}
	} while ( flag == 1);
	printf("\n");


	int completed = 1;
	for(i = 0; i < numP; ++i) {
		if ( stateVector[i] != 1) {
			completed = 0;
		}
	}

	if ( completed == 1 ) {
		printf("The system is in a safe state\n");
	}
	else { printf("The system is in an unsafe state\n"); }




	/*
	
	// Test Prints
	printf("NumP: %d\n", numP);
	printf("NumR: %d\n", numR);

	printf("Max Vector\n");
	for( i = 0; i < numR; ++i)
	{
		printf("V[%d]->[%d]\n",i, maxVector[i]);
	}
	printf("Current M\n");
	for(i=0; i < numP; i++) {
  		for(j=0; j < numR; j++) {
	    	printf(" %d", currentM[i*numR +j]);
  		}
	}
	printf("\n");
	printf("Max M\n");
	for(i=0; i < numP; i++) {
  		for(j=0; j < numR; j++) {
	    	printf(" %d", maxM[i*numR +j]);
  		}
	}
	printf("\n");
	printf("Need M\n");
	for(i=0; i < numP; i++) {
  		for(j=0; j < numR; j++) {
	    	printf(" %d", needM[i*numR +j]);
  		}
	}
	printf("\n");

	*/

	// Free
	free(maxVector);   
	free(avaVector);
	free(stateVector); 
	free(currentM);
	free(maxM);
	free(needM);

	return 0;     
}