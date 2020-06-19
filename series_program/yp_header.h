 /**
 *   @file       :yamp_header.h           
 *   @manual     
 *   @brief      
 *   @reference  :!man 2 inotify_init    
 *   @functions  
 *
 *   @author     yamp
 *   @date       June 17, 2020
 */

#ifndef YP_HEADER_H
#define YP_HEADER_H

#include <stdio.h>                                                                                           
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/inotify.h>
#include <sys/wait.h>

#define OPEN  0
#define CLOSE 1

#endif
