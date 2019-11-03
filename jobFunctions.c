#include "spellChecker.h"

	//function to insert job
	void insertJob(server *server, int socket) {
	//insert job at rear
	jobs[server->job_rear] = socket;
	//increment the job_rear
	server->job_rear = (++server->job_rear) % MAX_BUF_SIZE;
	//increment the job_count
	++server->job_count;
	}


	//function to remove job
	int removeJob(server *server) {
	//get job from front of queue
	int socket = jobs[server->job_front];
	//clear the index at the front of queue
	jobs[server->job_front] = 0;
	//increment job_front
	server->job_front = (++server->job_front) % MAX_BUF_SIZE;
	//decrement job count
	--server->job_count;
	//return job
	return socket;
	}
