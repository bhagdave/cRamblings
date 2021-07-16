#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

void throw_mysql_error(MYSQL *con){
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

MYSQL * initialise_mysql(char *host, char *port, char *user, char *passwd, char *db){
    int iPort;
	MYSQL *con = mysql_init(NULL);
	if (con == NULL){
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
    iPort = atoi(port);
	if (mysql_real_connect(con,host,user,passwd,db,iPort,NULL,0) == NULL){
		throw_mysql_error(con);
	}
	return con;
}
