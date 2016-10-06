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
    pfInterMap = generateMap(iInLen, iOutLen);
}

Interpolation::~Interpolation()
{
    free(piInputArr);
    free(piOutputArr);
}

int *Interpolation::RunInterpolation()
{
    if (eMethodUsed == DEFAULT_TYPE)
        cout << "Using default interpolation \n";
    else if(eMethodUsed == COEF_TYPE)
        cout << "Using fixed coeff type interpolation \n";
    float a = 0.0, b = 0.0;
    int index = 0;
    for(int i=0; i<iOutLen; i++)
    {
        if (eMethodUsed == DEFAULT_TYPE)
        {
            index = int(pfInterMap[i]);
            a = pfInterMap[i] - float(index);
            b = 1 - a;
        }
        else if(eMethodUsed == COEF_TYPE)
        {
            index = aiInterIndex[i];
            a = Coeff[aiInterCoeff[i]][1];
            b = Coeff[aiInterCoeff[i]][0];            
        }
        else
        { 
            return NULL;
        }
        piOutputArr[i] = ( b * float(piInputArr[index]) )+ ( a * float(piInputArr[index+1]));
    }
    return piOutputArr;
}

float *Interpolation::generateMap(int iInLen, int iOutLen)
{
    int iRetCLInit = init_opencl();
    for(int i = 0; i<iOutLen; i++)
    {
        pfInterMap[i] = float(iInLen-1) * float(i) / float(iOutLen-1);
    }
    return pfInterMap;
}

void Interpolation::setMethod(INTER_METHOD SelectedMethod)
{
    eMethodUsed = SelectedMethod;
    if(eMethodUsed == COEF_TYPE)
    {
        getCoeffMatrix();
        aiInterIndex = new int[iOutLen];
        aiInterCoeff = new int[iOutLen];
        ConvertMapToFixedArr();        
    }
}

void Interpolation::getCoeffMatrix()
{
    for(int i=0; i<32; i++)
    {
        Coeff[i][1] = (float(i)/32.0);
        Coeff[i][0] = 1.0 - Coeff[i][1];
    }
}

void Interpolation::ConvertMapToFixedArr()
{
    float fDec = 0.0;
    for (int i=0; i<iOutLen; i++)
    {
        aiInterIndex[i] = int(pfInterMap[i]);
        fDec = pfInterMap[i] - float(aiInterIndex[i]);
        aiInterCoeff[i] = int(fDec * 32);
    }
}
