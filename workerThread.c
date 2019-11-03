#include "spellChecker.h"

	void *workerthread(void *serve) {
	server *server=serve;
    	int bytes;
    	char *word;
    	char *getWord = "word input> ";
	char *answer;
    	while(1) {
        	pthread_mutex_lock(&server->job_mutex);
        	while (server->job_front == server->job_front && server->job_count == 0) {
            		pthread_cond_wait(&server->job_not_empty, &server->job_mutex);
        	}
        	//get socket
        	int socket = remove_job(server);
        	//send signal
        	pthread_cond_signal(&server->job_not_full);
        	//unlock mutex
        	pthread_mutex_unlock(&server->job_mutex);
        	//spellCheck for client until they connect
        	while(1) {
            		send(socket, getWord, strlen(getWord), 0);
            		word = calloc(WORD_SIZE, 1);
            		//receive word
            		bytes= (int) recv(socket, word, WORD_SIZE, 0);
            		//if there was an error
            		if (bytes < 0) {
				char *error = "Error receiving message";
                		send(socket, error, strlen(error), 0);
                		continue;
            		}
            		if(strcmp(word, "..\n") == 0) {
			printf("client disconnected. Goodbye! Thank you for using spellChecker\n");
                	exit(0);
            		}
            		//search for word
            		int correct = lookup(word);
					if (correct==1){
						answer="OK\n";
					}else{
						answer="MISSPELLED\n";
					}
					//send client answer
            		send(socket, answer, strlen(answer), 0);
            		pthread_mutex_lock(&server->log_mutex);
            		//check if the buffer is full
            		while(server->log_rear == server->log_front && server->log_count == MAX_BUF_SIZE) {
                		pthread_cond_wait(&server->log_not_full, &server->log_mutex);
            		}
					//insert into log queue
            		insert_log(server, word, correct);
            		//signal log queue
            		pthread_cond_signal(&server->log_not_empty);
            		//unlock the mutex
            		pthread_mutex_unlock(&server->log_mutex);
        	}
        	close(socket);
    	}
    	return NULL;
	}


