#include "header.h"
MYSQL *conn;
char query[200] = "";
void init()
{
	conn = mysql_init(NULL);
	if(conn == NULL){
		fprintf(stderr,"mysql initiation error : %s\n",mysql_error(conn));
		exit(1);
	}
	return ;
}
void connect_to_db()
{
	char *database = "database_name";
	char *password = "your password";
	if(!mysql_real_connect(conn,"localhost","root",password,database,0,NULL,0)){
		fprintf(stderr,"Error Connecting to database : %s\n",mysql_error(conn));
		exit(1);
	}
	printf("Connection Established\n");
	return ;
}
void insert()
{
	strcat(query,"insert into customer(name,mobile,description) values('");
	char temp[20],mob[11],des[100];
	long int n;
	printf("Enter the name : ");
	scanf(" %[^\n]",temp);
	strcat(query,temp);
	strcat(query,"',");
	printf("Enter the mobile : ");
	scanf("%ld",&n);
	sprintf(mob,"%ld",n);
	strcat(query,mob);
	strcat(query,",'");
	printf("Enter some description of plan : ");
	scanf(" %[^\n]",des);
	strcat(query,des);
	strcat(query,"');");
	if(mysql_query(conn,query)){
		fprintf(stderr,"Query Error : %s\n",mysql_error(conn));
		exit(1);
	}
	query[0]='\0';
	strcat(query,"insert into plan(area,advance,total) values(");
	float area;
	printf("Enter the area of plan : ");
	scanf("%f",&area);
	sprintf(temp,"%.3f",area);
	strcat(query,temp);
	strcat(query,",");
	printf("Enter the Advance taken : ");
	scanf("%ld",&n);
	sprintf(temp,"%ld",n);
	strcat(query,temp);
	strcat(query,",");
	printf("Enter the Total Amount : ");
	scanf("%ld",&n);
	sprintf(temp,"%ld",n);
	strcat(query,temp);
	strcat(query,");");
	if(mysql_query(conn,query)){
		fprintf(stderr,"Query Error : %s\n",mysql_error(conn));
		exit(1);
	}
	mysql_close(conn);
	return ;
}
void delete()
{
	short int a,b;
	char name[20];
	strcat(query,"delete from plan where ");
	printf("0. To Exit\n");
	printf("1. by UID\n");
	printf("2. by name\n");
	printf("Enter your choice : ");
	scanf("%hd",&a);
	switch(a){
		case 0:
			exit(0);
		case 1:
			printf("Enter the UID to Delete : ");
			scanf("%hd",&b);
			sprintf(name,"uid = %hd;",b);
			strcat(query,name);
			break;
		case 2:
			printf("Enter the name to Delete : ");
			scanf(" %[^\n]",name);
			strcat(query,"name ='");
			strcat(query,name);
			strcat(query,"';");
			break;
		default:
			printf("Enter a valid  choice\n");


	}
	if(mysql_query(conn,query)){
		fprintf(stderr,"Query Error : %s\n",mysql_error(conn));
		exit(1);
	}
	query[0] = '\0';
	if(a == 1){
		strcat(query,"delete from customer where ");
		strcat(query,name);
	}
	else{
		strcat(query,"delete from customer where name = '");
		strcat(query,name);
		strcat(query,"';");
	}
	if(mysql_query(conn,query)){
		fprintf(stderr,"Query Error : %s\n",mysql_error(conn));
		exit(1);
	}
	mysql_close(conn);
	return ;
}
void display()
{
	printf("0. Exit\n");
	printf("1. Display all(everything)\n");
	printf("2. Display completed\n");
	printf("3. Display incompleted\n");
	printf("Enter the choice :");
	short int a;
	scanf("%hd",&a);
	query[0] = '\0';
	switch(a){
		case 0:
			exit(0);
			break;
		case 1: 
			strcat(query,"select * from customer inner join plan on customer.uid = plan.uid;");
			break;
		case 2:
		       	printf("0. Exit\n");
			printf("1. Completed Status\n");
			printf("2. Payment Status\n");
			scanf("%hd",&a);
			if(a == 0 || !(a == 1 || a == 2))
				exit(0);
			else if(a == 1)
				strcat(query,"select customer.uid,customer.name from customer inner join plan on customer.uid = plan.uid where status = true;");
			else if(a == 2)
				strcat(query,"select customer.uid,customer.name from customer inner join plan on customer.uid = plan.uid where paid = true;");
			
			break;
		case 3:
		       	printf("0. Exit\n");
			printf("1. Completed Status\n");
			printf("2. Payment Status\n");
			scanf("%hd",&a);
			if(a == 0 || !(a == 1 || a == 2))
				exit(0);
			else if (a ==1 )
			strcat(query,"select customer.uid,customer.name,plan.advance,plan.total,plan.due from customer inner join plan on customer.uid = plan.uid where status = false;");
			else if (a == 2)
			strcat(query,"select customer.uid,customer.name,plan.advance,plan.total,plan.due from customer inner join plan on customer.uid = plan.uid where paid = false;");
			break;
		default:
			printf("Enter valid choice !\n");
			exit(0);

	}
	if(mysql_query(conn,query)){
		fprintf(stderr,"Query error : %s \n",mysql_error(conn));
		exit(1);
	}
	MYSQL_ROW row;
	MYSQL_RES *res= mysql_store_result(conn);
	int num_fields = mysql_num_fields(res);
	while ((row = mysql_fetch_row(res))!= NULL) {

	for (int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        	printf("\n");
   	}
	mysql_close(conn);
	return;
}
void payment_status(){
	short int a;
	printf("0. Exit\n");
	printf("1. Check Payment Status\n");
	printf("2. Change Payment status\n");
	printf("Enter the choice : ");
	scanf("%hd",&a);
	switch(a){
		case 0: 
			exit(0);
		case 1: 
			query[0]='\0';
			strcat(query,"select customer.uid,customer.name,plan.paid from customer inner join plan on customer.uid = plan.uid;");
			break;
		case 2:
			printf("Enter the uid of the plan to complete payment : ");
			scanf("%hd",&a);
			sprintf(query,"update plan set paid = true ,advance = if(paid = true,total ,advance) where uid = %hd;",a);
			break;
		default:
			printf("Enter a valid choice ! \n");
			break;
	}
	if(mysql_query(conn,query)){
		fprintf(stderr,"Query error : %s\n",mysql_error(conn));
		exit(1);
	}
	mysql_close(conn);
	return ;
}
void search(){
	long int a ;
	printf("Enter the mobile no to search : ");
	scanf("%ld",&a);
	sprintf(query,"select customer.uid,customer.name,plan.status,plan.paid from customer inner join plan on customer.uid = plan.uid where customer.mobile = %ld;",a);
	if(mysql_query(conn,query)){
		fprintf(stderr,"Query error : %s\n",mysql_error(conn));
		exit(1);
	}
	MYSQL_ROW row;
	MYSQL_RES *res= mysql_store_result(conn);
	int num_fields = mysql_num_fields(res);
	while ((row = mysql_fetch_row(res))!= NULL) {
		for (int i = 0; i < num_fields; i++) {
            		printf("%s\t", row[i] ? row[i] : "NULL");
        	}
        	printf("\n");
   	}
	mysql_close(conn);
	return;
}
void change_status()
{
	short int a;
	printf("Enter the uid to change the status : ");
	scanf("%hd",&a);
	sprintf(query,"update plan set status = true where uid = %hd;",a);
	if(mysql_query(conn,query)){
		fprintf(stderr,"Query error : %s\n",mysql_error(conn));
		exit(1);
	}
	mysql_close(conn);
	return ;
}
