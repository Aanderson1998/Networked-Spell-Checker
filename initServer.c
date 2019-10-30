#include "spellChecker.h"


	void initServer(server *server){
	//set job_count ptr to 0
    	server->job_count = 0;
	//set log count ptr to 0
    	server->log_count = 0;
	//set job_front ptr to 0
    	server->job_front = 0;
	//set job_rear ptr to 0
    	server->job_rear = 0;
	//set log_front ptr to 0
    	server->log_front = 0;
	//set log_rear ptr to 0
    	server->log_rear = 0;
	//create log and job mutex
    	if (pthread_mutex_init(&server->job_mutex, NULL) != 0) {
        	perror("couldn't initialize job mutex");
    		}
	if (pthread_mutex_init(&server->log_mutex, NULL) != 0) {
        	perror("Couldn't initialize log mutex");
    		}
	if (pthread_cond_init(&server->job_not_empty, NULL) != 0) {
        	perror("Couldn't initialize job_not_empty condition variable");
    		}
	if (pthread_cond_init(&server->log_not_empty, NULL) != 0) {
        	perror("Couldn't initialize log_not_empty condition variable");
    		}
	if (pthread_cond_init(&server->job_not_full, NULL) != 0) {
        	perror("Couldn't initialize job_not_full condition variable");
    		}
	if (pthread_cond_init(&server->log_not_full, NULL) != 0) {
        	perror("Couldn't initalize log_not_full condition variable");
    		}
	//allocating space for log and jobs in thread queues
	for(int i = 0; i < MAX_BUF_SIZE; i++) {
        	jobs[i] = (int) calloc(1, sizeof(int));
        	logs[i] = (char *) calloc(1, sizeof(char *));
    		}
	}


