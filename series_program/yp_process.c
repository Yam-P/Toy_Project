#include "yp_func.h"

int yp_parent_ps() {
	return 0;
}

int yp_child_ps() {
    //int ret = execl("/usr/bin/find", "find", ".", "-name", "*c", NULL);
	//FILE *fp = popen("ls -l | sed -n 5p | awk '{print $9}'", "r");
	FILE *fp = popen("./sleep", "r");
	if (fp == NULL) {
		printf("popen() fiail\n");
		return -1;
	}
	
	char line[1024];
	while (fgets(line, 1024, fp)) {}
		
	pclose(fp);

	printf("%s", line);

	return 0;
}

int yp_pid() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child pid: %d\n", getpid());
    	if(yp_child_ps()) {
			printf("child_ps() fail\n");
		}
    }
    else if (pid > 0) {
        printf("Parent pid: %d\n", getpid());
    	if(yp_parent_ps()) {
			printf("parent_ps() fail\n");
		}
		int exit_status;
		pid = wait(&exit_status);
		if (WIFEXITED(exit_status)) {
			//printf("child %d returns %d\n", pid, WEXITSTATUS(exit_status));
		}
		else {
			printf("child %d is not exited\n", pid);
		}
    }


    return 0;
}   
