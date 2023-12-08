/*
Command line app to convert an SQL query against a MySQL database to a JSON file
Dave Gill
dave@stem.or.guk
Dec-2023
Compilation instructions
	gcc get_json.c -o get_json `mysql_config --cflags --libs`
	REQUIRED LIBRARY
	libmysqlclient-dev
*/
#include "mysql_includes.h"
#include <stdbool.h>

int main(int argc, char *argv[]){
    if (argc != 7){
        printf("\n%s%s%s\n\n%s\n\n%s\n",
            "Usage: ", argv[0], " host port user password database sql",
            "The Sql will be executed against the host database.",
            "The output will be sent to STD Output in JSON format.");
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

    // Start JSON output
    printf("[\n");
    bool first_row = true;
    while ((row = mysql_fetch_row(result))){
        if (!first_row){
            printf(",\n");
        }
        first_row = false;
        printf("    {");
        for(int i = 0; i < num_fields; i++){
            field = mysql_fetch_field_direct(result, i);
            if (i > 0){
                printf(", ");
            }
            printf("\"%s\": \"%s\"", field->name, row[i] ? row[i] : "NULL");
        }
        printf("}");
    }
    printf("\n]\n");

    mysql_free_result(result);
    mysql_close(con);
    return 0;
}

