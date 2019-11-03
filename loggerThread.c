#include "spellChecker.h"

	void *loggerThread(server *server){
	while(1) {
        	//lock the log queue
        	pthread_mutex_lock(&server->log_mutex);
			//check if it's empty
        	while (server->log_front == server->log_rear && server->log_count == 0) {
            		pthread_cond_wait(&server->log_not_empty, &server->log_mutex);
        	}
        	//get the log results
        	char *result = removeLog(server);
        	//write results to log
        	fprintf(LOG, "%s\n", result);
        	//clean
        	fflush(LOG);
        	//signal queue isn't full
        	pthread_cond_signal(&server->log_not_full);
        	//unlock queue
        	pthread_mutex_unlock(&server->log_mutex);
    		}
	}

