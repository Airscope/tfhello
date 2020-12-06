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
        void add(CtxtInteger &sum, const CtxtInteger &a, const CtxtInteger &b);
        void sub(CtxtInteger &difference, const CtxtInteger &a, const CtxtInteger &b);
        void mul(CtxtInteger &product, const CtxtInteger &multiplicand, const CtxtInteger &multiplier);
        void div(CtxtInteger &quotient, CtxtInteger &remainder, const CtxtInteger &dividend, const CtxtInteger &divisor);

        void copy(CtxtInteger &dst, CtxtInteger &src);

    private:
        void addRange(LweSample *carry, LweSample *sum, const LweSample *a, const LweSample *b, int begin, int end);
        void initWithZeros(LweSample *result, int length);
        void copy(LweSample *dst, const LweSample *src, int length);

    private:
        const TFheGateBootstrappingCloudKeySet *bk_;
    };

} // namespace tfhello

#endif