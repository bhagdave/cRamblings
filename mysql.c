#include <mysql.h>
#include <stdio.h>
int main(){
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW  row;
	char *server = "localhost";
	char *user   = "root";
	char *password = "h6redmine";
	char *database = "MS";
	conn =  mysql_init(NULL);
	if (!mysql_real_connect(conn,server,user, password, database,0,NULL,0)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	if (mysql_query(conn, "select * from campaign")){
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	printf("Tables");
	while((row = mysql_fetch_row(res))!= NULL){
		printf("%s \n",row[0]);
	}
	mysql_free_result(res);
	mysql_close(conn);
}
