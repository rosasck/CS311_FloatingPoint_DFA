/**
 * @file crosas.c
 * @author Cintiha K. Rosas Gordillo
 * @version 0.1
 * @date 2020-10-24
 * Class: CS311
 * Section: T/TH 
 * Description:  
 * 
 */

#include <stdio.h>
#include <string.h>

int main(){

	//Holds the name of the file that the input is being taken
    char fileName[100];

	//Holds the current state within the DFA for the given string 
    char currentS;

	//Holds where we are in the transition table
    int TransRow, TransColumn;

	//To read in from the file
    FILE * fp;

	//hols the input we will analyze as part of our alphabet
    char input[100];


	// Variables to make transition table
	int TransTableY;
	int TransTableX;
	int numAcceptStates;
	
	
	//opening the file to read in DFA
   	printf("\nPlease enter the name of the file: ");
	scanf("%s",fileName);
    fp= fopen(fileName, "r");

	
    //reading in vars to make DFA TABLE
	fscanf(fp, "%d\n", &TransTableY);
	fscanf(fp, "%d\n", &TransTableX);

	//printing to know column and row counts		
	printf("Columns: %d \n",TransTableY);
	printf("Rows: %d",TransTableX);

	//making DFA to fill  up
    char DFA[TransTableX][TransTableY];

	//reading in number of accept states
	fscanf(fp, "%d\n", &numAcceptStates);
	char acceptStates[numAcceptStates];

	//reading in accept states
	int k;
	for(k=0; k < numAcceptStates-1; ++k)
	{
		fscanf(fp, "%c", &acceptStates[k]);
	}
	fscanf(fp, "%c\n", &acceptStates[k]);

	//reading in DFA
	for(int i=0; i < TransTableX; i++ ){
		
		for(int j=0; j < TransTableY; j++){
			fscanf(fp, "%c", &DFA[i][j]);
		}	
	}


	//printing num of accept states	
	printf("\nNumber of Accept States: %d \n", numAcceptStates);

	//printing out accept states
	printf("Accept States: ");
	for(int k=0; k < numAcceptStates; k++)
	{
		printf("%c, ", acceptStates[k]);
	}

	//closing file 
     fclose(fp);

	/**printing trans table
    for(int i=0; i < TransTableX; i++ ){
		printf("\n");
			for(int j=0; j < TransTableY; j++){
				printf("%c",DFA[i][j]);
			}
		}
	**/
	//reading in user string to accept or reject 
	printf("\nPlease enter a string to evaluate: ");
	scanf( "%s", input);	
            
	int len = strlen(input); 

	currentS = 'A';  //Start state is A


	for(int i = 0; i < len; i++){ //Loops through each letter of the input 
				
		TransRow = -1;

		TransColumn = -1;

		for(int j = 1; j < 11; j++){ //Find the correct row based on the state
			if(currentS == DFA[j][0]){
				TransRow = j;
			}
		}
				
		for(int j = 0; j < 16; j++){ //Finds the column based on ur input character
			if(input[i] == DFA[0][j]){
				TransColumn = j;
			}

		}


		//If we did not find the letter in the table, we default to dead state
		if(TransColumn == -1)
			currentS = 'I'; 
				

		//set the new state and go to the next letter
		else
			currentS = DFA[TransRow][TransColumn]; 
	}

	//Print if the string was in the alphabet or not
	int found= 0;
	printf("Current State %c", currentS);
	for(int i =0; i < numAcceptStates; i++){
		if(currentS == acceptStates[i]){
			printf("\n");
			printf( "\n Input %s : VALID \n", input);
			printf("\n");
			found = 1;

		}
	}
	if(found == 0){
		printf("\n");
		printf("\nInput %s : INVALID \n", input);
		printf("\n");
	}	
	return 0;
}
