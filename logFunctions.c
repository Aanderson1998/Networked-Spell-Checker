#include "spellChecker.h"


	//function to insert log
	void insertLog(server *server, char *word, int correct) {
	//variable to hold log input string
	char logInput[WORD_SIZE];
	//clearing value out of front index in job queue
	jobs[server->job_front] = (int) calloc(1, sizeof(int));
	//variable to hold length of word
	size_t length = strlen(word);
	//making last index in word the termination charater
	word[length - 1] = '\0';
	//figuring out if word was correct or  not then saving response in answer variable
	char *answer;
	if(correct==1){
		answer="OK";
	}else{
		answer="MISSPELLED";
	}
	//using strcpy and strcat to write total log input which is "word is OK/MISSPELLED" depending on answer
	strcpy(logInput, word);
	strcat(logInput, " is ");
	strcat(logInput, answer);
	//inserting log in to queue at rear
	strcpy(logs[server->log_rear], logInput);
	//incrementing log_rear
	server->log_rear = (++server->log_rear) % MAX_BUF_SIZE;
	//incrementing log_count
	++server->log_count;
	}

	//function to remove log
	char *removeLog(server *server) {
        //get the log input at front of log queue
        char *logResult = logs[server->log_front];
	//emptying front slot of queue
        logs[server->log_front] = (char *) calloc(1, sizeof(char *));
        //increment log_front
        server->log_front = (++server->log_front) % MAX_BUF_SIZE;
        //decrement log_count
        --server->log_count;
	//return logResults
        return logResult;
        }
