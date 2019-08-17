#include <stdio.h>
#include <stdlib.h>
#include "bits.h"



/* function to print int type in its binary implementation */
static void intToBinary(int n)
{
  int c=0, k=0;
   
  for (c=0; c<sizeof(int)*8 ; c++)
  {
    k=n>>c;
 
    if (k&1)
      printf("1");
    else
      printf("0");
  }
 
  return;
}



/* function to run one of the functions pointed by the functions array */
int runFunction(BitFunction function,bitmap_t* bitmap,int feature)
{
	return function(bitmap,feature); 
}



/* function to create a bitmap, depending on the number of features user enters in main */
bitmap_t* createBitmap(int numberOfFeatures)
{
	int i=0, blocksNumber=0;
	bitmap_t* bitmap;
	bitmap=(bitmap_t*)malloc(sizeof(bitmap_t));

	if(bitmap==NULL)
	{
		return NULL;
	}
	blocksNumber=( (numberOfFeatures%(sizeof(int)*8))==0 ? numberOfFeatures/(8*sizeof(int)) : numberOfFeatures/(8*sizeof(int))+1 );
	bitmap->m_array=(int*)calloc(blocksNumber,sizeof(int));
	if (bitmap->m_array==NULL)
	{	
			free(bitmap);
			return NULL;
	}
	bitmap->m_numberOfFeatures=numberOfFeatures;

	return bitmap;
}



/* function to destroy a bitmap */
void destroyBitmap(bitmap_t* bitmap)
{
	if(bitmap==NULL)
	{
		return;
	}
	free(bitmap->m_array);
	free(bitmap);

	return;
}



/* function to print the status of all excisting features in a row */
void printAllFeatures(bitmap_t* bitmap)
{
	int i=0, blocksNumber=0;
	blocksNumber=( (bitmap->m_numberOfFeatures%(sizeof(int)*8))==0 ? bitmap->m_numberOfFeatures/(8*sizeof(int)) : bitmap->m_numberOfFeatures/(8*sizeof(int))+1 );
	for(i=0 ; i<blocksNumber ; i++)
	{
		intToBinary(bitmap->m_array[i]);
	}
	printf("\n");
}



/* function to turn on a specific bit */
int bitOn(bitmap_t* bitmap, int feature)
{
	int block=0, index=0;

	if(feature<=0 || feature>bitmap->m_numberOfFeatures)
	{
		return -1;
	}
	block=(feature-1)/(sizeof(int)*8);
	index=(feature-1)%(sizeof(int)*8);
	bitmap->m_array[block]=(bitmap->m_array[block])|(1<<(index));

	return 1;
	/*shift, or*/
}



/* function to turn off a specific bit */
int bitOff(bitmap_t* bitmap, int feature)
{
	int block=0, index=0;

	if(feature<=0 || feature>bitmap->m_numberOfFeatures)
	{
		return -1;
	}
	block=(feature-1)/(sizeof(int)*8);
	index=(feature-1)%(sizeof(int)*8);
	bitmap->m_array[block]=(bitmap->m_array[block])&(~(1<<(index)));

	return 1;
	/*shift, not, and*/
}



/* function to get the status of a specific bit */
int bitStatus(bitmap_t* bitmap, int feature)
{
	int block=0, index=0;

	if(feature<=0 || feature>bitmap->m_numberOfFeatures)
	{
		return -1;
	}
	block=(feature-1)/(sizeof(int)*8);
	index=(feature-1)%(sizeof(int)*8);
	if(((bitmap->m_array[block])&(1<<(index)))==0)
	{
		printf("Bit status is 0\n");	/*JUST TO CHECK*/
		return 0;
	}
	else
	{
		printf("Bit status is 1\n");	/*JUST TO CHECK*/
		return 1;
	}
	/*shift, and*/
}