#include <stdio.h>
#include <stdlib.h>
#include "ad.h"



Calendar_t* createAd(int size)
{
    Calendar_t* calendar;
    calendar=(Calendar_t*)malloc(sizeof(Calendar_t));
    if(calendar==NULL)
    {
        return NULL;
    }
    (calendar->array)=(Meeting_t**)malloc((sizeof(Meeting_t*))*size);
    if(calendar->array==NULL)
    {
        free(calendar);
        return NULL;
    }
    calendar->capacity=size;
    calendar->index=0;
    
    return calendar;
}


Meeting_t* createMeeting()
{
    float a=25,b=25;
    int room;
    Meeting_t* meeting;
    meeting=(Meeting_t*)malloc(sizeof(Meeting_t));
    if(meeting==NULL)
    {
	return;
    }
    scanf("%f",&a);
	while(a<0 || a>=24)
	{
		printf("Enter legal time\n");	
		scanf("%f",&a);
	}
    scanf("%f",&b);
	while(b<0 || b>=24)
	{
		printf("Enter legal time\n");	
		scanf("%f",&b);
	}
    scanf("%d",&room);
	while(room <1)
	{
		printf("Enter legal room number\n");	
		scanf("%d",&room);
	}
	if(a>=b)
	{
		printf("Meeting can't end before it started\n");
		return;
	}
	meeting->start_time=a;
	meeting->end_time=b;
	meeting->room_number=room;

    return meeting;
}


void destroyAd(Calendar_t* calendar)
{
    int i=0;
    for(i=0 ; i<(calendar->index) ; i++)
    {
        free(calendar->array[i]);
    }
    if(calendar!=NULL)
    {
        free(calendar->array);
        free(calendar);
    }
    
    return;
    
}


void printAd(Calendar_t* calendar)
{
    int i=0;
    if(calendar!=NULL)
    {
        for(i=0 ; i<(calendar->index) ; i++)
        {
            printf("start:%f end:%f in room:%d\n", calendar->array[i]->start_time, calendar->array[i]->end_time, calendar->array[i]->room_number);
        }
    }
    
    return;
}













int insertAppointment(Calendar_t* calendar, Meeting_t* meeting)
{
	Meeting_t* temp;
	int i=0, j=0, insert=0;
	if(calendar==NULL || meeting==NULL)
	{
		return 0;
	}
	if(calendar->array==NULL)
	{
		return 0;
	}
	if(calendar->index==0)
	{
		calendar->array[0]=meeting;
		calendar->index++;
		return 1;
	}
	if(meeting->end_time<=calendar->array[0]->start_time)
	{
		insert=0;
	}
	else if(meeting->start_time>=calendar->array[calendar->index-1]->end_time)
	{
		insert=calendar->index;
	}
	else
	{
		for(i=0 ; i<calendar->index ; i++)
		{
			if((meeting->start_time)>(calendar->array[i]->end_time))
			{
				if(i+1==calendar->index)
				{
					insert=i+1;
					break;	
				}
				else if((calendar->array[i+1]->start_time)>meeting->start_time)
				{
					if((calendar->array[i+1]->start_time)>(meeting->end_time))
					{
						insert=i+1;
						break;
					}
					else if((calendar->array[i+1]->start_time)<(meeting->end_time))
					{
						return 0;
					}	
				}					
			}
		}
		if(i==calendar->index)
		{
			return 0;
		}
	}

	if ((calendar->index)==(calendar->capacity))
	{
		temp=*calendar->array;
		calendar->array=realloc(calendar->array,(calendar->capacity)*2*sizeof(meeting));
		if (calendar->array)
		{
			calendar->capacity*=2;
		}
		else{
			calendar->array=&temp;
			return 0;
		}	
	}

	for(i=calendar->index ; i>insert ; i--)
	{
		calendar->array[i]=calendar->array[i-1];
	}
	calendar->array[i]=meeting;
	calendar->index++;					
	return 1;
}




















int removeAppointment(Calendar_t* calendar, float begin_hour)
{
    int i=0, j=0;
    if(calendar!=NULL)
    {
	if((calendar->array)==NULL)
	{
		return 0;
	}
        for(i=0 ; i<(calendar->index) ; i++)
        {
            if((calendar->array[i]->start_time)==begin_hour)
	    {
	    	free(calendar->array[i]);
		for(j=i ; j<calendar->index-1 ; j++)
		{
			calendar->array[j]=calendar->array[j+1];
		}
		(calendar->index)--;
		return 1;
	    }
        }
    }
    
    return 0;
}


int findAppointment(Calendar_t* calendar, float begin_hour)
{
    int i=0;
    if(calendar!=NULL)
    {
        for(i=0 ; i<(calendar->index) ; i++)
        {
            if((calendar->array[i]->start_time)==begin_hour)
	    {
		return i;
	    }
        }
    }
    
    return -1;
}
