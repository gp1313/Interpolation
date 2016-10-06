#ifndef _INTER_H_
#define _INTER_H_

#include <iostream>
#include <stdlib.h>

#include <opencl_interpolation.h>
enum INTER_METHOD
    {
        DEFAULT_TYPE = 0,
        COEF_TYPE,
    };

namespace inter
{
    
    class Interpolation
    {
        public:
            Interpolation(int *InputArr, int InLen, int OutLen);
            int *RunInterpolation();
            void setMethod(INTER_METHOD);
            ~Interpolation();
//        private:
            int iInLen,iOutLen;
            int *piInputArr, *piOutputArr;

            float *pfInterMap;
            float *generateMap(int iInLen, int iOutLen);            
            
            INTER_METHOD eMethodUsed;
            
            float Coeff[32][2];
            int *aiInterIndex, *aiInterCoeff;
            void getCoeffMatrix();
            void ConvertMapToFixedArr();            
    };
};
#endif
