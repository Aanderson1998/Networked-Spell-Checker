#include "spellChecker.h"

	int remove_job(server *server) {
    	int socket = jobs[server->job_front];
    	//clear the array index
    	jobs[server->job_front] = 0;
    	//increment the index, and optionally loop back to 0 if we reach end of buffer
    	server->job_front = (++server->job_front) % MAX_BUF_SIZE;
    	//decrement the amount of clients in the buffer
    	--server->job_count;
    	return socket;
	}
