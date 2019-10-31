#include "spellChecker.h"

	void *worker_thread(server *server) {
    	while(1) {
        	//lock clientQ
        	pthread_mutex_lock(&server->job_mutex);
        	//if client Q is empty
        	while (server->job_front == server->job_front && server->job_count == 0) {
            		pthread_cond_wait(&server->job_not_empty, &server->job_mutex);
        	}
        	//get socket from clientQ
        	int socket = remove_job(server);
        	//send signal that Q is not full
        	pthread_cond_signal(&server->job_not_full);
        	//unlock mutex
        	pthread_mutex_unlock(&server->job_mutex);
	}
	}
