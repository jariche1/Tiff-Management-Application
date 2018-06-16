#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "tiff_op.h"

int main(){
	char choice = '\0';
	char* filename[100];
	int num_pages;
	
	system("clear");
	
	while(choice != 'q' && choice != 'Q'){
		printf("\n\n\n\t------------------------------------------\n");
		printf("\t|                                        |\n");
		printf("\t|   Tiff Management Application (TiMA)   |\n");
		printf("\t|         Author: Jeremy Ariche          |\n");
		printf("\t|         Version: 1.0.0                 |\n");
		printf("\t|                                        |\n");
		printf("\t------------------------------------------\n");
		printf("\t*                                        *\n");
		printf("\t*                                        *\n");
		printf("\t*      1. Remove Blanks from Tiff        *\n");
		printf("\t*      2. Remove Pages from Tiff         *\n");
		printf("\t*      3. Merge Multiple Tiffs           *\n");
		printf("\t*      4. List Tiff Files                *\n");
		printf("\t*      5. Help                           *\n");
		printf("\t*                                        *\n");
		printf("\t*                                        *\n");
		printf("\t******************************************\n\n");
		
		printf("Please enter a number specifying which action to perform then press enter...\n");
		printf("(Press 'q' or 'Q' to exit)...\n");
		
		choice = getchar();
		
		switch(choice){
			case '1':
				  printf(" Enter a tiff file...\n");
				  scanf("%s",&filename);
				  remBlanks(filename);
				  break;
			case '2':
				  printf(" Enter a tiff file...  \n");
				  scanf("%s",&filename);
				  printf(" Specify the number of pages to delete...\n");
				  scanf("%d",&num_pages);
				  remPages(filename,num_pages);
				  break;
			case '3':	
				  printf(" Enter the number of tiff files to merge...\n");
				  scanf("%d",&num_pages);
				  merge(num_pages);
				  break;
			case '4':	
				 lsTiff();
				  break;
			case '5':	
				  printf(" Help \n");
				  system("cat HELP.md");
				  break;
			default: 
				  printf("INVALID SELECTION...Please try again\n");
				  break;
		}
		
		while ((getchar()) != '\n');
	}
	printf("Exiting Program...\n");
	system("clear");
	return 0;
}