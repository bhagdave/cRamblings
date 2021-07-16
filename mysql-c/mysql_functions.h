#include <mysql.h>

void finish_with_error(MYSQL *);

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

MYSQL * initialiase(char * hostname, char * user, char *passwd, char * database){
	MYSQL *con = mysql_init(NULL);
	if (con == NULL){
    		fprintf(stderr, "%s\n", mysql_error(con));
      		exit(1);
	}
	mysql_real_connect(con, hostname,user,passwd,database,0,NULL,0);
	return con;
}
