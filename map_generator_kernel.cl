__kernel
void map_generator(__global float *pfMapArr, __global float *iInputLength, __global float *iOutputLength)
{
    int index = get_global_id(0);
    float fIndex = (float)index;
    pfMapArr[index] = iInputLength[0] * fIndex / iOutputLength[0];
}
