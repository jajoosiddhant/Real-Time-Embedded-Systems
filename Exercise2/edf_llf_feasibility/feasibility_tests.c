/*
 * 
 * Filename: EDF and llf feasibility/scheduability test
 * Author: Siddhant Jajoo
 * Description: This code finds out if the given task set is feasible under Earliest Deadline First protocol
 * and Least laxity First protocol.
 * Date: 02/21/2019.
 * References: GeeksforGeeks, Real time Embedded Systems-Sam Siewert and John Pratt. 
 */

#include <math.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define U32_T unsigned int

// U=0.7333
U32_T ex0_period[] = {2, 10, 15};
U32_T ex0_wcet[] = {1, 7, 2};

// U=0.9857
U32_T ex1_period[] = {2, 5, 7};
U32_T ex1_wcet[] = {1, 1, 2};

// U=0.9967
U32_T ex2_period[] = {2, 5, 7, 13};
U32_T ex2_wcet[] = {1, 1, 1, 2};

// U=0.93
U32_T ex3_period[] = {3, 5, 15};
U32_T ex3_wcet[] = {1, 2, 3};

// U=1.0
U32_T ex4_period[] = {2, 4, 16};
U32_T ex4_wcet[] = {1, 1, 4};

//U=1.0
U32_T ex5_period[] = {2, 5, 10};
U32_T ex5_wcet[] = {1, 2, 1};

//U=0.996
U32_T ex6_period[] = {2, 5, 7, 13};
U32_T ex6_wcet[] = {1, 1, 1, 2};
U32_T ex6_dam[] = {2,3,7,15};

//U=1.0
U32_T ex7_period[] = {3, 5, 15};
U32_T ex7_wcet[] = {1, 2, 4};

//U=0.996
U32_T ex8_period[] = {2, 5, 7, 13};
U32_T ex8_wcet[] = {1, 1, 1, 2};


int edf_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);
int llf_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);
U32_T minimum(U32_T dline[], U32_T numServices);
int gcd(int a , int b);
long int lcm(U32_T period[], U32_T numServices);

int main(void)
{ 
    int i;
	U32_T numServices;
    
    printf("******** EDF Test Feasibility Example\n");
   
    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D): ",
		   ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
	numServices = sizeof(ex0_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D): ", 
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
	numServices = sizeof(ex1_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex2_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
	numServices = sizeof(ex3_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D): ",
		   ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
	numServices = sizeof(ex4_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");


    printf("Ex-5 U=%4.2f (C1=1, C2=2, C3=1; T1=2, T2=5, T3=10; T=D): ",
		   ((1.0/2.0) + (2.0/5.0) + (1.0/10.0)));
	numServices = sizeof(ex5_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-6 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; D1=2, D2=3, D3=7, D4=15): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex6_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex6_period, ex6_wcet, ex6_dam) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");


    printf("Ex-7 U=%4.2f (C1=1, C2=2, C3=4; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (4.0/15.0)));
	numServices = sizeof(ex7_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-8 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex8_period)/sizeof(U32_T);
    if(edf_feasibility(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");


	printf("\n\n");
  
  
    printf("******** LLF Point Feasibility Example\n");

    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D): ",
		   ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
	numServices = sizeof(ex0_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D): ", 
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
	numServices = sizeof(ex1_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex2_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
	numServices = sizeof(ex3_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D): ",
		   ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
	numServices = sizeof(ex4_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");


    printf("Ex-5 U=%4.2f (C1=1, C2=2, C3=1; T1=2, T2=5, T3=10; T=D): ",
		   ((1.0/2.0) + (2.0/5.0) + (1.0/10.0)));
	numServices = sizeof(ex5_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-6 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; D1=2, D2=3, D3=7, D4=15): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex6_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex6_period, ex6_wcet, ex6_dam) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");


    printf("Ex-7 U=%4.2f (C1=1, C2=2, C3=4; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (4.0/15.0)));
	numServices = sizeof(ex7_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-8 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex8_period)/sizeof(U32_T);
    if(llf_feasibility(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");


}



/*
 * This function checks if the given set of tasks are feasible or not using edf protocol.
 */ 
int edf_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
	{
		U32_T rc = TRUE, min, c, i, j, k, status, flag, lcmvalue;
		U32_T dline[numServices];
		U32_T p[numServices];
		U32_T current_exec[numServices];
		
		lcmvalue = lcm(period,numServices);
		
		//Copying the parameters into temporary variables.
		for (c=0;c<numServices;c++)
			{
				dline[c] = deadline[c];
			}
			
		for (c=0;c<numServices;c++)
			{
				p[c] = period[c];
			}
			
		for (c=0;c<numServices;c++)
			{
				current_exec[c] = wcet[c];
			}
				
	    for (i=1; i <= lcmvalue; i++)  //iterate at every time instant 
	    {
	      status=0;

			min =  minimum(dline, numServices);
			
			if (current_exec[min] != 0)
			{
				current_exec[min]--;
				//printf("Task %d completed at time %d\n", min, i);
			}
			
			for (j=0; j<numServices;j++)
			{
				
	
			if (i%period[j]==0)	 //copy time period if over
		    {
				p[j] = period[j];
				dline[j] = deadline[j]; 
				current_exec[j] = wcet[j];
			}
	
				p[j]--;			
				dline[j]--;
			
			if (dline[j] == 0 && current_exec[j]!=0)		//feasibility check
			{
				status = 1;
				rc = FALSE;
				break;
			}
			else if((current_exec[j] == 0))
			{
				dline[j] = lcmvalue*2;  //if Ci is zero making deadline high enough to not interfere in other processes.
			}
			
			}
		
				
		if (status) break;
		
		}
		return (rc);
	}   



/*
 * This function checks if the given set of tasks are feasible or not using llf protocol.
 */ 

int llf_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
	{
		U32_T rc = TRUE, min, c, i, j, k, status, lcmvalue;
		U32_T dline[numServices];
		U32_T p[numServices];
		U32_T current_exec[numServices];
		U32_T llf_exec[numServices];
		
	//Copying the parameters into temporary variables.	
		for (c=0;c<numServices;c++)
			{
				dline[c] = deadline[c];
			}
			
		for (c=0;c<numServices;c++)
			{
				p[c] = period[c];
			}
			
		for (c=0;c<numServices;c++)
			{
				current_exec[c] = wcet[c];
			}
		
		
		lcmvalue = lcm(period,numServices);
				
	    for (i=1; i <= lcmvalue; i++) 	//iterate at every time instant
	    {
	      status=0;
			
			for (c=0;c<numServices;c++)		//Calulate llf value at every time instant 
			{
				llf_exec[c] = dline[c] - current_exec[c];
			}
			min =  minimum(llf_exec, numServices);
			
			if (current_exec[min] != 0) 
			{
				current_exec[min]--;
			//	printf("Task %d completed at time %d\n", min, i);
			}
			
			for (j=0; j<numServices;j++)
			{
				
	
			if (i%period[j]==0)		//copy time period if over
		    {
				p[j] = period[j];
				dline[j] = deadline[j]; 
				current_exec[j] = wcet[j];
			}
	
				p[j]--;			
				dline[j]--;
			
			if (dline[j] == 0 && current_exec[j]!=0) //infeasibilty check
			{
				status = 1;
				rc = FALSE;
				break;
			}
			else if((current_exec[j] == 0))
			{
				dline[j] = lcmvalue*2; //if Ci is zero making deadline high enough to not interfere in other processes. 
			}
			
			}
		
				
		if (status) break;
		
		}
		return (rc);
	}   



/*
 *To find the minimum deadline at a point of time 
 */
U32_T minimum(U32_T dline[], U32_T numServices)
{
	U32_T min = dline[0] ;
	U32_T i, index=0;
	for(i=0;i<=numServices-1;i++)
	{
		if( (min >= dline[i]))
		{
			min = dline[i];
			index=i;
		}
	}
	return (index);
}
 
 
 /*
 * This function finds the greates common divisor.
 */ 
 int gcd(int a , int b)
{
if (b==0)
{
	return a;
}
return gcd(b, a%b);
}

/*
 * This function finds the least common multiple.
 */ 
long int lcm(U32_T period[], U32_T numServices)
{
	long int res = period[0];
	int i;
	for (i=1; i<numServices; i++)
	{
		res = (((period[i]*res))/(gcd(period[i], res)));
	}
	return res;
}
