#include <cstdio>
#include <cstring>

static const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encodeblock(unsigned char in[3], unsigned char out[4], int len) {
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

void encode(FILE *infile, FILE *outfile) {
    unsigned char in[3], out[4];
    int i, len;

    while (!feof(infile)) {
        len = 0;
        for (i = 0; i < 3; i++) {
            in[i] = (unsigned char) getc(infile);
            if (!feof(infile)) {
                len++;
            } else {
                in[i] = 0;
            }
        }
        if (len) {
            encodeblock(in, out, len);
            for (i = 0; i < 4; i++) {
                putc(out[i], outfile);
            }
        }
    }
}

unsigned char decode_char2code(unsigned char c)
{
    if (c >= '0' && c <= '9') return c-'0'+52;
    if (c >= 'a' && c <= 'z') return c-'a'+26;
    if (c >= 'A' && c <= 'Z') return c-'A';
    if (c == '+') return 62;
    if (c == '/') return 63;
    return 0; // '='
}

int decode(unsigned char in[], unsigned char out[])
{
    int t = 0;
    int len = strlen(in);
    while (in[len - 1] == '=') len--;
    for (int i = 0; i < len; i++)
        in[i] = decode_char2code(in[i]);

    for (int i = 0; i < len; i++)
    {
        out[t++] = ((in[i] << 2) | (in[i + 1] >> 4));
        if (i + 2 < len)
            out[t++] = ((in[i + 1] << 4) | (in[i + 2] >> 2));
        if (i + 3 < len)
            out[t++] = ((in[i + 2] << 6) | in[i + 3]);
    }
    return t; // 解码后长度
}

