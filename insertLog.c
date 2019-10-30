#include "spellChecker.h"


	//function to insert log
	void insertLog(server *server, char *word, int correct) {
	//variable to hold log input string
    	char logInput[WORD_SIZE];
    	jobs[server->job_front] = (int) calloc(1, sizeof(int));
	//getting log input
    	size_t length = strlen(word);
    	word[length - 1] = '\0';
	//figuring out if word was correct or not, then writing saving it to put in log input
    	char *answer;
    	if(correct==1){
	answer="OK";
	}else{
	answer="MISSPELLED";
	//using strcpy and strcat to write total log input which is word is OK/MISSPELLED depending on answer
    	strcpy(logInput, word);
    	strcat(logInput, " is ");
    	strcat(logInput, answer);
	//inserting log in to queue and updating slots
    	strcpy(logs[server->log_rear], logInput);
    	server->log_rear = (++server->log_rear) % MAX_BUF_SIZE;
    	++server->log_count;
	}
