/*
 * Features.cpp
 *
 *  Created on: 30 сент. 2016 г.
 *      Author: radiolok
 */

#include "Features.h"

sigset_t alarm_sig;

bool delay = true;

void DelayOff(void)
{
	delay = false;
}

bool IsDelay(void)
{
	return delay;
}

void WaitRelay(int relay){
	if (IsDelay())
	{
		if (ONE_RELAY_DELAY){
			usleep(relay * ONE_RELAY_DELAY);
		}
	}

}

int PrepareClock(unsigned int freq){
	int status = 0;

	unsigned int period = 1000000/freq;
	struct itimerval value;

	/* Block SIGALRM in this thread */
	sigemptyset (&(alarm_sig));
	sigaddset (&(alarm_sig), SIGALRM);
	pthread_sigmask (SIG_BLOCK, &(alarm_sig), NULL);

	/* Set the timer to go off after the first period and then
	   repetitively */
	value.it_value.tv_sec = period/1000000;
	value.it_value.tv_usec = period%1000000;
	value.it_interval.tv_sec = period/1000000;
	value.it_interval.tv_usec = period%1000000;
	status = setitimer (ITIMER_REAL, &value, NULL);
	if (status != 0)
		perror ("Failed to set timer");

	return status;
}

void WaitClock(void){
	if (IsDelay())
	{
	int sig;

		/* Wait for the next SIGALRM */
	sigwait (&(alarm_sig), &sig);
	}

}
