# SQLiteMate
Simple and tiny SQLite3 DB requests assistant

******
Usage with CLI params:

red@RED-PC:~$ ./SQLiteMate My.db "SELECT * FROM Table"
where:
My.db: an SQL3 database
"SELECT * FROM Table": SQL query

******
Usage without CLI params:

red@RED-PC:~$ ./SQLiteMate

Database with the name 'My.db' will be open or created (if it is not present).
File with the name 'request.txt' with the SQL query will be open (file must exist).
File with the name 'response.txt' with the SQL query result will be created.