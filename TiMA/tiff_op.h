#ifndef TIFF_OP_H
#define TIFF_OP_H

#include <stdio.h>

void splitMultipageTiff(char*,int);
void deleteDirectory(int*,int);
void mergeDirectories(char*,int,char*);
void delTextFile(char*);
void remBlanks(char*);
bool isBlank(uint32*,uint32);
void remPages(char*,int);
void merge(int);
void lsTiff();
float calculateSD(float[],int);


#endif
