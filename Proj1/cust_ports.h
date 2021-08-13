/* -----------------------------------------------------------------------------------
FILE NAME:         cust_ports.h
DESCRIPTION:       Header file for a basic accounting program for creating and managing accounts.
USAGE:             ./cs202_template
COMPILER:          GNU g++ compiler on Linux
NOTES:             Details on what this program does
MODIFICATION HISTORY:  Author                Date               Version
					   ------------------    ----------         --------------
					   Christopher Zinser    2020-10-02         1.0  Original version
											 2020-10-03			1.1 
											 2020-10-04			1.1
											 2020-10-05			1.1  
											 2020-10-06			1.1  
											 2020-10-07			1.1  
											 2020-10-08			1.1  
											 2020-10-09			1.1  
---------------------------------------------------------------------------------------- */
#ifndef __CUST_PORTS_H__
#define __CUST_PORTS_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

struct account_info{

char accid[7];
double acc_bal;
double growth_rate;
int comp_per_year;

};

struct Customer{
char custID[6];
char lname[20];
char fname[20];
char mname[20];
char tid[20];
char phonenum[20];
account_info acc[5];
};

//Function prototypes

void read_file(char * file, Customer * cust, int* num_recs);
void read_recs(istream &in, Customer * cust, bool mode,int* num_recs);
void write_file(char *file, Customer *cust, int num_recs);
void report(Customer *cust,int id,int years, char * name,bool mode);
void cust_info(Customer *cust,int id);
void create_cust(Customer *cust,int* num_recs);
void create_acc(Customer *cust,int num_recs);
void trim(char* string);
void function_switch(Customer *cust,char* outputted, int* num_recs );
void command_line_interp(Customer *cust,char* argv[], char* outputted, int* num_recs);
void dash_remover(char *input);
void upper_case(char* input);
void help_menu();
void str_input(char* input,char * phrase,int orig);
int menu();
int searchid(Customer *cust,int num_recs);
char yes_no();
#endif      //  __CUST_PORTS_H__