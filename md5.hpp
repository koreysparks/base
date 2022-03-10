
#pragma once

#include <string>

namespace pp{

    using namespace std;

    class CMD5 
	{
    public:
        CMD5();
        CMD5(const string &str);

	public:
        void update(const string &str);
        const unsigned char* digest();
        string toString();
        void reset();

    private:
        void update(const unsigned char *input, size_t length);
        void final();
        void transform(const unsigned char block[64]);
        void encode(const unsigned int *input, unsigned char *output, size_t length);
        void decode(const unsigned char *input, unsigned int *output, size_t length);
        string bytesToHexString(const unsigned char *input, size_t length);
		// 去除换行及空格
		string trim(const string& str);

	private:
        CMD5(const CMD5&);
        CMD5& operator=(const CMD5&);

    private:
        unsigned int m_state[4];	/* state (ABCD) */
        unsigned int m_count[2];	/* number of bits, modulo 2^64 (low-order word first) */
        unsigned char m_buffer[64];	/* input buffer */
        unsigned char m_digest[16];	/* message digest */
        bool m_finished;		/* calculate finished ? */

        static const unsigned char PADDING[64];	/* padding for calculate */
        static const char HEX[16];
        static const size_t BUFFER_SIZE = 1024;
    };
}
