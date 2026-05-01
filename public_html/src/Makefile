all: currentBids.cgi purchases.cgi didntWin.cgi selling.cgi startAuction.cgi startBid.cgi getAuctions.cgi getAuctionsTable.cgi

startAuction.cgi: startAuction.cpp
	g++ -ggdb  startAuction.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/startAuction.cgi


currentBids.cgi: currentBids.cpp
	g++ currentBids.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/currentBids.cgi

purchases.cgi: purchases.cpp
	g++ purchases.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/purchases.cgi

didntWin.cgi: didntWin.cpp
	g++ didntWin.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/didntWin.cgi	

selling.cgi: selling.cpp
	g++ selling.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/selling.cgi



startAuctiontest.cgi: startAuctiontest.cpp
	g++ -ggdb  startAuction.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/startAuctiontest.cgi

startBid.cgi: startBid.cpp
	g++ startBid.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/startBid.cgi
getAuctions.cgi: getAuctions.cpp
	g++ getAuctions.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/getAuctions.cgi

getAuctionsTable.cgi: getAuctionsTable.cpp
	g++ getAuctionsTable.cpp -I/opt/homebrew/Cellar/mysql/9.6.0_1/include/ -L/opt/homebrew/Cellar/mysql/9.6.0_1/lib -lmysqlclient -lm -o ../cgi-bin/getAuctionsTable.cgi

