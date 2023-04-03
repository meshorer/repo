
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

static char *decoding_table = NULL;

static size_t mod_table[] = {0, 2, 1};

void build_decoding_table()
{
    int i = 0;
    decoding_table = malloc(256);

    if (NULL == decoding_table)
    {
        exit(1);
    }

    for (i = 0; i < 64; i++)
    {
        decoding_table[(unsigned char)encoding_table[i]] = i;
    }
}

void base64_cleanup()
{
    free(decoding_table);
}

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length)
{
    size_t i = 0;
    int j = 0;
    uint32_t octet_a = 0;
    uint32_t octet_b = 0;
    uint32_t octet_c = 0;
    uint32_t triple = 0;
    char *encoded_data = NULL;
    *output_length = 4 * ((input_length + 2) / 3);   /* caluculate optimal output to allocate */

    encoded_data = malloc(*output_length);
    if (encoded_data == NULL)
    {
        return NULL;
    }

    for (i = 0, j = 0; i < input_length;)
    {

        octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < mod_table[input_length % 3]; i++)
    {
        encoded_data[*output_length - 1 - i] = '=';
    }

    return encoded_data;
}

unsigned char *base64_decode(const char *data,size_t input_length,size_t *output_length)
{
    size_t i = 0;
    int j = 0;
    unsigned char *decoded_data = NULL;
    if (decoding_table == NULL)
    {
        build_decoding_table();
    }

    if (input_length % 4 != 0)
    {
       return NULL;
    }

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=')
    {
        (*output_length)--;
    }
    if (data[input_length - 2] == '=')
    {
        (*output_length)--;
    }

    decoded_data = malloc(*output_length);

    if (decoded_data == NULL)
    {
        return NULL;
    }

    for (i = 0, j = 0; i < input_length;)
    {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

        if (j < *output_length)
        {
            decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        }
        if (j < *output_length)
        {
            decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        }
        if (j < *output_length)
        {
            decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
        }
    }

    return decoded_data;
}

int main()
{

    char *data = "Hello World!";
    size_t *input_size = strlen(data);
    char *decoded_data = NULL;
    size_t *decode_size = 0;
    char *encoded_data = base64_encode(data, input_size, &input_size);
    printf("Encoded Data is: %s \n", encoded_data);

    decode_size = strlen(encoded_data);
    decoded_data = base64_decode(encoded_data, decode_size, &decode_size);
    printf("Decoded Data is: %s \n", decoded_data);
    exit(0);
}
