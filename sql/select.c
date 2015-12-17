#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;
void display_header();
void display_row();

int main(int argc, char const *argv[])
{
	int res;
	int first_row = 1;

	mysql_init(&my_connection);
	if(mysql_real_connect(&my_connection, "localhost",
		"root","0000","my_test",0,NULL,0)){
		printf("connection success\n");
		res = mysql_query(&my_connection, 
			"SELECT * FROM PERSON");
		if(res){
			fprintf(stderr, "SELECT ERRPR %s\n", 
				mysql_error(&my_connection));
		}
		else{
			res_ptr = mysql_use_result(&my_connection);
			if(res_ptr){
				while((sqlrow = mysql_fetch_row(res_ptr))){
					if(first_row){
						display_header();
						first_row = 0;
					}
					display_row();
				}
				if(mysql_errno(&my_connection)){
					fprintf(stderr, "retive error: %s\n", 
						mysql_error(&my_connection));
				}
				mysql_free_result(res_ptr);
			}
		}
		mysql_close(&my_connection);
	}
	else{
		fprintf(stderr, "connection failed\n");
		if(mysql_errno(&my_connection)){
			fprintf(stderr, "connection error %d: %s\n",
			mysql_errno(&my_connection),mysql_error(&my_connection) );
			exit(-1);
		}
	}
	return 0;
}

void display_header(){
	MYSQL_FIELD *field_ptr;
	int i= 0;

	printf("Column details:\n");
	while((field_ptr = mysql_fetch_field(res_ptr)) != NULL){
		printf("\t Name: %s\n", field_ptr->name);
		printf("\t Type: \n");
		if(IS_NUM(field_ptr->type)){
			printf("Numeric field\n");
		}else{
			switch(field_ptr->type){
				case FIELD_TYPE_VAR_STRING:
					printf("VARCHAR\n"); break;
				case FIELD_TYPE_LONG:
					printf("LONG\n");	break;
				default:
				printf("Type is %d check in mysql_com.h\n",
						field_ptr->type);
			}
		}
		printf("\t Max width %ld\n", field_ptr->length);
		if(field_ptr->flags & AUTO_INCREMENT_FLAG){
			printf("\t Auto increments\n");
		}
		printf("\n");
	}

}

void display_row(){
	unsigned int field_count = 0;
	while(field_count < mysql_field_count(&my_connection)){
		if(sqlrow[field_count])
			printf("\t%10s", sqlrow[field_count]);
		else
			printf("NULL");
		field_count++;
	}
	printf("\n");
}

//-lmysqlclient