#include <iostream>
#include <interpolation.h>

using namespace std;
using namespace inter;
#define DebugDisplay 1
#define USE_CPU 0
int main()
{
    int iOutLen = 19;
    int iInLen = 10;
    int iaArr[iInLen];
    int *piOutputArr = NULL;
    iaArr[0] = 12;
    iaArr[1] = 112;
    iaArr[2] = 132;
    iaArr[3] = 1278;
    iaArr[4] = 1256;
    iaArr[5] = 123;
    iaArr[6] = 1321;
    iaArr[7] = 142;
    iaArr[8] = 15232;
    iaArr[9] = 1202;
    
    Interpolation oReferInter(iaArr, iInLen, iOutLen);
    if (USE_CPU)
    {
        oReferInter.pfInterMap = oReferInter.generateMap(iInLen, iOutLen);
    }else
    {
        oReferInter.pfInterMap = cl_map_generation(iInLen, iOutLen);
    }
    oReferInter.setMethod(COEF_TYPE);
    piOutputArr = oReferInter.RunInterpolation();

#if DebugDisplay
    for(int i =0; i<iInLen; i++)
    {
        cout << iaArr[i] << " ";
    }
    cout << endl;
        
    for(int i =0; i<iOutLen; i++)
    {
        cout << oReferInter.pfInterMap[i] << " ";
    }
    cout << endl;
    for(int i =0; i<iOutLen; i++)
    {
        cout << piOutputArr[i] << " ";
    }
    cout << endl;
#endif
    return 0;
}
