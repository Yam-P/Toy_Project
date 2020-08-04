#include "yp_func.h"

#define NUM_PROG 4
#define FILE0 0
#define PROG1 1

int yp_series_implement(void) {
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
	if(pclose(fp[0]) == -1) return -1;
	printf("======================================\n");
	
	#if 1
	for (int i = 0; progs[i] != 0; ++i) {
		char excute[100];
		strcpy(excute, dir_name);
		strcat(excute, progs[i]);
		
		fp[i + 1] = popen(excute, "r");
		printf("excute file: %s\n", excute);
		if(pclose(fp[i + 1]) == -1) return -1;
	}
	#endif

	// How can I free about double ptr...

	free(progs);
	return 0;
}

int yp_inotify(char *dir) {
	int fd = inotify_init();
	if (fd == -1) {
		printf("inotify_init() fail.\n");
		return -1;
	}

	int wd = inotify_add_watch(fd, dir, IN_CREATE | IN_DELETE);

	while (1) {
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		struct inotify_event *event = (struct inotify_event *) &buf[0];
		int read_ret = read(fd, buf, sizeof(buf)); 
		if (read_ret == -1) {
			printf("inotify_read() fail.\n");
			return -1;
		}
		else {
			printf("inotify_read() success!\n");
		}

		while (read_ret > 0) {
			if (event->mask & IN_CREATE || event->mask & IN_DELETE) {
				printf("event occured: %s\n", event->name);
				printf("Start programs!\n");
				if (yp_series_implement()) {
					printf("series_implement() fail.\n");
					return -1;
				}
			}

			uint32_t event_struct_len = sizeof(struct inotify_event) + event->len;
			event = (struct inotify_event *)(char *)event + event_struct_len;
			read_ret -= event_struct_len;
		}
	}

	close(wd);
	close(fd);
	return 0;
}

int yp_parent_ps() {
	return 0;
}

int yp_child_ps() {
	int err_code = 0;
	if (yp_inotify("./programs/")) {
		printf("inotify fail\n");
		err_code = 2;
		goto err;
	}
	
	return 0;

err:
	printf("err_code: %d\n", err_code);
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
