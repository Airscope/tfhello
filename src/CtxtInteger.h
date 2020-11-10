#ifndef TFHELLO_CTXTINTEGER_H_
#define TFHELLO_CTXTINTEGER_H_

#include <tfhe/tfhe.h>

namespace tfhello
{

    class CtxtInteger
    {
    private:
        LweSample *ciphertexts_;
        size_t size_;
        const TFheGateBootstrappingParameterSet *param_;

    public:
        CtxtInteger(const TFheGateBootstrappingParameterSet *param, size_t size = 32) : ciphertexts_(new_gate_bootstrapping_ciphertext_array(size, param)), size_(size), param_(param) {}

        ~CtxtInteger() { delete_gate_bootstrapping_ciphertext_array(size_, ciphertexts_); }

        //const LweSample *at(size_t index) const { return &ciphertexts_[index]; }
        //LweSample *at(size_t index) { return &ciphertexts_[index]; }

        const LweSample *operator[](size_t index) const { return &ciphertexts_[index]; }
        LweSample *operator[](size_t index) { return &ciphertexts_[index]; }
        const TFheGateBootstrappingParameterSet *param() const { return this->param_; }

        // No implicit copy allowed
        CtxtInteger(const CtxtInteger &) = delete;
        CtxtInteger &operator=(const CtxtInteger &) = delete;

        // Explicit copy
        void copyTo(CtxtInteger &dst);

        size_t size() const { return this->size_; }
    };
} // namespace tfhello

#endif