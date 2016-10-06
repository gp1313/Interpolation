#ifndef _OPENCL_INTER_H_
#define _OPENCL_INTER_H_
#include "CL/cl.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int init_opencl();
void run_opencl();
void close_opencl();

#endif
