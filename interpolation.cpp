#include <interpolation.h>

using namespace inter;
using namespace std;
Interpolation::Interpolation(int *piArr,int iInLength, int iOutLength)
{
    iInLen = iInLength;
    iOutLen = iOutLength;
    piInputArr = new int[iInLen];
    piOutputArr = new int[iOutLen];
    pfInterMap = new float[iOutLen];
    for(int i=0; i<iInLen; i++)
        piInputArr[i] = piArr[i];

    eMethodUsed = DEFAULT_TYPE;
}

Interpolation::~Interpolation()
{
    free(piInputArr);
    free(piOutputArr);
}

int *Interpolation::RunInterpolation()
{
    pfInterMap = generateMap(iInLen, iOutLen);
    if (eMethodUsed == DEFAULT_TYPE)
    {
        float a = 0.0, b = 0.0;
        int index = 0;
        for(int i=0; i<iOutLen; i++)
        {
            index = int(pfInterMap[i]);
            a = pfInterMap[i] - float(index);
            b = 1 - a;
            piOutputArr[i] = ( b * float(piInputArr[index]) )+ ( a * float(piInputArr[index+1]));
        }
    }
    return piOutputArr;
}

float *Interpolation::generateMap(int iInLen, int iOutLen)
{
    for(int i = 0; i<iOutLen; i++)
    {
        pfInterMap[i] = float(iInLen-1) * float(i) / float(iOutLen-1);
    }
    return pfInterMap;
}
