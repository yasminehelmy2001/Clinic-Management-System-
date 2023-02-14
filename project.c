#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
		char name[50];
		int age;
		char gender[10];
		int ID;
		struct node *next;   //next node holds the address of the next node in the linked list. (pointer to node)
	}node;
	
	typedef struct slot{
		char time[50];
		int IDslot;
		struct slot*next;
	}slot;
	
	
	void push(node ** head,char ptrname[], int age_value, char ptrgender[] ,int ID_value){
		
	node*newnode=(node*)malloc(sizeof( node)); //creating a new node with size of everything inside struct and with a pointer poiting to its first location (newnode pointer)
	strcpy(newnode->name,ptrname);  //The standard strcpy(str2,str1) function copies a given C-string to another string, even if str2 is an array of char
	newnode->age=age_value;
	strcpy(newnode->gender,ptrgender);
	newnode->ID=ID_value;
	
	newnode->next=*head;        //newnode points to node that head is pointing to
	*head=newnode;    //head points to newnode
}

void edit(node * ptr,char ptrname[], int age_value, char ptrgender[] ,int ID_value){
	//editing values
	strcpy(ptr->name,ptrname);  
	ptr->age=age_value;
	strcpy(ptr->gender,ptrgender);
	ptr->ID=ID_value;
	
}

void print_node(node*head)
{
	struct node *temp=head; //address inside temp is address of first node
	while(temp!=NULL)  //until the end of the list
	{
		printf("Name is: %s\n", temp->name);
		printf("Age is: %d\n", temp->age);
		printf("Gender is: %s\n", temp->gender);
		printf("ID is: %d\n", temp->ID);
		temp=temp->next; //move to the next node
		printf("\n");
	}
	
	
}

void print_user(node*tmp)              //tmp is address of a node in a linked list(whichever one the user wants to print.)
{
	printf("Name is: %s\n", tmp->name);
	printf("Age is: %d\n", tmp->age);
	printf("Gender is: %s\n", tmp->gender);
	printf("ID is %d\n", tmp->ID);
}

int check_ID(node*head,int ID)
{
	node*temp=head;         
					
	while(temp!=NULL) //until the end of the list
	{
	if(temp->ID==ID)
	{
	 printf("ID exists, please try again: ");
     scanf("%d", &ID);
   	temp=head;             //search from the beginning of the list if the new ID entered exists or not
	}
	if(temp->ID!=ID)
	{
	temp=temp->next;       //move to the next node to check if ID matches
	}
	}
    return ID;
	
}
int check_ID_edit(node*head,int ID,node*ptr)
{
	node*temp=head;         
					
	while(temp!=NULL) //until the end of the list
	{
	if(temp->ID==ID&&ptr->ID!=ID)           //if ID doesnt belong to a user except the user we are editing
	{
	 printf("ID exists, please try again: ");
     scanf("%d", &ID);
   	temp=head;             //search from the beginning of the list if the new ID entered exists or not
	}
	else
	{
	temp=temp->next;       //move to the next node to check if ID matches
	}
	}
    return ID;
	
}
int check_ID_exist(node*head,int ID,slot*beg)      //checks if ID belongs to a patient before reserving 
{
	node*temp=head;   //search from the beginning of the list     
	slot*ptr=beg;
	int count1=0,count2=0;			
	while(temp!=NULL) //until the end of the list
	{
	if(temp->ID==ID)
	{
		count1++;                  
		break;
	}
	else
	{
	temp=temp->next;       //move to the next node to check if ID matches
	}
	}
	
	while(ptr!=NULL)
	{
		if(ptr->IDslot==ID)
		{
			
			count2++;
			break;
		}
		else
		{
			ptr=ptr->next;
		}
	}
if(count1==0)    //ID does not exist in database
{
	return 0;
}	
else if(count1==1&&count2==0)  //ID exists in data base and is not reserved
{
	return 1;                   
}
else
{
	return 2;                    //ID exists in data base but is reserved
}
}

		  //if temp->ID!=ID in all nodes, ID does not belong to a patient, so admin can't reserve a slot.
		
	

	




void add_time(slot**head,char time[]) //if we want to send head, we will receive it in node*head, but since we want to change in head (pass by reference), we send
//&head, so we receive it as node**head.
{
	slot*newslot;
	newslot=(slot*)malloc(sizeof(slot)); //newslot is a pointer to the first address in the newslot node
	strcpy(newslot->time,time);
	newslot->IDslot=0;         //all ID values are equal to 0 until a user reserves it. By doing this, in user feature, we only print slots with ID!=0.
	newslot->next=*head;
	*head=newslot;
}

void print_available_slots(slot*head)
{
struct slot *temp=head; //address inside temp is address of first node
	int i=1;
	while(temp!=NULL)  //until the end of the list
	{
		if(temp->IDslot==0)
		{
		printf("\n%d- %s",i, temp->time);         //print only slots with ID==0 as reseved slots have ID!=0. ex(slot 4:30-5:00 has ID:2323, it is reserved so we don't print it)
		temp=temp->next;
		i++;
		}
		else
		{
			temp=temp->next;
		}
		
	}
	printf("\n");
}

void reserve_slot(slot*beg,char desiredslot[],int patientID)
{
	slot*point=beg;
	int count=0;
				while(point!=NULL)
				{
					if(strcmp(point->time,desiredslot) == 0)                 //I cant use st1==str2, must user strcmp function   //if time selected by user exists in linked list, reserve the slot to the user (enter their ID to the node of timing selected)
					{
						point->IDslot=patientID;
						count++;
						break;
					}
					
					else{
					point=point->next;
					}
				}
				if(count==0)
				{
					printf("Incorrect timing entered.\n"); //time entered doesnt exist in linked list                 
				}
				else
				{
					printf("reservation successful!\n");
				}
}

void delete_reserved_slot(slot*beg,int patientID)
{
	int count=0;
	slot*point=beg;
	while(point!=NULL)
				{
					if(point->IDslot==patientID)                 
					{
						point->IDslot=0;             //delete ID reserved in the node of timing selected so the timing can be available again.
						count++;
						break;
					}
					
					else{
					point=point->next;
					}
				}
				if(count==0)
				{
				printf("ID is not reserved.\n");        //ID must be reserved in order to delete reservation
				}
				else{
					printf("reservation cancelled.\n");
				}
}

void print_reserved_slots(slot*beg)
{
struct slot *temp=beg; //address inside temp is address of first node
	int i=1;
	while(temp!=NULL)  //until the end of the list
	{
		if(temp->IDslot!=0)             //print slots/nodes with ID=(user ID), not ID=0 as ID=0 is not reserved for anyone
		{
		printf("\n%d- %s: %d",i, temp->time,temp->IDslot);
		temp=temp->next;
		i++;
		}
		else
		{
			temp=temp->next;
		}
		
	}
	printf("\n");
}

void update_reserv(slot*beg,int ID,int IDedit)         //update reservation ID after editing it in database
{
	slot*ptr=beg;
	while(ptr!=NULL)
	{
		if(ptr->IDslot==IDedit)   
		{
			ptr->IDslot=ID;
			break;
		}
		else
		{
			ptr=ptr->next;
		}
	}
}

void main (void)
{
	//all initializations must be at the beginning
	node*head=NULL;     //creating a pointer to a node called head (a node which includes name, age, etc....)
	slot*beg=NULL;  //NULL as we want the last "next" address to be NULL. (last pointer to node of the linked list points to nothing)
	slot*pntr;
	
	int mode,password=0,countpass=0,admin_feature;
	int i,age,ID;
	int IDedit,contin;
	int user_feature, user_ID;
	int patientID,patientID2;
	int value;
	
	char name[100],gender[20];
	char time1[50]="2:00-2:30";
	char time2[50]="2:30-3:00";                  
	char time3[50]="3:00-3:30";
	char time4[50]="4:00-4:30";
	char time5[50]="4:30-5:00";
	char desiredslot[50];
	
	add_time(&beg, time5);
	add_time(&beg, time4);
	add_time(&beg, time3);
	add_time(&beg, time2);
    add_time(&beg, time1);
	
	
	bool counter=0;
	bool count=0;
	bool quit=0;
	bool exit=0;
	bool IDexists=0;
	
	while(1)
	{
	printf("\nInsert 0 for Admin mode or 1 for User mode: ");
	scanf("%d",&mode);
	if(mode==0)
	{
		printf("Enter Password: ");
	
			scanf("%d" ,&password);
			while(countpass<2&&password!=1234){
				
			printf("Incorrect password, Try again: ");
			scanf("%d" ,&password);
			countpass++;
				}
			if(password==1234)
			{
				
				printf("Welcome, Enter the number that corresponds to your needed feature\n 1-Add a new patient record.\n2-Edit a patient record.\n3-Reserve a slot with the doctor\n4-Cancel Reservation.\n");
				scanf("%d", &admin_feature);
				quit=0;
				while(quit==0)              //repeat switch case if number entered is not 1,2,3, or 4.
				{
				switch(admin_feature)
				{
				case 1:
					printf("Enter name: ");
					scanf("%s",name);
					printf("Enter age: ");
					scanf("%d", &age);
					printf("Enter gender: ");
					scanf("%s",gender);
					printf("Enter ID: ");
					scanf("%d", &ID);
					ID=check_ID(head,ID);
					push(&head,name,age,gender,ID);         //pushing a node to linked list
					quit=1;
					break;
					
				case 2:
					printf("enter ID you wish to edit: ");
					scanf("%d", &IDedit);
					struct node*ptr=head;
					count=0;
					
					while(ptr!=NULL)      //until the end of the list
					{
						if(ptr->ID==IDedit)
						{
						printf("Enter name: ");
						scanf("%s",name);
						printf("Enter age: ");
						scanf("%d", &age);
						printf("Enter gender: ");
						scanf("%s",gender);
						printf("Enter ID: ");
						scanf("%d", &ID);
						ID=check_ID_edit(head,ID,ptr);
						update_reserv(beg,ID,IDedit);   //update reservation ID after editing it in database
						edit(ptr,name,age,gender,ID);  //edit(ptr) because the address of the node we're changing is inside ptr.
						count++;
						break;
						}
						if(ptr->ID!=IDedit)
						{
							ptr=ptr->next;         //move to the next node to check if ID matches
						}
					}
					if(count!=1)
					{
						printf("ID not found");              //ID not found in all nodes of the linked list
					}
					quit=1;
					break;
					
					
				
				case 3: 
				
				
				printf("\n************Available Slots*************\n");
				print_available_slots(beg);
				printf("\n****************************************\n");	
				printf("\n");
				
				printf("\nEnter patient ID: \n");
				scanf("%d",&patientID);
				value=check_ID_exist(head,patientID,beg);       //value=0 if it doesnt exist in database =1 if ID exists in database and =2 if exists in database but is reserved already
				
				if(value==1)
				{
				printf("Enter desired slot: \n");
				scanf("%s",desiredslot);
				
				counter=0;
				while(counter==0)           //until time is entered correctly, keep looping
				{
				pntr=beg;
				
				while(pntr!=NULL)  //until the end of the list
				{
				if(strcmp(pntr->time,desiredslot)==0&&pntr->IDslot==0)   //check if desired slot exists AND is not reserved
				{
					reserve_slot(beg,desiredslot,patientID);           //then reserve it
					counter++;                                        //get out of while loop
					break;
				}
				else
				{
					pntr=pntr->next;
				}
				}
				
				if(counter==0)
				{
					printf("Invalid slot, please try again: ");
					scanf("%s", desiredslot);
				}
				}
				}
				
				else if(value==2)
				{
					printf("Slot already reserved for this ID.\n");     //value=0, patient ID is not registered to a user, so they can't reserve a slot
					
					
				}
				else if(value==0)
				{
					printf("ID does not exist in database.\n");
				}
				
				quit=1;
				break;
				
				case 4:
				printf("\nEnter patient ID: \n");
				scanf("%d",&patientID2);
				delete_reserved_slot(beg,patientID2);
				quit=1;          //quit=1 so leave while loop and switch case
				break;
				
				default:

				printf("Option doesn't exist, please enter a valid number: ");                              
				scanf("%d", &admin_feature);       //loop switch case again as quit=0. (number entered is incorrect).
				break;
				}

				
			}
			}
			
		}
		if(mode==1)
		{
			printf("Welcome. Enter the number corresponding to your needed feature\n1-View Patient Record.\n2-View today's reservations.\n");
			scanf("%d",&user_feature);
			exit=0;
			while(exit==0)            //ask user to enter a correct number if user entered a number other than 1 or 2.
			{
			switch(user_feature)
			{
				case 1:
				printf("Enter ID: ");
				scanf("%d", &user_ID);
				node*tmp=head;
				IDexists=0;
				while(tmp!=NULL)  //check until the end of the list
				{
					if(tmp->ID==user_ID)
					{
						printf("\n******************PATIENT RECORD********************\n\n");		
						print_user(tmp); //pointer tmp has the addressof the node we want to print the information of
						printf("\n****************************************************\n");	
							IDexists=1;          
						break;
					
					}
					else
					{
						tmp=tmp->next;
					}
				}
				if(IDexists==0)
				{
					printf("ID is not registered to a user.\n");      //ID was not found in all nodes of the linked list
				}
				exit=1;
				break;
				
				case 2:
				printf("\n******************TODAY'S RESERVATIONS********************\n");	
			print_reserved_slots(beg);
				printf("\n**********************************************************\n");	
				exit=1;
			break;
			
			default:
			printf("Option doesn't exist, please enter a valid number: ");
			scanf("%d", &user_feature);         //loop again
			break;
			}
			
			
			
			}
		}
		
	
	
}

}
		
		
	

	

	
