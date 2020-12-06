#include <iostream>
#include <tfhe/tfhe.h>
#include "src/Evaluator.h"
#include "src/Encryptor.h"
#include <HEAAN/HEAAN.h>

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

    int16_t ptxt2 = 1332, ptxt1 = 1444;

    tfhello::CtxtInteger ctxt1(params, bits), ctxt2(params, bits);
    tfhello::Encryptor encryptor(key);
    encryptor.encrypt(ctxt1, ptxt1, bits);
    encryptor.encrypt(ctxt2, ptxt2, bits);

    tfhello::Evaluator evaluator(&key->cloud);
    tfhello::CtxtInteger ctxt3(params, bits);
    evaluator.mul(ctxt3, ctxt1, ctxt2);

    int16_t ptxt3 = encryptor.decrypt(ctxt3, bits);
    cout << "actual result: " << ptxt3 << ", expected result: " << int16_t(ptxt1 * ptxt2) << endl;

    /*
    ZZ a;
    cin >> a;
    stringstream ss;
    string str;
    ss << a;
    ss >> str;
    cout << str << endl;
    */

    // clean up all pointers
    delete_gate_bootstrapping_secret_keyset(key);
    delete_gate_bootstrapping_parameters(params);

    return 0;
}