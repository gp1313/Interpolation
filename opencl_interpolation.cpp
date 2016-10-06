#include <opencl_interpolation.h>

using namespace std;

void read_file(char **pcKernelSourceFile, int *iFileLength)
{
    FILE *pstmSourceFile = fopen("map_generator_kernel.cl", "r");
    if(!pstmSourceFile)
    {
        printf("cannot read kernel file \n");
        return;
    }
    fseek(pstmSourceFile, 0, SEEK_END);
    *iFileLength = ftell(pstmSourceFile);
    fseek(pstmSourceFile, 0, SEEK_SET);
    *pcKernelSourceFile = (char *)malloc(((*iFileLength) + 1));
    fread(*pcKernelSourceFile, 1, *iFileLength, pstmSourceFile);
    fclose(pstmSourceFile);
    int len = *iFileLength;
    (*pcKernelSourceFile)[len] = '\0';
}

float *cl_map_generation(int iInputLen, int iOutputLen)
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
        return NULL;
    }
    
    cl_uint CLDeviceNum;
    cl_device_type CLDeviceType = CL_DEVICE_TYPE_GPU;
    cl_device_id CLDeviceIDs;
    err = clGetDeviceIDs(CLPlatformIDs, CLDeviceType, 0, NULL, &CLDeviceNum);
    if(CLDeviceNum == 1)
    {
        err = clGetDeviceIDs(CLPlatformIDs, CLDeviceType, CLDeviceNum, &CLDeviceIDs, NULL);
        if(err == CL_SUCCESS)
            printf("getDeviceId method is successfull \nCLDeviceNum : %d \n", CLDeviceNum);
    }

    cl_context CLContext = clCreateContext(NULL, CLDeviceNum, &CLDeviceIDs, NULL, NULL, &err);
    if(err == CL_SUCCESS)
    {
        printf("Context created successfully \n");
    }

    // Read kernel source file for build process of program 
    char *pcKernelSourceFile;
    int iFileLength;
    read_file(&pcKernelSourceFile, &iFileLength);
    const size_t stringLen = iFileLength;
    printf("source file length : %d \n", iFileLength);
    cl_program CLProgram = clCreateProgramWithSource(CLContext, 1, (const char **)&pcKernelSourceFile, &stringLen, &err);
    if(err == CL_SUCCESS)
    {
        printf("Program create method was successful \n");
    }

    err = clBuildProgram(CLProgram, CLDeviceNum, &CLDeviceIDs, NULL, NULL, NULL);
    if(err == CL_SUCCESS)
    {
        printf("Program Build was successful \n");
    }
    else if (err == CL_INVALID_PROGRAM)
    {
        printf("Program is invalid \n");
    }
    else if (err == CL_INVALID_PROGRAM)
    {
        printf("Program is invalid \n");
    }
    else if (err == CL_INVALID_VALUE)
    {
        printf("Program is CL_INVALID_PROGRAM \n");
    }
    else if (err == CL_INVALID_DEVICE)
    {
        printf("Program is CL_INVALID_DEVICE \n");
    }
    else if (err == CL_INVALID_OPERATION)
    {
        printf("Program is CL_INVALID_OPERATION \n");
    }
    else if (err == CL_COMPILER_NOT_AVAILABLE)
    {
        printf("Program is CL_COMPILER_NOT_AVAILABLE \n");
    }
    else if (err == CL_BUILD_PROGRAM_FAILURE)
    {
        printf("Program is CL_BUILD_PROGRAM_FAILURE \n");
    }
    else
    {
        printf("Program build failed \n");
    }

    cl_command_queue CLCommandQueue = clCreateCommandQueue(CLContext, CLDeviceIDs, 0, &err);
    if( err == CL_SUCCESS)
    {
        printf("Command queue is created successfully \n");
    }

    cl_kernel CLKernel = clCreateKernel(CLProgram, "map_generator", &err);
    if(err == CL_SUCCESS)
    {
        printf("Kernel created successfully\n");
    }

    cl_mem CLBufferMapArr, CLInputLen, CLOutputLen;
    CLBufferMapArr = clCreateBuffer(CLContext, CL_MEM_WRITE_ONLY, sizeof(float)*iOutputLen, NULL, &err);
    CLInputLen = clCreateBuffer(CLContext, CL_MEM_READ_ONLY, sizeof(float), NULL, &err);
    CLOutputLen = clCreateBuffer(CLContext, CL_MEM_READ_ONLY, sizeof(float), NULL, &err);
    

        
    cl_event CLEvent;
    float fInputLen = iInputLen - 1;
    float fOutputLen = iOutputLen - 1;
    
    err = clEnqueueWriteBuffer(CLCommandQueue, CLInputLen, CL_TRUE, 0, sizeof(float), &fInputLen, 0, NULL, &CLEvent);
    clReleaseEvent(CLEvent);
    
    err = clEnqueueWriteBuffer(CLCommandQueue, CLOutputLen, CL_TRUE, 0, sizeof(float), &fOutputLen, 0, NULL, &CLEvent);
    clReleaseEvent(CLEvent);

    err = clSetKernelArg(CLKernel, 0, sizeof(cl_mem), &CLBufferMapArr);
    err = clSetKernelArg(CLKernel, 1, sizeof(cl_mem), &CLInputLen);
    err = clSetKernelArg(CLKernel, 2, sizeof(cl_mem), &CLOutputLen);
    
    if(err == CL_SUCCESS)
    {
        printf("Buffer allocated successfully\n");
    }

    // Run Kernel 
    size_t stWorkSize[1];
    stWorkSize[0] = iOutputLen;
    err = clEnqueueNDRangeKernel(CLCommandQueue, CLKernel, 1, NULL, stWorkSize, NULL, 0, NULL, &CLEvent);
        
    if(err == CL_SUCCESS)
    {
        cout << "kernel execution successfull \n";
    }
    clReleaseEvent(CLEvent);
    clFinish(CLCommandQueue);
    printf("Done \n");    
    float *fTemp = NULL;
    return fTemp;
}
