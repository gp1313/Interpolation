#include <opencl_interpolation.h>

using namespace std;

int init_opencl()
{
    // Setup OpenCL platform and query details about it.
    cl_int err;
    cl_uint CLPlatformNum; 
    cl_platform_id CLPlatformIDs;
    err = clGetPlatformIDs(0, NULL, &CLPlatformNum);
    printf("Number of platforms detected : %d \n", CLPlatformNum);
    if(CLPlatformNum == 1)
    {
        err = clGetPlatformIDs(CLPlatformNum, &CLPlatformIDs, NULL);
        if(err == CL_SUCCESS)
        {
            printf("getPlatformID method was successfull \n");
        }
    }
    else 
    {
        printf("CLPlatfomrNum is not 1 \n");
        return -1;
    }
    
    cl_uint CLDeviceNum;
    cl_device_type CLDeviceType = CL_DEVICE_TYPE_GPU;
    cl_device_id CLDeviceIDs;
    err = clGetDeviceIDs(CLPlatformIDs, CLDeviceType, 0, NULL, &CLDeviceNum);
    if(CLDeviceNum == 1)
    {
        err = clGetDeviceIDs(CLPlatformIDs, CLDeviceType, CLDeviceNum, &CLDeviceIDs, NULL);
        if(err == CL_SUCCESS)
            printf("getDeviceId methos is successfull \nCLDeviceNum : %d \n", CLDeviceNum);
    }

    cl_context CLContext = clCreateContext(NULL, CLDeviceNum, &CLDeviceIDs, NULL, NULL, &err);
    if(err == CL_SUCCESS)
    {
        printf("context created successfully \n");
    }
    return 0;
}
