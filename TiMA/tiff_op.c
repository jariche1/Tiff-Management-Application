#include <stdio.h>
#include <tiffio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tiff_op.h"

void remBlanks(char* tif_file){
	
	TIFF *tif;                //Declare pointer to tif
	FILE *fptr; 
	uint32 width;             //tif width
	uint32 height;            //tif width
	uint32 npixels;           //tif number of pixels
	uint32* raster;           //tif buffer
	bool blank;               //check blankness
	bool blanks_detected = 0;
	int blank_count = 0;      //count number of blank documents
	int dir_count = 0;        //directory count
	int remainder_count = 0;  //non blank directory count
	
	
	tif=TIFFOpen(tif_file, "r");
	if(!tif){
		printf("Error Opening Tiff file! Program terminating...\n");
		exit(EXIT_SUCCESS);
	}
	
	//write blank page nmbrs to txt file
		fptr = fopen("blank.txt", "w");
		FILE *fptr1 = fopen("remain.txt", "w"); 
		
		do{
			
			//Check if blank directory exists
			TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);                     // uint32 width;
			TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);                   // uint32 height;
			npixels = width*height;
			raster = (uint32 *) _TIFFmalloc(npixels * sizeof(uint32));
			TIFFReadRGBAImage(tif, width, height, raster, 0); 
			blank = isBlank(raster,npixels);
			
			if(blank){
				printf(" Directory %d is blank!\n",dir_count + 1);
				blanks_detected = 1;
				blank_count++;
				fprintf(fptr,"%d ", dir_count + 1);
			}else{
				fprintf(fptr1,"%d ", dir_count + 1);
				printf(" No blank page found...\n");
			}
			_TIFFfree(raster);
			dir_count++;
			
		}while(TIFFReadDirectory(tif));
		TIFFClose(tif);
		fclose(fptr);
	    fclose(fptr1);
		remainder_count = dir_count - blank_count;
	
	
	if(blanks_detected){
		//Split multipage tif
		splitMultipageTiff(tif_file,dir_count);
		
		//Delete all blank split_xxx tifs	
		fptr = fopen("blank.txt","r");
		int blankarr[blank_count]; 

		// delete blank tiffs
		for (int i = 0; i < blank_count; i++){
		  fscanf(fptr, "%d", &blankarr[i]);
		}
		fclose(fptr);
		deleteDirectory(blankarr,blank_count);

		//Merge remaining directories back together
		mergeDirectories("remain.txt",remainder_count,tif_file);

		//Delete remaining tifs
		fptr1 = fopen("remain.txt","r");
		int remainArr[remainder_count];
		// Read in page numbers that are blank
		for (int i = 0; i < remainder_count; i++){
		  fscanf(fptr1, "%d", &remainArr[i]);
		}
		fclose(fptr1);
		deleteDirectory(remainArr,remainder_count);
	}else{
		printf("No blank pages were found!");
	}
	
	//Delete text file(s)
    delTextFile("remain.txt");
	delTextFile("blank.txt");

	return;
}

void remPages(char* tif_file,int numpages){
	
	TIFF *tif;                //Declare pointer to tif
	FILE *fptr1;              //File pointer
	int dir_count = 0;        //directory count
	int remainder_count;      //non blank directory count
	bool dowrite = 1;         //flag to write remaining tif files
	
	//Read in pages for deletion
	printf("Please enter which pages to delete...\n");
	int pages[numpages];
	for(int i = 0;i < numpages;i++){
		 scanf("%d",&pages[i]);
	}
	
	//write remaining pages to text file
	tif=TIFFOpen(tif_file, "r");
	fptr1 = fopen("remain.txt", "w");   
	do{
		for(int i = 0;i < numpages;i++){
			if(pages[i] == (dir_count+1)){
				dowrite = 0;
				break;
			}
		}

		if(dowrite){
			printf("Writing page: %d...\n",(dir_count+1));
			fprintf(fptr1,"%d ", (dir_count+1));
		}
		dir_count++;
		dowrite = 1;
		
	}while(TIFFReadDirectory(tif));
	remainder_count = dir_count - (numpages);
	TIFFClose(tif);
	fclose(fptr1);
	
	for(int i = 0;i < numpages;i++){
		 if(pages[i] > dir_count){
		 	printf("Invalid page numbers entered. Program terminating...\n");
			delTextFile("remain.txt");
			exit(EXIT_SUCCESS);
		 }
	}
	
	//Split multipage tif
	splitMultipageTiff(tif_file,dir_count);
	
	//Delete all specified pages
	deleteDirectory(pages,numpages);

	//Merge remaining directories back together
	mergeDirectories("remain.txt",remainder_count,tif_file);
	
	//Delete remaining tifs
	fptr1 = fopen("remain.txt","r");
	int remainArr[remainder_count];
	// Read in page numbers that are blank
    for (int i = 0; i < remainder_count; i++){
	  fscanf(fptr1, "%d", &remainArr[i]);
    }
	fclose(fptr1);
	deleteDirectory(remainArr,remainder_count);

	//Delete text file(s)
	delTextFile("remain.txt");
	
	return;

}

void merge(int num_files){
	if(num_files < 2){
		printf("Not enough arguments...\n");
		return;
	}
	
	char* tiffcp = "tiffcp -c lzw ";
	char* newtif[50];
	int space = 0;
	int size = 100;
	char n[size];
	char tfiles[num_files][size];
	
	//get files to be merged
	printf("Please enter the correct names of the tif files (Press enter after typing each name)..\n");
	for(int i = 0;i < num_files;i++){
		scanf("%s",n);
		strcpy(tfiles[i], n);
	}
	
	printf("Please enter a new name for the merged file (Don't forget the .tif extension!)..\n");
	scanf("%s",&newtif);
	
	//get cumulative string length of each input
	for(int i = 0; i < num_files; i++){
		space = space + strlen(tfiles[i]);
	}
	char* Nsource_tif = malloc(space + (num_files) + 1);
	strcpy(Nsource_tif, tfiles[0]);
	strcat(Nsource_tif, " ");
	
	//Concatenate all files
	for(int i = 0; i < num_files; i++){
		strcat(Nsource_tif, tfiles[i+1]);
		strcat(Nsource_tif, " ");
	}
	
	char* merge_com = malloc(strlen(tiffcp) + strlen(Nsource_tif) + strlen(newtif)+ 1);
	strcpy(merge_com, tiffcp);
	strcat(merge_com, Nsource_tif);
	strcat(merge_com, newtif);
	system(merge_com);
	
	printf("New file Create!\n");
	return;
}

void lsTiff(){
	
	system("ls | grep -e '.tif'");
	return;
}

void splitMultipageTiff(char* filename, int dc){
	
		TIFF *tif=TIFFOpen(filename, "r");
		if(dc > 1){
			printf("\nSplitting file...\n\n");
			char* split_tiff_com = "tiffsplit ";
			char* split = " split_";
			char *split_mp_com = malloc(strlen(split_tiff_com)+strlen(filename)+ strlen(split)+1);
			strcpy(split_mp_com, split_tiff_com);
			strcat(split_mp_com, filename);
			strcat(split_mp_com, split);
			system(split_mp_com);
			TIFFClose(tif);
		}else{
			printf("\nThis is not a multipage tiff! Program terminating...\n");
			exit(EXIT_SUCCESS);
		}
	
	return;
}

void deleteDirectory(int* pg, int arrlen){
		bool break1;
	//Determine each numbers lexical map 
	for (int i = 0; i < arrlen; i++){
		int count = 1;
		break1 = 0;
        for(char x1 = 'a'; x1 <= 'z';x1++){
			for(char x2 = 'a'; x2 <= 'z';x2++){
				for(char x3 = 'a'; x3 <= 'z';x3++){
					if(count == pg[i]){
						//Identify blank tif documents
						char* split_ = "rm split_";
						char* tif = ".tif";
						char* xyz = malloc(4); // Dump contents into "x1"
						char* rm_split_xxx = malloc(17); 
						strcpy(xyz, &x1);
						strcat(xyz, &x2);
						strcat(xyz, &x3);
						xyz[3] = '\0';
						strcpy(rm_split_xxx, split_);
						strcat(rm_split_xxx, xyz);
						strcat(rm_split_xxx, tif);
						//Delete blank document
						printf("Deleting file %d...\n",pg[i]);
						system(rm_split_xxx);
						break1 = 1;
						break;
					}
					count++;
				}
				if(break1){
					break;
				}
			}
			if(break1){
				break;
			}
		}	
    }
	
	return;
}

void mergeDirectories(char* filetxt,int arrlen,char* dst){
	FILE* fptr1;
	fptr1 = fopen(filetxt,"r");
	int remainArr[arrlen];
	// Read in page numbers that are blank
    for (int i = 0; i < arrlen; i++){
	  fscanf(fptr1, "%d", &remainArr[i]);
    }
	fclose(fptr1);
	
	char src[arrlen*14];
	for (int i = 0; i < arrlen; i++){
		int count = 1;
		bool break1 = 0;
        for(char x1 = 'a'; x1 <= 'z';x1++){
			for(char x2 = 'a'; x2 <= 'z';x2++){
				for(char x3 = 'a'; x3 <= 'z';x3++){
					if(count == remainArr[i]){
						//Identify remaining tif documents
						char* split = "split_";
						char* tif = ".tif ";
						char* split_xxx_tif = malloc(strlen(split)+strlen(tif)+5); // Dump contents into "x1"
						char* xxx = malloc(4); // Dump contents into "x1"
						strcpy(xxx, &x1);
						strcat(xxx, &x2);
						strcat(xxx, &x3);
						xxx[3] = '\0';
						strcpy(split_xxx_tif, split);
						strcat(split_xxx_tif, xxx);
						strcat(split_xxx_tif, tif);
						if(i == 0){
							strcpy(src, split_xxx_tif);
						}else{
						    strcat(src, split_xxx_tif);	
						}
						break1 = 1;
						break;
					}
					count++;
				}
				if(break1){
					break;
				}
			}
			if(break1){
				break;
			}
		}	
    }
	
	char* merge = "tiffcp -c lzw ";
	char* tiffcp_split_xxx_dst = malloc(strlen(merge)+strlen(src)+strlen(dst) +1);
	strcpy(tiffcp_split_xxx_dst, merge);
	strcat(tiffcp_split_xxx_dst, src);
	strcat(tiffcp_split_xxx_dst, dst);
	printf("\n\nMerging remaining files...\n");
	system(tiffcp_split_xxx_dst);
	
	return;

}

void delTextFile(char* txtfile){
	if (remove(txtfile) == 0){
		printf("\n%s",txtfile);	
       printf(" deleted successfully\n");
	}
	
	return;
}

bool isBlank(uint32* r,uint32 len){
	char R,G,B;
	int Ri,Gi,Bi;
	double threshold = 6.00;
	double std;
	float luminance[len];
	
	for(int i = 0; i < len;i++){
		R =(int )TIFFGetR(r[i]);
		Ri = ((int)R + 256)%256;
		//printf("i = %d: (%d,",i,Ri);
		
		G =(int )TIFFGetG(r[i]);
		Gi = ((int)G + 256)%256;
		//printf("%d,",Gi);
	
	    B =(int )TIFFGetB(r[i]);
		Bi = ((int)B + 256)%256;
		//printf("%d) ==> ",Bi);
		
		//Compute Luminance
		luminance[i] = 0.2126*Ri + 0.7152*Gi + 0.0722*Bi;
		//printf("Luminance: %lf\n",luminance[i]);
	}
	
	std = calculateSD(luminance,len);
	
	//printf("Standard Deviation: %lf\n",std);
	if(std <= threshold){
		return 1;
	}
	
	return 0;
}

float calculateSD(float data[], int arrlen){
    float sum = 0.0, mean, standardDeviation = 0.0;

    int i;
    for(i=0; i< arrlen; ++i){
        sum += data[i];
    }

    mean = sum/arrlen;

    for(i=0; i<arrlen; ++i)
        standardDeviation += pow(data[i] - mean,2);

    return sqrt(standardDeviation/arrlen);
}