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

        void encrypt(CtxtInteger &ciphertext, int message, int bits = 32)
        {
            vector<int> data = encoder_.encode(message, bits);
            for (int i = 0; i < bits; ++i)
            {
                bootsSymEncrypt(ciphertext[i], data[i], sk_);
            }
        }

        int decrypt(const CtxtInteger &ciphertext, int bits = 32)
        {
            vector<int> data(bits);
            for (int i = 0; i < bits; ++i)
            {
                data[i] = bootsSymDecrypt(ciphertext[i], sk_);
            }
            return encoder_.decode(data, bits);
        }

    private:
        const TFheGateBootstrappingSecretKeySet *sk_;
        Encoder encoder_;
    };

} // namespace tfhello

#endif