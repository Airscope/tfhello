#include <iostream>
#include <tfhe/tfhe.h>
#include "src/Evaluator.h"
#include "src/Encryptor.h"

using namespace std;

int main()
{
    //generate a keyset
    const int minimum_lambda = 110;
    const int bits = 16;
    TFheGateBootstrappingParameterSet *params = new_default_gate_bootstrapping_parameters(minimum_lambda);

    //generate a random key
    uint32_t seed[] = {314, 1592, 657};
    tfhe_random_generator_setSeed(seed, 3);
    TFheGateBootstrappingSecretKeySet *key = new_random_gate_bootstrapping_secret_keyset(params);

    int ptxt2 = -12345, ptxt1 = 67890;

    tfhello::CtxtInteger ctxt1(params), ctxt2(params);
    tfhello::Encryptor encryptor(key);
    encryptor.encrypt(ctxt1, ptxt1);
    encryptor.encrypt(ctxt2, ptxt2);

    tfhello::Evaluator evaluator(&key->cloud);
    tfhello::CtxtInteger ctxt3(params);
    evaluator.sub(ctxt3, ctxt1, ctxt2);

    int ptxt3 = encryptor.decrypt(ctxt3);
    cout << "actual result: " << ptxt3 << ", expected result: " << ptxt1 - ptxt2 << endl;

    //clean up all pointers
    delete_gate_bootstrapping_secret_keyset(key);
    delete_gate_bootstrapping_parameters(params);

    return 0;
}