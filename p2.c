#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
 
void calcWaitingTime(int Sburst_time[], int Tburst_time[], time_t Tarv_time[], time_t Sarv_time[], int Snoq, int Tnoq)
{
	const int quantum=3;
	int time=0, total_time=0;
	int Srem_bt[100], Trem_bt[100], Srdq[100], Trdq[100], Swait[100], Twait[100], Ttat[100], Stat[100];
	int t=Tnoq,s=Snoq;
	for(int k=0;k<Tnoq;k++)
	{
		total_time+= Tburst_time[k];
		Trdq[k]=Tburst_time[k];
	}
	for(int k=0;k<Snoq;k++)
	{
		total_time+= Sburst_time[k];
		Srdq[k]=Sburst_time[k];
	}
	while (1)
    		{
		        bool done = true;
			for (int i = 0 ; i < t; i++)
			{
			        if (Trdq[i] > 0)
            			{
			                done = false; 
			                if (Trdq[i] > quantum)
			                {
				                time += quantum;
						Trdq[i] -= quantum;
			                }
					else
			                {
				                time = time + Trdq[i];
				                Twait[i] = time - Tburst_time[i];
				                Trdq[i] = 0;
                			}
            			}
        		}
			time++;
			if (done == true)
		        break;
		}
	while (1)
    		{
		        bool done = true;
			for (int i = 0 ; i < s; i++)
			{
			        if (Srdq[i] > 0)
            			{
			                done = false; 
			                if (Srdq[i] > quantum)
			                {
				                time += quantum;
						Srdq[i] -= quantum;
			                }
					else
			                {
				                time = time + Srdq[i];
				                Swait[i] = time - Sburst_time[i];
				                Srdq[i] = 0;
                			}
            			}
        		}
			if (done == true)
		        break;
		}
	for (int k=0;k<Tnoq;k++)
        	Ttat[k] = Tburst_time[k] + Twait[k];
	for (int k=0;k<Snoq;k++)
	        Stat[k] = Sburst_time[k] + Swait[k];
	printf("Processes	Arrival Time	Burst time	Waiting time	Turnaround time\n");
	for (int k=0;k<Tnoq;k++)
		printf("T%d\t\t%ld\t\t%d\t\t%d\t\t%d\n",k,Tarv_time[k],Tburst_time[k],Twait[k],Ttat[k]);
	for (int k=0;k<Snoq;k++)
		printf("S%d\t\t%ld\t\t%d\t\t%d\t\t%d\n",k,Sarv_time[k],Sburst_time[k],Swait[k],Stat[k]);
	printf("Total time spent- %d\n",total_time);
}

int main()
{
	const int MAX_LIM=500;
	time_t Tarv_time[100],Sarv_time[100],first;
	int choice,Snoq=0, Tnoq=0;
	char Sques[100][MAX_LIM], Tques[100][MAX_LIM];
	int Sburst_time[100], Tburst_time[100];
	time(&first);
	system("clear");
	while(choice!=3)
	{
		printf("1.\tEnter questions as Teacher\n2.\tEnter questions as Student\n3.\tEnd query session\n\tYour choice-");
		scanf("%d",&choice);
		while(getchar()!='\n');
		if(choice==1)
		{
			system("clear");
			printf("Enter Question Number.%d-",Tnoq);
			time(&Tarv_time[Tnoq]);
			fgets(Tques[Tnoq],MAX_LIM,stdin);
			Tburst_time[Tnoq]=(strlen(Tques[Tnoq])/10);
			Tnoq++;
		}
		if(choice==2)
		{
			system("clear");
			printf("Enter Question Number.%d-",Snoq);
			time(&Sarv_time[Snoq]);
			fgets(Sques[Snoq],MAX_LIM,stdin);
			Sburst_time[Snoq]=(strlen(Sques[Snoq])/10);
			Snoq++;
		}
	}
	for(int k=Tnoq-1;k>=0;k--)						
	{
		Tarv_time[k]=Tarv_time[k]-first;
	}
	for(int k=Snoq-1;k>=0;k--)						
	{
		Sarv_time[k]=Sarv_time[k]-first;
	}	
	printf("\n\n\t\tEvaluating all questions\n");
	calcWaitingTime( Sburst_time, Tburst_time, Tarv_time, Sarv_time, Snoq, Tnoq);
	printf("\n");
	return 0;
}
