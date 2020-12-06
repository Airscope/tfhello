#ifndef TFHELLO_ENCRYPTOR_H_
#define TFHELLO_ENCRYPTOR_H_

#include <tfhe/tfhe.h>

#include "Encoder.h"
#include "CtxtInteger.h"

namespace tfhello
{
    class Encryptor
    {
    public:
        explicit Encryptor(const TFheGateBootstrappingSecretKeySet *sk) : sk_(sk) {}

        void encrypt(CtxtInteger &ciphertext, int64_t message, size_t bits)
        {
            vector<int> data = encoder_.encode(message, bits);
            for (int i = 0; i < bits; ++i)
            {
                bootsSymEncrypt(ciphertext[i], data[i], sk_);
            }
        }

        int64_t decrypt(const CtxtInteger &ciphertext, size_t bits)
        {
            vector<int> data(bits);
            for (int i = 0; i < bits; ++i)
            {
                data[i] = bootsSymDecrypt(ciphertext[i], sk_);
            }
            return encoder_.decode(data, bits);
        }

        /*
        void encrypt(CtxtInteger &ciphertext, int message)
        {
            encrypt(ciphertext, message, 32);
        }

        int decrypt(const CtxtInteger &ciphertext)
        {
            return decrypt(ciphertext, 32);
        }
        */

    private:
        const TFheGateBootstrappingSecretKeySet *sk_;
        Encoder encoder_;
    };

} // namespace tfhello

#endif