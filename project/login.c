#include "header.h"
short int Login()
{
	init();
	connect_to_db();
	printf("0. Exit\n");
	printf("1. Admin\n");
	printf("2. user\n");
	printf("Login as :");
	short int a ;
	scanf("%hd",&a);
	switch(a){
		case 0: 
			exit(0);
		case 1:
			char passwd[10];
			printf("Enter the password of admin : ");
			scanf("%s",passwd);
			while(strcmp(passwd,"admin")){
				printf("Incorrect Password, Try again!\nEnter the password :");
				scanf("%s",passwd);
				if(!strcmp(passwd,"exit")){
					printf("Thank you !\n");
					return 1;
				}
			}
			Admin();
			break;
		case 2:
			User();
			break;

		default :
			printf("Enter a valid Choice\n");
			exit(0);
	}
}
void Admin()
{
	printf("you have login as Admin\n");
	printf("0. Exit\n");
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Display\n");
	printf("4. Search\n");
	printf("5. Change complete status\n");
	printf("6. Change Payment status\n");
       	printf("Enter your choice :");
	short int a;
	scanf("%hd",&a);
	switch(a){
		case 0:
			exit(0);
			break;
		case 1:
			insert();
			break;
		case 2:
			delete();
			break;
		case 3:
			display();
			break;
		case 4:
			search();
			break;
		case 5:
			change_status();
			break;
		case 6: 
			payment_status();
			break;
	}	
	return ;
}
void User()
{
	printf("Welcome User\n");
	printf("0. Exit\n");
	printf("1. Insert\n");
	printf("2. Change Complete status\n");
	printf("3. Display\n");
	printf("4. Search\n");
	printf("5. Change Payment status\n");
       	printf("Enter your choice :");
	short int a;
	scanf("%hd",&a);
	switch(a){
		case 0:
			exit(0);
			break;
		case 1:
			insert();
			break;
		case 2:
			change_status();
			break;
		case 3:
			display();
			break;
		case 4:
			search();
			break;
		case 5: 
			payment_status();
			break;
	}	
	return ;
}
