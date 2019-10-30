#include "spellChecker.h"

	int remove_job(server *server) {
    	int socket = jobs[server->job_front];
    	jobs[server->job_front] = 0;
    	server->job_front = (++server->job_front) % MAX_BUF_SIZE;
    	--server->job_count;
    	return socket;
	}
