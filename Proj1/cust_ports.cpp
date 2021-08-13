/* -----------------------------------------------------------------------------------
FILE NAME:         cust_ports.cpp
DESCRIPTION:       A basic accounting program for creating and managing accounts.
USAGE:             ./cust_ports
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
//Creates constant of author name
const char PROGRAMMER_NAME[] = "Christopher Zinser";     // Global constant
#include "cust_ports.h"
/*-----------------------------------------------------------------------------
 FUNCTION:          main()
 DESCRIPTION:       Say what this function does
 RETURNS:           0
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */

int main(int argc, char * argv[]){
  
  //C-string that will contain the file
	if(argc >= 3){

	}else{
	  cout<< "If a DB exists already.. do ./cust_ports -f dbname  "<<endl
		  << "Otherwise create one with ./cust_ports -f dbname" <<endl;
	  
	}
  char* outputted = argv[2];
  //Declaration and Inititalization of num_recs
  int num_recs = 0;
  //Declaring and initializing a pointer to num_rec
  int *num_rec_ptr = &num_recs;
  //Creates new customer [Dynamic memory]
  Customer * cust = new Customer[20];
  //Reads in the customer data into the structure
  read_file(argv[2], cust , num_rec_ptr);
  //Reads command line inputs
  if( argc >= 4){
    command_line_interp(cust,argv,outputted,num_rec_ptr);
  }else{
	if(argc >= 3){
		
		function_switch(cust, outputted, num_rec_ptr);
	}else{
		if(strcmp(argv[1], "-h") ==0){
			help_menu();
		}else{
			//cout<< "File not specified" << endl;
		}
	}
  }
 
  //cout<< "First ID: " << cust[1].custID << endl;
  if(argc >= 3){
	write_file(outputted,  cust,  num_recs);
  }
  
    //cout << endl;
    cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";cout << __DATE__ << "  " __TIME__ << endl;
    cout << endl;
    
  delete cust;
  return 0;
}

void read_file(char * file, Customer * cust, int* num_recs){
  //Drives the process of reading the file
  ifstream in(file);
  //cout<< "read func" << endl;
  read_recs(in, cust, 0,num_recs);
  in.close();


}

/*-----------------------------------------------------------------------------
 FUNCTION:          read_recs()
 DESCRIPTION:       Reads records from the specified file into the cust structure
 RETURNS:           N/A
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void read_recs(istream &in, Customer * cust, bool mode, int* num_recs){
	
  string str = "";
  int num = 0;
  //Begins reading in records
  
   //cout<< "Read rec"<< endl;
   
  while(num <20){
   
    if(in.eof()) break;
    
    //read_cust_info(in, cust, 0);
    char Data[100];
    in.getline(Data,100,'\n');
	//Checks validity
    if(Data[0]){
		//Valid data is read in
		strcpy(cust[num].custID, Data);
        //cout<<"CID:" <<cust[num].custID << endl;
    
		in.getline(Data,100,',');
		//cout <<"Last Name: " <<Data << endl; 
		strcpy(cust[num].lname,Data);
		trim(cust[num].lname);
		in.getline(Data,100,',');
		//cout <<"Middle Name: " <<Data << endl; 
		strcpy(cust[num].mname,Data);
		trim(cust[num].mname);
		in.getline(Data,100,'\n');
		//cout <<"First Name: " <<Data << endl; 
		strcpy(cust[num].fname,Data);
		trim(cust[num].fname);
		in.getline(Data,100,'\n');
		//cout <<"Tax ID: " <<Data << endl; 
		strcpy(cust[num].tid,Data);
		in.getline(Data,100,'\n');
		//cout <<"Phone Number: " <<Data << endl; 
		strcpy(cust[num].phonenum,Data);
    }
	//sets initial stream position
    streampos pos;
    pos = in.tellg();
	for(int i = 0;Data[0];i++){
	   //reads in account data
        
        in.getline(Data,100,'\n');
        if(Data[0]){
        in.seekg(pos);
        in>>Data;
        //cout<<"Account ID: "<< Data << endl;
        strcpy(cust[num].acc[i].accid,Data);
        in>>Data;
        //cout<<"Account Balance: "<< Data << endl;
        cust[num].acc[i].acc_bal = atof(Data);
        in>>Data;
        //cout<<"Account Growth Rate: "<< Data << endl;
        cust[num].acc[i].growth_rate =atof(Data);
        in.getline(Data,100,'\n');
      //  cout<<"Account Compound Rate: "<< Data << endl;
    //    cout<< endl;
        cust[num].acc[i].comp_per_year =atoi(Data);
        pos = in.tellg();
        }
	}
  //in.seekg(pos);
  //cout<< "num: " << num << endl;
  //cout<< endl;
  //cout<< endl;
  
  num++;
  *num_recs =num+1;

    //cout<< num++ <<":"<< Data <<endl;
    
  
  
  
  

	}

}


/*-----------------------------------------------------------------------------
 FUNCTION:          write_file()
 DESCRIPTION:       Writes the structure into the specified file
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void write_file(char *file, Customer *cust, int num_recs){
  //cout<< cust[0].custID <<endl;
  cout<< "Prepping to write "<<num_recs<< " records to " << file<< endl;
  ofstream output;
  output.open(file);
  int num= 0;
  //cout<< ARRAY_SIZE(cust) << endl;
  for(int cust_count=0; cust_count<num_recs; cust_count++ ){

    if(cust[cust_count].custID[0]){
    //  cout<< "Writting #" << cust_count<< " with id:" << cust[cust_count].custID << endl;
      output<< cust[cust_count].custID<<endl;
      output<< cust[cust_count].lname << ", "<<cust[cust_count].mname <<", " <<cust[cust_count].fname <<endl;
      output<< cust[cust_count].tid<< endl;
      output<< cust[cust_count].phonenum <<endl;
      for(int acc_count=0;acc_count<ARRAY_SIZE(cust->acc);acc_count++ ){
        if(cust[cust_count].acc[acc_count].comp_per_year<365 &&     cust[cust_count].acc[acc_count].comp_per_year>0){
          output<< cust[cust_count].acc[acc_count].accid << " ";
          output<< cust[cust_count].acc[acc_count].acc_bal <<" ";
          output<< cust[cust_count].acc[acc_count].growth_rate<<" ";
          output<< cust[cust_count].acc[acc_count].comp_per_year;
          output<<endl; 
        }
      }
    output<< endl;
   // cout<< cust_count << endl;
    }
  }
  output.close();

  //cout<< "write ended" << endl;

}
/*-----------------------------------------------------------------------------
 FUNCTION:          report()
 DESCRIPTION:       Generates/Writes/Displays a generated report based on the inputed customer id 
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void report(Customer *cust, int id,int years, char* name,bool mode){
	//local variable initialization and declaration
 int printamnt =1;
 double total = 0;
 double total_bal = 0;
  ofstream output;
  output.open(name);
  
  if(mode ==1){
	  printamnt = 20;
  }
  
  
	for(int i2 =0; i2< printamnt; i2++){
		if(mode == 1){
		 //cout<< "mode is 1" << endl;
		 
			 //cout<< "Setting is 1 id is: "<<i2 << endl;
			 id = i2;
			 
			 
		 
		 
		}
	 //Outputs report to screen
	if(cust[id].custID[0]){
		cout<<"CustID  Last_Name       First_Name      Middle      TAXID        Phone" <<endl
		<< "------  --------------  --------------  ----------  -----------  ---------------"<<endl
		<<left<<setw(6) << cust[id].custID<<"  "<<left<<setw(14)<<cust[id].lname<<"  "<<left  << setw(14)<< cust[id].fname <<"  "<<left<< setw(10)<<cust[id].mname<<"  "<< left << setw(11) << cust[id].tid<<left <<"  "<<setw(14) <<cust[id].phonenum<<endl
		<<"-------------------------------------------------------------------------------------------"<<endl
		<<"        Accounts        Balance%Rate              % Rate    C/Y  Projections ("<<years<<" yr)"<<endl
		<<"        --------        ----------------------    ------    ---  --------------------------"<<endl;
		cout<< setprecision(2)<<fixed;
 

	for (int i = 0; cust[id].acc[i].accid[0] && i < ARRAY_SIZE(cust[id].acc); i++){
	  
		cout<<"        "<<setw(6)<<cust[id].acc[i].accid<<"          "<<left << setw(22)<<cust[id].acc[i].acc_bal<<left<<"    "<<setw(6) <<cust[id].acc[i].growth_rate <<"    " <<left << setw(3) <<cust[id].acc[i].comp_per_year<<"  "<< left<< setw(26)<<cust[id].acc[i].acc_bal * pow((1 + ((cust[id].acc[i].growth_rate/100)/cust[id].acc[i].comp_per_year)),cust[id].acc[i].comp_per_year*years)<<endl;
    
		total += cust[id].acc[i].acc_bal * pow((1 + ((cust[id].acc[i].growth_rate/100)/cust[id].acc[i].comp_per_year)),cust[id].acc[i].comp_per_year*years);

		total_bal += cust[id].acc[i].acc_bal;
	}
	cout<<"        -------"<<endl<<"        Totals:         "<<left << setw(15) << total_bal <<"                          "<<left<<setw(15)<<total<<endl<<endl;

	//outputs report to file
	output<<"CustID  Last_Name       First_Name      Middle      TAXID        Phone" <<endl
	<< "------  --------------  --------------  ----------  -----------  ---------------"<<endl
	<<left<<setw(6) << cust[id].custID<<"  " <<setw(14)<<cust[id].lname<<"  "<<left<< setw(14)<< cust[id].fname <<"  "<<left<< setw(10)<<cust[id].mname<<"  "<< left << setw(11) << cust[id].tid<<left <<"  "<<setw(14) <<cust[id].phonenum<<endl
	<<"------------------------------------------------------------------------"<<endl
	<<"        Accounts        Balance%Rate              % Rate    C/Y     Projections ("<<years<<" yr)"<<endl
	<<"        --------        ----------------------    ------    ---  --------------------------"<<endl;
	output<< setprecision(2)<<fixed;
	for (int i = 0; cust[id].acc[i].accid[0]&&i < ARRAY_SIZE(cust[id].acc); i++){
		output<<"        "<<setw(6)<<cust[id].acc[i].accid<<"          "<<left << setw(22)<<cust[id].acc[i].acc_bal<<left<<"    "<<setw(6) <<cust[id].acc[i].growth_rate <<"    " <<left << setw(3) <<cust[id].acc[i].comp_per_year<<"  "<< left<< setw(26)<<cust[id].acc[i].acc_bal * pow((1 + ((cust[id].acc[i].growth_rate/100)/cust[id].acc[i].comp_per_year)),cust[id].acc[i].comp_per_year*years)<<endl;
    
	}
  

  


	output<<"        -------"<<endl<<"        Totals:         "<<left << setw(15) << total_bal <<"                          "<<left<<setw(15)<<total<<endl<<endl;
	total = 0;
	total_bal = 0;
	}
 }
 output.close();
}
/*-----------------------------------------------------------------------------
 FUNCTION:          cust_info()
 DESCRIPTION:       Displays Customer info
 RETURNS:           0
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void cust_info(Customer *cust,int id){

	int accnt_num = 0;
	for(int i=0; cust[id].acc[i].accid[0]&&i < ARRAY_SIZE(cust[id].acc);i++){
		accnt_num++;
	}

	cout<<setw(11) <<"Record No." << ":"<<id << endl;
	cout<<setw(11) <<"Customer Id" << ":"<<cust[id].custID << endl;
	cout<<setw(11) <<"Last Name" << ":"<<cust[id].lname << endl;
	cout<<setw(11) <<"First Name" << ":"<<cust[id].fname << endl;
	cout<<setw(11) <<"Middle Name" << ":"<<cust[id].mname << endl;
	cout<<setw(11) <<"Tax ID Num" << ":"<<cust[id].tid << endl;
	cout<<setw(11) <<"Num acts. " << ":"<<accnt_num << endl;
	cout<<"Acct ID       Balance                    rate   C/Y" <<endl<<
          "-------       ----------------------     ----  -----"
    <<endl;
	cout<< setprecision(2)<<fixed;
	//cout<< "First entry check: "<< cust[id].acc[0].accid<<endl;
	for(int i=0; cust[id].acc[i].accid[0]&&i < ARRAY_SIZE(cust[id].acc);i++){
		//cout<< "Before if " << endl;
		if(cust[id].acc[i].accid[0]){
		//cout<< "Inside loop"<< endl;
		cout<<left<< setw(7)<<cust[id].acc[i].accid << "       "<<left<< setw(22) << cust[id].acc[i].acc_bal << "     "<<left<<setw(4)<<
  
		cust[id].acc[i].growth_rate <<"  "<< left<< setw(5)<< cust[id].acc[i].comp_per_year<<endl;
	}	
}




}
/*-----------------------------------------------------------------------------
 FUNCTION:          menu()
 DESCRIPTION:       programs ui interface
 RETURNS:           int
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
int menu(){
  cout<< "Menu: "<< endl;
  int choice=-1;
  char entry;
  while(choice<0){
		cout<< "1.)Create Portfolio" << endl
			<<"2.)Create Stock and Bond Accounts"<<endl
			<<"3.)Display Information"<<endl
			<<"a.)Display Information for all customers"<<endl
			<<"4.)Display Projections"<<endl
			<<"5.)Display Report"<<endl
			<<"6.)Write Database to file"<<endl
			<<"q.)Quit"<<endl;
			//cin>> choice;
			//cout<< choice << endl;
			//cin.get();
			
			cin >> entry;
			
			choice = (int)entry;
			if(!(choice == 'a') || !(choice == 'q')){
				choice = choice - '0';
			}

			
        if(choice >0 && choice <8 || choice == 49 || choice == 65){
			//cout<< "you chose: " << choice<< endl;

        }else{
			
          cout<< "Invalid Choice of... "<< endl;
		  cout<< endl;
		  //cout<< "you chose: " << choice<< endl;
          //choice = -1;
			
        }
  }



  return choice;
}
/*-----------------------------------------------------------------------------
 FUNCTION:          searchid()
 DESCRIPTION:       searches the structure for a matching id
 RETURNS:           int
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
int searchid(Customer *cust,int num_recs){
	int returning;
	char idf[6];
      bool found = 0;
      while(found != 1){
      cout << "Enter Customer ID" << endl;
      //cout<< num_recs<<endl;
      cin >> idf;
	  upper_case(idf);
      //cout<< "Beginning Search for "<<idf << endl;
      for(int i = 0; cust[i].custID[0]; i++){
      //cout<<i<<":"<<cust[i].custID << endl;
        if(cust[i].custID[0]){


                 // cout<< "Id: " << cust[i].custID << " Searching    for: "<< idf << endl;
                  if(strcmp(cust[i].custID, idf) == 0){
                    //cout<< "found: "<<idf <<endl;
                  
                  returning = i;
                  found =1;
                  break;
                  
                  
                  
                }else{
                  if(!found){
                  
                  
                  }

                }
			}
        }
		if(found != 1){
			cout<< "Invalid Id.. try again" << endl;
			
		}
              //cout<< "Exited search"<<endl;
      }
      //cout<< "Exited While" << endl;
      
	return returning;
}
/*-----------------------------------------------------------------------------
 FUNCTION:          yes_no()
 DESCRIPTION:       collects a yes or no user input
 RETURNS:           Either a y or a n char
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
char yes_no(){
	char yn= 'c';
	while(yn != 'y'&& yn != 'n'){
        
        cout<< "Would you like a custom output file (y/n)?: ";
        cin>> yn;
        
        cout<< endl;
    }

	return yn;
}

/*-----------------------------------------------------------------------------
 FUNCTION:          create_cust()
 DESCRIPTION:       creates a new customer and registers it to the database file
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void create_cust(Customer *cust,int* num_recs){

  char custID[6];
  char lname[20];
  char fname[20];
  char mname[20];
  char tid[20];
  char phonenum[20];
  
  //cout << "Starting Customer creator"<<endl;
  cout<<"";
      cout<< "Enter Customer ID: ";
      str_input(custID,"Enter Customer ID: ",sizeof(custID));
	  upper_case(custID);

      cout<< endl;


      cout<< "Enter Last Name: ";
      str_input(lname,"Enter Last Name: ",sizeof(lname));

      cout<< endl;


      cout<< "Enter First Name: ";
      str_input(fname,"Enter First Name: ",sizeof(fname));

      cout<< endl;

      cout<<"Enter Middle name: ";
      str_input(mname,"Enter Middle name: ",sizeof(mname));

      cout<< endl;


      cout<<"Enter Tax ID: ";
      str_input(tid,"Enter Tax ID: ",sizeof(tid));
	  upper_case(tid);

      cout<< endl;

      cout<< "Enter Phone Number: ";
	  cin.ignore();
      cin.getline(phonenum,20);
      cout<< endl;




	for(int i = 0; cust[i].custID[0]; i++ ){

		if(!cust[i+1].custID[0]){
			//cout<< "Missing ID: " << endl;
			strcpy(cust[i+1].custID ,custID);
			strcpy(cust[i+1].lname ,lname);
			strcpy(cust[i+1].fname ,fname);
			strcpy(cust[i+1].lname ,lname);
			strcpy(cust[i+1].mname ,mname);
			strcpy(cust[i+1].tid ,tid);
			strcpy(cust[i+1].phonenum,phonenum);
	break;
    }


  }
  
  
	//cout<<"Rec amount:"<< *num_recs << endl;
	*num_recs+=1;
	//cout<<"Rec amount After:"<< *num_recs << endl;
	//cout<<"ID: " << cust[*num_recs].custID <<endl; 

	//account_info acc[5];
}
/*-----------------------------------------------------------------------------
 FUNCTION:          str_input()
 DESCRIPTION:       gets user inputted str and validates its length. 
					Invalid data is looped with a custom outputted
					phrase
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void str_input(char* input,char* phrase,int orig){
	
	
	
	cin>> input;
	while(strlen(input) > orig){
		cout<< "Input should be less than " << orig << endl;
		cout<< phrase;
		cin>> input;
		cout<< endl;
	}
	
}


/*-----------------------------------------------------------------------------
 FUNCTION:          create_acc()
 DESCRIPTION:       creates a new account for the specified customer
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void create_acc(Customer *cust,int num_recs){
  char accid[7];
  double acc_bal;
  double growth_rate;
  int comp_per_year;

  cout<< "Enter account ID: ";
  str_input(accid,"Enter account ID: ",sizeof(accid));
  upper_case(accid);
  cout<<endl;

  cout<< "Enter account balance: ";
  cin>>acc_bal;
  cout<<endl;

  cout<< "Enter growth rate percentage: ";
  cin>> growth_rate;
  cout<< endl;

  cout<< "Enter Comp per year: ";
  cin>>comp_per_year;
  cout<<endl;

  int CustNum; 
  CustNum = searchid(cust,num_recs);
  cout<<"CustNum "<< CustNum << endl;
	if(cust[CustNum].acc[0].accid[0]){
		for(int i = 0; cust[CustNum].acc[i].accid[0]; i++){
		//cout<< cust[CustNum].acc[i].accid << endl;
			if(cust[CustNum].acc[i].accid[0]){
			cout<< "Accounts Already exist" << endl;
			if(!cust[CustNum].acc[i+1].accid[0]){
				cout<< "Missing ID: " << endl;
				strcpy(cust[CustNum].acc[i+1].accid ,accid);
				cust[CustNum].acc[i+1].acc_bal=acc_bal;
				cust[CustNum].acc[i+1].growth_rate=growth_rate;
				cust[CustNum].acc[i+1].comp_per_year=comp_per_year;
      
				break;

				}
			}
		}
	}else{
	//cout<< "no accounts" << endl;
	strcpy(cust[CustNum].acc[0].accid ,accid);
      cust[CustNum].acc[0].acc_bal=acc_bal;
      cust[CustNum].acc[0].growth_rate=growth_rate;
      cust[CustNum].acc[0].comp_per_year=comp_per_year;
	
	}
  
  

}
/*-----------------------------------------------------------------------------
 FUNCTION:          trim()
 DESCRIPTION:       removes all spaces and tabs from a cstring
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void trim(char* string){
  int length = strlen(string);
  for(int i = 0; i < length; i++){
    if(string[i] == ' ' && string[i+1] != '\0' && string[i+1] != ' '){
      //cout<< "replacing: "<< string[i] << "with: "<<string[i+1]<<endl;
      string[i]= string[i+1];
      string[i+1]= ' ';
    }else{
		//End of string check
        if(string[i+1] == '\0'){
          //cout<< "String end" << endl;
        }
		//trims dashes
        if(string[i+1] == ' '){
			
          //cout<< "Inserted terminating charchter" << endl;
          string[i+1] = '\0';
        }
    }
  }
}
/*-----------------------------------------------------------------------------
 FUNCTION:          function_switch()
 DESCRIPTION:       redirects the program to the proper functions based on menu input
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void function_switch(Customer *cust,char* outputted, int* num_recs ){
	
	int choice = -1;
	while (choice != 65){
      choice =menu();
      int rid;
      int years = 0;
      char namec[20];
      char yn;
      
      switch(choice){
        case 1:
        create_cust(cust,num_recs);
      
        break;

        case 2:
			create_acc(cust, *num_recs);

        break;

        case 3:
			//cout<< "PRECHECK: " << cust[0].custID <<endl;
			rid = searchid(cust,*num_recs);
			//cout<< "RID:" <<rid <<endl;
			cout<<""<<endl;
			cust_info(cust,rid);
        break;  
		
		case 49:
		
			for(int i = 0; cust[i].custID[0]; i++){
				//cout<< "Id: " << cust[i].custID << " Searching    for: "<< argv[3+1] << endl;
				if(cust[i].custID[0]){
					cust_info(cust,i);
					cout<< endl;
				}
			}
		
		break;

        case 5:
			//all proj
			
			cout<< "Years: ";
			cin>> years;
			cout<< endl;
			yn = yes_no();
			if(yn == 'y'){
				//cout<< "Entering custom name input" << endl;
				cout<< "What will the name of the output file be: ";
				cin>> namec;
				
				if(namec[1]){
          
					report(cust,0,years,namec,1);


				}else{
					report(cust,0,years,"Cust_Rpt.txt",1);

				}
        
            }else{
				if(yn == 'n'){
					
					report(cust,0,years,"Cust_Rpt.txt",1);
					
				}
				
			}
			
			cout<< endl;
					
		break;

		case 4:
			rid = searchid(cust,*num_recs);
			
			cout<<""<<endl;
			cout<< "Years: ";
			cin>> years;
			cout<< endl;
			report(cust,rid,years,"Cust_Rpt.txt",0);
			
			
			//cout<< "yes_no() returned: "<<yn<< endl; 
            			
			break;
			
			case 6:
				cout<< "Specify a custom output name: ";
				cin>> outputted;
				cout<< endl;

			break;

			case 65:
      
      
			break;
        }

	  
    }
	
	
	
	
}
  /*-----------------------------------------------------------------------------
 FUNCTION:          command_line_interp()
 DESCRIPTION:       interprits command line arguments and redirects the program
 accordingly
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void command_line_interp(Customer *cust,char* argv[], char* outputted, int* num_recs){
	
	if(argv[2+1]){
      //cout << "argv[3]: "<<argv[3]<<endl;
      if(strcmp(argv[2+1], "-cust") == 0){
        //cout << " -cust argument" << endl;
        if(argv[3+1]){
			upper_case(argv[4]);
          if(argv[4+1]){
            //cout<< "4th arg: " << argv[4] << endl;
            if(argv[4+1]){
				
				if(strcmp(argv[5],"-info")==0){
					for(int i = 0; i < *num_recs; i++){
					//cout<< "Id: " << cust[i].custID << " Searching    for: "<< argv[3+1] << endl;
						if(strcmp(cust[i].custID, argv[3+1]) == 0){
							cust_info(cust,i);
							break;
						}
					}
					
					
				}else{
					char* cpy = argv[5];
					//cout<< "Fresh cpy: " << cpy << endl;
					//cout<< "Cpy = " << cpy << endl;
					dash_remover(cpy);
					for(int i = 0; i < *num_recs; i++){
					//cout<< "Id: " << cust[i].custID << " Searching    for: "<< argv[3+1] << endl;
						if(strcmp(cust[i].custID, argv[3+1]) == 0){
							report(cust,i,atoi(cpy),"Cust_Rpt.txt",0);
							break;
						}
					}
					
				}
                
            }
          }
        }
        

      }

      if(strcmp(argv[2+1], "-out") == 0){
        //cout << " -out argument" << endl;
        if(argv[3+1]){


          strcpy(outputted,argv[4]);
		  //cout<< outputted<< endl;
          
        }
      
      }else{

      }

      if(strcmp(argv[3], "-rpt") == 0){
        if(argv[4]){
          //cout << " -rpt argument" << endl;
          if(argv[5]){
			  
					char* cpy = argv[5];
					//cout<< "Fresh cpy: " << cpy << endl;
					//cout<< "Cpy = " << cpy << endl;
					dash_remover(cpy);
					
						
						report(cust,0,atoi(cpy),argv[4],1);
						cout<< endl;
					
				}else{
					//cout<< "No Argv[5]"<<endl;
					
					//cout<< "Id: " << cust[i].custID << " Searching    for: "<< argv[3+1] << endl;
						
							report(cust,0,1,argv[4],1);
							
				}
                
			}
      
		}
      if(isdigit(argv[3][1])){
		  char* cpy = argv[3];
		  dash_remover(cpy);
          //cout<< "Contains digit" << endl;
            
              report(cust,0,atoi(cpy),"Cust_Rpt.txt",1);
              cout<< endl;
            
        }
    }
	
}
/*-----------------------------------------------------------------------------
 FUNCTION:          dash_remover()
 DESCRIPTION:       removes all -'s from command line arguments.
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void dash_remover(char *input){
	
	for(int i = 0; input[i];i++){
						
		if(input[i] == '-'){
			input[i] = ' ';
		}
	
	}
}
/*-----------------------------------------------------------------------------
 FUNCTION:          upper_case()
 DESCRIPTION:       Turns all lowercase charachters in a c-string to uppercase
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void upper_case(char* input){
	for(int i = 0; input[i];i++){
						
		if(input[i] != '\0'){

			input[i] = (char)toupper(input[i]);
			
		}else{
			
			
				cout<< "Found \0" << endl;
			
		}
	
	}
	
}
/*-----------------------------------------------------------------------------
 FUNCTION:          help_menu()
 DESCRIPTION:       Prints the help menu to the screen
 RETURNS:           n/a
 NOTES:             Optional notes on this function
 ------------------------------------------------------------------------------- */
void help_menu(){
	cout<<"Help Menu:       $ means input"<<endl
		<<"|-------------------------------------------------------------------------------------------------------------------------"<<endl
		<<"|"<<setw(40)<<"Help Menu"<<setw(39)<<""<<endl
		<<"|-------------------------------------------------------------------------------------------------------------------------"<<endl
		<<"|"<<setw(30)<<"Interactive Mode"<<" | "<< "./cust_ports -f $filename" <<endl
		<<"|"<<setw(30)<<""<<" | "<< "" <<endl
		<<"|"<<setw(30)<<"Show Single Customer Info"<<" | "<< "./cust_ports -f $filename -cust $cust_id -info" <<endl
		<<"|"<<setw(30)<<""<<" |"<< "" <<endl
		<<"|"<<setw(30)<<" Single Customer Projection"<<" | "<<setw(57)<<"./cust_ports -f $filename.dat -cust $customer_Id -$num_years  "<<endl
		<<"|"<<setw(30)<<""<<" | "<< "" <<endl
		<<"|"<<setw(30)<<"All Customer Projection"<<" | "<< "./cust_ports -f $filename.dat -$num_years " <<endl
		<<"|"<<setw(30)<<""<<" | "<< "" <<endl
		<<"|"<<setw(30)<<"All Customer report default"<<" | "<< " ./cust_ports -f $filename.dat -rpt $output_file_name " <<endl
		<<"|"<<setw(30)<<""<<" |"<< "" <<endl
		<<"|"<<setw(30)<<"All Customer Report custom"<<" |"<< " ./cust_ports -f $filename.dat -rpt $output_file_name -$num_years" <<endl
		<<"|"<<setw(30)<<""<<" |"<< "" <<endl
		<<"|"<<setw(30)<<"Custom Output"<<" |"<< " ./cust_ports -f $filename.dat -out $output_file_name.dat" <<endl
		<<"|"<<setw(30)<<""<<" |"<< "" <<endl;
		
	
	
	
}

