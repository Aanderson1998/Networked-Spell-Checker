#include "spellChecker.h"

	void *loggerThread(void *serve){
	server *server=serve;
	while(1) {
		//lock log_mutex
		pthread_mutex_lock(&server->log_mutex);
		//check if log queue is empty
		while (server->log_front == server->log_rear && server->log_count == 0) {
			//if empty do a wait on log_not_empty condition variable
			pthread_cond_wait(&server->log_not_empty, &server->log_mutex);
		}
		//when queue is not empty get the log results at front of queue
		char *result = removeLog(server);
		//write results to log file
		fprintf(LOG, "%s\n", result);
		//clear output buffer
		fflush(LOG);
		//signal log_not_full condition variable
		pthread_cond_signal(&server->log_not_full);
		//unlock log_mutex
		pthread_mutex_unlock(&server->log_mutex);
		}
	}

