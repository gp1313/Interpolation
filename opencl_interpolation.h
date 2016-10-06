#ifndef _OPENCL_INTER_H_
#define _OPENCL_INTER_H_
#include "CL/cl.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

float *cl_map_generation(int in, int out);
void run_opencl();
void close_opencl();

#endif
