Basic functionality for login page. The only available username and password are "Username" and "Password" respectively.
Feel free to make any changes you see fit.

3/12/26:
    Added addInfo.c, which takes input for username and password as command line arguments and adds them to the database. It's not connected to the html files for now, but the functionality is there
    It's not easy to run and I don't know how to do it on blue. On my local machine the command to compile it is:
        
        gcc addInfo.c -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -o output

    To get the first 2 options, I ran the command mysql_config --include and mysql_config --libs respecitvely.
    after you compile the program it's pretty easy to run, just ./output username password


3/14/26:
    added a makefile for addInfo.c, Tested it to see it compile on my personal blue account, so hopefully it works for the team blue account.

I found the parameters for compiling by running the "mysql_config" command which shows the locations for all the libraries and include files for mysql  to work. 

the makefile only has 2 targets right now, default compiles addInfo.c into 
addInfo.cgi (as opposed to output). clean removes the addInfo.cgi file for now. 

you can just run the command "make" in the directory with the Makefile, and it should compile addInfo.c. Running "make clean" will run the clean target and remove addInfo.cgi

        -Kyle

3/15/26
    changed makefile to find the mysql include file and libs file, so as long as they exist on the machine it should work the same on mac as  the same on blue
    --Kyle
