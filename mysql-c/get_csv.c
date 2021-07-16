/*
Command line app to convert an SQL query against a MySQL database to a CSV file
Dave Gill
dave@beerhawk.co.uk
Dec-2017
Compilation instructions
	gcc get_csv.c -o get_csv `mysql_config --cflags --libs`
	REQUIRED LIBRARY
	libmysqlclient-dev
*/

#include "mysql_includes.h"

int main(int argc, char *argv[]){
	if (argc != 7){
		printf("\n%s%s%s\n\n%s\n\n%s\n",
			"Usage: ", argv[0], " host port user password database sql",
			"The Sql will be executed against the host database.",
			"The output will be sent to STD Output in csv format.");
		exit(0);
	}
	MYSQL *con;
	con = initialise_mysql(argv[1],argv[2],argv[3],argv[4], argv[5]);
	if (mysql_query(con, argv[6])){
      		throw_mysql_error(con);
  	}
	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL){
      		throw_mysql_error(con);
	}
	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	int fields = 1;
	while(field = mysql_fetch_field(result)) {
		if (fields == num_fields){
	        	printf("%s", field->name);
		} else {
	        	printf("%s,", field->name);
		}
		fields++;
        }
	printf("\n");
	while ((row = mysql_fetch_row(result))){
      		for(int i = 0; i < num_fields; i++){
			if (i == (num_fields -1)){
	          		printf("%s", row[i] ? row[i] : "NULL");
			} else {
        	  		printf("%s,", row[i] ? row[i] : "NULL");
			}
      		}
        	printf("\n"); 
  	}
  	mysql_free_result(result);
	mysql_close(con);
}
