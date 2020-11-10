#ifndef TFHELLO_EVALUATOR_H_
#define TFHELLO_EVALUATOR_H_

#include <tfhe/tfhe.h>
#include "CtxtInteger.h"

namespace tfhello
{
    class Evaluator
    {
    public:
        Evaluator(const TFheGateBootstrappingCloudKeySet *bk) : bk_(bk) {}
        void add(CtxtInteger &result, const CtxtInteger &a, const CtxtInteger &b);
        void sub(CtxtInteger &result, const CtxtInteger &a, const CtxtInteger &b);
        void mul(CtxtInteger &result, const CtxtInteger &a, const CtxtInteger &b);
        void div(CtxtInteger &result, const CtxtInteger &a, const CtxtInteger &b);

    private:
        void initWithZeros(LweSample *result, int length);
        void copy(LweSample *dst, const LweSample *src, int length);

    private:
        const TFheGateBootstrappingCloudKeySet *bk_;
    };

} // namespace tfhello

#endif