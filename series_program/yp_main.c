/**                                                
*   @file       : yp_main.c
*   @manual    	: observe the status about dirs from argv 
*   @brief      
*   @reference  :
*   @functions  
*
*   @author     yamp
*   @date       June 17, 2020
*/

#include "yp_func.h"

int main(int argc, char **argv) {
	printf("argc: %d\n", argc);
	(void)argv;
#if 0                                                                  
    int fd = inotify_init();
    int err_num = 0;

    if (fd == -1) { 
        err_num = 1;
        goto err;
    }

    char **dir_name;
#endif

	if(yp_pid()) {
		goto err;
	};

    return 0;

err:
	printf("error\n");
   // if (fd >= 0) closed(fd);

}
