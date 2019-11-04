#include "spellChecker.h"

	void *workerThread(void *serve) {
	server *server=serve;
	//integer variable to hold bytes of the received word from client
	int bytes;
	//char * variable to hold word value
	char *word;
	//char * that prompts client to input word
	char *getWord = "word input> ";
	//char * variable to hold the answer (if word is spelled correctly or not)
	char *answer;
	while(1) {
		//lock job mutex
		pthread_mutex_lock(&server->job_mutex);
		//check if job queue is empty
		while (server->job_front == server->job_front && server->job_count == 0) {
			//if empty do a wait on job_not_empty condition variable
			pthread_cond_wait(&server->job_not_empty, &server->job_mutex);
		}
		//when job queue is not empty get socket(job) at front of job queue
		int socket = removeJob(server);
		//signal job_not_full condition variable
		pthread_cond_signal(&server->job_not_full);
		//unlock mutex
		pthread_mutex_unlock(&server->job_mutex);
		//spellCheck for client until they disconnect
		while(1) {
			send(socket, getWord, strlen(getWord), 0);
			word = calloc(WORD_SIZE, 1);
			//receive word
			bytes= (int) recv(socket, word, WORD_SIZE, 0);
			//if there was an error in receiving word send error message
			if (bytes < 0){
				char *error = "Error receiving message";
				send(socket, error, strlen(error), 0);
				continue;
			}
			//if escape button was pressed send goodbye message and print client disconnected
			if(word[0] == 27) {
                		send(socket, "Goodbye! Thank you for using the spell Checker.\n", strlen("Goodbye! Thankyou for using the spell checker.\n"), 0);
				printf("client disconnected.\n");
                		break;
			}
			//search for word
			int correct = findWord(word);
			if (correct==1){
				answer="OK\n";
			}else{
				answer="MISSPELLED\n";
				}
			//send client answer
			char *str="word is ";
			strcat(str,answer);
			send(socket, str, strlen(str), 0);
			pthread_mutex_lock(&server->log_mutex);
			//check if log queue is full
			while(server->log_rear == server->log_front && server->log_count == MAX_BUF_SIZE) {
				//if it is do a wait on log_not_full condition variable
				pthread_cond_wait(&server->log_not_full, &server->log_mutex);
				}
			//when log is not full, insert into log queue
			insertLog(server, word, correct);
			//signal log_not_empty condition variable
			pthread_cond_signal(&server->log_not_empty);
			//unlock the mutex
			pthread_mutex_unlock(&server->log_mutex);
		}
		//if client disconnected close socket
		close(socket);
	}
	return NULL;
	}


