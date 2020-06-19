#include "yp_func.h"

#define FILE_SIZE    1024                                                          
#define NUM_LINE     100 

int fp_close_all(FILE **fp, int num_prog) {
    int err_file_num;                                                              
    for (int i = 0; i < num_prog; ++i) {
        if (fp[i] == NULL) {
            err_file_num = i;
            goto err;
        }
        if (pclose(fp[i]) == -1) printf("pclose() fail of fp[%d]\n", i);
    }
        
    return 0;

err: 
    printf("%d file close error\n", err_file_num);
    return 1;
}

char **fp_exist_progs(FILE *fp) {
	char lines[FILE_SIZE] = "";
	char tmp_line[NUM_LINE];
	int num_line = 0;

	// 공백이 있을 때까지 각 line을 받아옴
	while (fgets(tmp_line, sizeof(tmp_line), fp)) {
	    strcat(lines, tmp_line);
		++num_line;
	}

	char **ret = (char **)malloc(sizeof(char *) * (num_line + 1));

	char split_char = '\n';
	char *line = strtok(lines, &split_char);
	
	for (int i = 0; line != NULL; ++i) {
		int tmp_str_size = strlen(line);

		ret[i] = (char *)malloc(sizeof(char) * tmp_str_size);
		strcpy(ret[i], line);

	    line = strtok(NULL, &split_char);
	}

	ret[num_line] = 0;
	return ret;
}
