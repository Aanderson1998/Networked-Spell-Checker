#include "spellChecker.h"


	char *removeLog(server *server) {
	//get the log input at front of log queue
    	char *logResult = logs[server->log_front];
    	logs[server->log_front] = (char *) calloc(1, sizeof(char *));
    	//increment the read pointer
    	server->log_front = (++server->log_front) % MAX_BUF_SIZE;
    	//decrement the log_count
    	--server->log_count;
    	return logResult;
	}
