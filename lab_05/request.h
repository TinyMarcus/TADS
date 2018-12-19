#ifndef REQUEST_H
#define REQUEST_H

struct request
{
	float arrival_time;
	float process_time;
	float down_time;
	struct request *next;
};

#endif
