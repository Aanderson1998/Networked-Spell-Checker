#include "spellChecker.h"

	void initServer(server *server){
	//allocating space in queues
	for(int i = 0; i < MAX_BUF_SIZE; i++) {
		jobs[i] = (int) calloc(1, sizeof(int));
		logs[i] = (char *) calloc(1, sizeof(char *));
		}
	//setting initial ptrs to 0 to signify empty queues
	server->job_count = 0;
	server->log_count = 0;
	server->job_front = 0;
	server->job_rear = 0;
	server->log_front = 0;
	server->log_rear = 0;
	//create mutex and making sure created properly or else printing error message
	if (pthread_mutex_init(&server->job_mutex, NULL) != 0) {
		perror("Problem initializing job mutex");
		}
	if (pthread_mutex_init(&server->log_mutex, NULL) != 0) {
		perror("Problem initializing log mutex");
		}
	//creating condition variableS and making sure they were created properly or else printing error message
	if (pthread_cond_init(&server->job_not_empty, NULL) != 0) {
		perror("Problem initializing job_not_empty condition variable");
		}
	if (pthread_cond_init(&server->job_not_full, NULL) != 0) {
		perror("Problem initializing job_not_full condition variable");
		}
	if (pthread_cond_init(&server->log_not_empty, NULL) != 0) {
		perror("Problem initializing log_not_empty condition variable");
		}
	if (pthread_cond_init(&server->log_not_full, NULL) != 0) {
		perror("Problem initializing  log_not_full condition variable");
		}
	}


