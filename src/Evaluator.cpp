#include "Evaluator.h"

#include <tfhe/tfhe.h>
#include <cassert>

namespace tfhello
{
    void Evaluator::addRange(LweSample *sum, LweSample *carry, const LweSample *a, const LweSample *b, int begin, int end)
    {
        LweSample *temp1 = new_gate_bootstrapping_ciphertext(bk_->params);
        LweSample *temp2 = new_gate_bootstrapping_ciphertext(bk_->params);
        bootsCONSTANT(carry, 0, bk_);
        for (int i = begin; i < end; ++i)
        {
            bootsXOR(temp1, &a[i], &b[i], bk_);
            bootsXOR(&sum[i], temp1, carry, bk_);
            bootsAND(temp2, carry, temp1, bk_);
            bootsAND(temp1, &a[i], &b[i], bk_);
            bootsOR(carry, temp1, temp2, bk_);
        }
        delete_gate_bootstrapping_ciphertext(temp1);
        delete_gate_bootstrapping_ciphertext(temp2);
    }

    void Evaluator::add(CtxtInteger &sum, const CtxtInteger &a, const CtxtInteger &b)
    {
        assert(a.size() == b.size());
        assert(sum.size() == a.size());
        LweSample *carry = new_gate_bootstrapping_ciphertext(sum.param());
        addRange(sum[0], carry, a[0], b[0], 0, a.size());
        delete_gate_bootstrapping_ciphertext(carry);

        /*
        LweSample *temp1 = new_gate_bootstrapping_ciphertext(result.param());
        LweSample *temp2 = new_gate_bootstrapping_ciphertext(result.param());
        LweSample *carry = new_gate_bootstrapping_ciphertext(result.param());
        bootsCONSTANT(carry, 0, bk_);
        for (int i = 0; i < a.size(); ++i)
        {
            bootsXOR(temp1, a[i], b[i], bk_);
            bootsXOR(result[i], temp1, carry, bk_);
            bootsAND(temp2, carry, temp1, bk_);
            bootsAND(temp1, a[i], b[i], bk_);
            bootsOR(carry, temp1, temp2, bk_);
        }
        delete_gate_bootstrapping_ciphertext(carry);
        delete_gate_bootstrapping_ciphertext(temp1);
        delete_gate_bootstrapping_ciphertext(temp2);
        */
    }
    void Evaluator::sub(CtxtInteger &difference, const CtxtInteger &a, const CtxtInteger &b)
    {
        assert(a.size() == b.size());
        assert(a.size() == difference.size());
        LweSample *temp1 = new_gate_bootstrapping_ciphertext(difference.param());
        LweSample *temp2 = new_gate_bootstrapping_ciphertext(difference.param());
        LweSample *carry = new_gate_bootstrapping_ciphertext(difference.param());
        bootsCONSTANT(carry, 0, bk_);
        for (int i = 0; i < a.size(); ++i)
        {
            bootsXOR(temp1, b[i], carry, bk_);
            bootsXOR(difference[i], temp1, a[i], bk_);
            bootsANDNY(temp2, a[i], temp1, bk_);
            bootsAND(temp1, b[i], carry, bk_);
            bootsOR(carry, temp1, temp2, bk_);
        }
        delete_gate_bootstrapping_ciphertext(carry);
        delete_gate_bootstrapping_ciphertext(temp1);
        delete_gate_bootstrapping_ciphertext(temp2);
    }

    void Evaluator::initWithZeros(LweSample *result, int length)
    {
        for (int i = 0; i < length; ++i)
        {
            bootsCONSTANT(&result[i], 0, bk_);
        }
    }

    void Evaluator::copy(LweSample *dst, const LweSample *src, int length)
    {
        for (int i = 0; i < length; ++i)
        {
            bootsCOPY(&dst[i], &src[i], bk_);
        }
    }

    /**
     * https://www.cnblogs.com/lfri/p/10046360.html
     **/
    void Evaluator::mul(CtxtInteger &product, const CtxtInteger &multiplicand, const CtxtInteger &multiplier)
    {
        assert(multiplicand.size() == multiplier.size());
        assert(product.size() == multiplicand.size());
        const int length = multiplicand.size();
        for (int i = 0; i < length; ++i)
        {
            bootsCONSTANT(product[i], 0, bk_);
        }

        LweSample *carry = new_gate_bootstrapping_ciphertext(product.param());
        LweSample *a = new_gate_bootstrapping_ciphertext(product.param());
        LweSample *a_xor_b = new_gate_bootstrapping_ciphertext(product.param());
        LweSample *a_and_b = new_gate_bootstrapping_ciphertext(product.param());
        LweSample *a_xor_b_and_c = new_gate_bootstrapping_ciphertext(product.param());

        for (int i = 0; i < length; ++i)
        {
            bootsCONSTANT(carry, 0, bk_);
            for (int j = 0; j < length - i; ++j)
            {
                /**
                 * NOTE: b represents product[i+j]
                 * a = multiplicand[j] & multiplier[i]
                 * b =  a ^ b ^ carry
                 * carry = (a & b) | ((a ^ b) & carry)
                */
                bootsAND(a, multiplier[i], multiplicand[j], bk_);
                bootsAND(a_and_b, a, product[i + j], bk_);
                bootsXOR(a_xor_b, a, product[i + j], bk_);
                bootsAND(a_xor_b_and_c, a_xor_b, carry, bk_);
                bootsXOR(product[i + j], a_xor_b, carry, bk_);
                bootsOR(carry, a_and_b, a_xor_b_and_c, bk_);
            }
        }
        delete_gate_bootstrapping_ciphertext(carry);
        delete_gate_bootstrapping_ciphertext(a);
        delete_gate_bootstrapping_ciphertext(a_xor_b);
        delete_gate_bootstrapping_ciphertext(a_and_b);
        delete_gate_bootstrapping_ciphertext(a_xor_b_and_c);
    }

    /**
     * https://www.cnblogs.com/lfri/p/10047038.html
     */
    void Evaluator::div(CtxtInteger &quotient, CtxtInteger &remainder, const CtxtInteger &dividend, const CtxtInteger &divisor)
    {
    }
}; // namespace tfhello
