#include "yp_func.h"

#define NUM_PROG 3
#define FILE0 0
#define PROG1 1

int yp_parent_ps() {
	return 0;
}

int yp_child_ps() {
	char *dir_name = "./programs/";
	FILE *fp[NUM_PROG] = { NULL, };

    //int ret = execl("/usr/bin/find", "find", ".", "-name", "*c", NULL);
	//FILE *fp = popen("ls -l | sed -n 5p | awk '{print $9}'", "r");
	//fp[0] = popen(" ls -l ./programs | sed -n \"2, \\$p\" ", "r");
	fp[0] = popen("ls -l ./programs | awk \'$1 ~ /??x+/ {print $9}\'", "r");

	char **progs = fp_exist_progs(fp[0]);
	printf("Programs in \"%s\"=============\n", dir_name);
	for (int i = 0; progs[i] != 0; ++i) {
		printf("%s\n", progs[i]);
	}
	if(pclose(fp[0]) == -1) goto err;
	printf("======================================\n");
	
	#if 1
	for (int i = 0; progs[i] != 0; ++i) {
		char excute[100];
		strcpy(excute, dir_name);
		strcat(excute, progs[i]);
		
		fp[i + 1] = popen(excute, "r");
		printf("excute file: %s\n", excute);
		if(pclose(fp[i + 1]) == -1) goto err;
	}
	#endif

	// How can I free about double ptr...

	free(progs);
	return 0;

err:
	printf("popen() or pclose() error!\n");
	return 1;
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
