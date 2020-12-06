#ifndef TFHELLO_ENCODER_H_
#define TFHELLO_ENCODER_H_

#include <tfhe/tfhe.h>
#include <vector>
namespace tfhello
{
    using std::vector;

    class Encoder
    {
    public:
        // little endian
        // most significant bit is right-most bit
        vector<int> encode(int64_t integer, size_t bits)
        {
            vector<int> ret(bits);
            for (int i = 0; i < bits; ++i)
            {
                ret[i] = (integer >> i) & 1;
            }
            return ret;
        }

        int64_t decode(const vector<int> &data, size_t bits)
        {
            int ret = 0;
            for (int i = 0; i < bits; ++i)
            {
                ret |= (data[i] << i);
            }
            return ret;
        }

    private:
    };

} // namespace tfhello

#endif