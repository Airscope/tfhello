#include "Evaluator.h"

#include <tfhe/tfhe.h>
#include <cassert>

namespace tfhello
{
    /*
    void Evaluator::add(LweSample *carry, LweSample *result, const LweSample *a, const LweSample *b, int begin, int end)
    {
        LweSample *temp1 = new_gate_bootstrapping_ciphertext(bk_->params);
        LweSample *temp2 = new_gate_bootstrapping_ciphertext(bk_->params);
        // LweSample *carry = new_gate_bootstrapping_ciphertext(bk_->params);
        // bootsCONSTANT(carry, 0, bk_);
        for (int i = begin; i < end; ++i)
        {
            bootsXOR(temp1, &a[i], &b[i], bk_);
            bootsXOR(&result[i], temp1, carry, bk_);
            bootsAND(temp2, carry, temp1, bk_);
            bootsAND(temp1, &a[i], &b[i], bk_);
            bootsOR(carry, temp1, temp2, bk_);
        }
        // delete_gate_bootstrapping_ciphertext(carry);
        delete_gate_bootstrapping_ciphertext(temp1);
        delete_gate_bootstrapping_ciphertext(temp2);
    }
    */

    void Evaluator::add(CtxtInteger &result, const CtxtInteger &a, const CtxtInteger &b)
    {
        assert(a.size() == b.size());
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
    }
    void Evaluator::sub(CtxtInteger &result, const CtxtInteger &a, const CtxtInteger &b)
    {
        assert(a.size() == b.size());
        LweSample *temp1 = new_gate_bootstrapping_ciphertext(result.param());
        LweSample *temp2 = new_gate_bootstrapping_ciphertext(result.param());
        LweSample *carry = new_gate_bootstrapping_ciphertext(result.param());
        bootsCONSTANT(carry, 0, bk_);
        for (int i = 0; i < a.size(); ++i)
        {
            bootsXOR(temp1, b[i], carry, bk_);
            bootsXOR(result[i], temp1, a[i], bk_);
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

    void Evaluator::mul(CtxtInteger &result, const CtxtInteger &a, const CtxtInteger &b)
    {
        /*
        assert(a.size() == b.size());
        LweSample *product = new_gate_bootstrapping_ciphertext_array(2 * a.size(), a.param());
        LweSample *temp_product = new_gate_bootstrapping_ciphertext_array(2 * a.size(), a.param());

        for (int i = 0; i < 2 * a.size(); ++i)
        {
            bootsCONSTANT(&product[i], 0, bk_);
        }

        LweSample *carry = new_gate_bootstrapping_ciphertext(result.param());

        LweSample *temp1 = new_gate_bootstrapping_ciphertext(result.param());
        LweSample *temp2 = new_gate_bootstrapping_ciphertext(result.param());
        LweSample *temp3 = new_gate_bootstrapping_ciphertext(result.param());
        LweSample *temp4 = new_gate_bootstrapping_ciphertext(result.param());

        for (int i = 0; i < a.size(); ++i)
        {
            bootsCONSTANT(carry, 0, bk_);
            for (int j = 0; j < a.size(); ++j)
            {
                bootsAND(temp1, a[i], b[j], bk_);
                bootsXOR(temp2, &product[i + j], temp1, bk_);
                bootsCOPY(temp4, &product[i + j], bk_);
                bootsXOR(&product[i + j], temp2, carry, bk_);
                bootsAND(temp3, carry, temp2, bk_);
                bootsAND(temp2, temp1, temp4, bk_);
                bootsOR(carry, temp2, temp3, bk_);
            }

            for (int j = a.size(); j < 2 * a.size(); ++j)
            {
            }
        }

        delete_gate_bootstrapping_ciphertext_array(2 * a.size(), product);
        */
    }
    void Evaluator::div(CtxtInteger &result, const CtxtInteger &a, const CtxtInteger &b)
    {
    }
}; // namespace tfhello
