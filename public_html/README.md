Basic functionality for login page. The only available username and password are "Username" and "Password" respectively.
Feel free to make any changes you see fit.

3/12/26:
    Added addInfo.c, which takes input for username and password as command line arguments and adds them to the database. It's not connected to the html files for now, but the functionality is there
    It's not easy to run and I don't know how to do it on blue. On my local machine the command to compile it is:
        
        gcc addInfo.c -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -o output

    To get the first 2 options, I ran the command mysql_config --include and mysql_config --libs respecitvely.
    after you compile the program it's pretty easy to run, just ./output username password
    
