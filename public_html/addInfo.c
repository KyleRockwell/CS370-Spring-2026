#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MYSQL_USERNAME "teamg_user"
#define MYSQL_PASSWORD "333333333"
#define MYSQL_DATABASE "teamg_db"

int main (int agrc, char *argv[])
{
  //Base length of the string to store input command, used later
  int BASE_LENGTH = 76;

  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  conn = mysql_init (NULL);
// ***********************
// * Connect to database *
// ***********************
  if (!mysql_real_connect(conn, "localhost", MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0))
  {
    fprintf (stderr, "%s\n", mysql_error(conn));
    return (0);
  }
// ****************
// * Send a query *
// ****************
  if (mysql_query(conn, "SELECT now()")) 
  {
    fprintf (stderr, "%s\n", mysql_error(conn));
    return (0);
  }

// ******************************
// * Retrieve result from query *
// ******************************
  res = mysql_use_result (conn);
  while ((row = mysql_fetch_row(res)) != NULL)
  {
    printf("%s\n", row[0]);
  }
  mysql_free_result (res);

  //Read comand line args into variables  
  char *username = argv[1];
  char *password = argv[2];

  //Calculate the total length of the string that stores the command
  int len1 = strlen(username);
  int len2 = strlen(password);
  int totalLen = BASE_LENGTH + len1 + len2;
  char *cmd = calloc(totalLen, sizeof(char));

  //Concatenate the commmand into cmd
  strcat(cmd, "INSERT INTO Users (Username, Password) VALUES (");
  strcat(cmd, "'"); 
  strcat(cmd, username);
  strcat(cmd, "'");
  strcat(cmd, ", ");
  strcat(cmd, "'");
  strcat(cmd, password);
  strcat(cmd, "'");
  strcat(cmd, ");");

  //Execute the command
  printf("%s", cmd);
  if( mysql_query(conn, cmd)) 
	printf("Good!");
  mysql_close (conn);
}
