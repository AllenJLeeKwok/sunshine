#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Header file for AS3 interop APIs
//this is linked in by the compiler (when using flaccon)
#include "AS3.h"

//Base64 encode & decode
void encode(char *src, int src_len, char *dst)
{
        int i = 0, j = 0;
        char base64_map[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 
        for (; i < src_len - src_len % 3; i += 3) {
                dst[j++] = base64_map[(src[i] >> 2) & 0x3F];
                dst[j++] = base64_map[((src[i] << 4) & 0x30) + ((src[i + 1] >> 4) & 0xF)];
                dst[j++] = base64_map[((src[i + 1] << 2) & 0x3C) + ((src[i + 2] >> 6) & 0x3)];
                dst[j++] = base64_map[src[i + 2] & 0x3F];
        }
 
        if (src_len % 3 == 1) {
                 dst[j++] = base64_map[(src[i] >> 2) & 0x3F];
                 dst[j++] = base64_map[(src[i] << 4) & 0x30];
                 dst[j++] = '=';
                 dst[j++] = '=';
        }
        else if (src_len % 3 == 2) {
                dst[j++] = base64_map[(src[i] >> 2) & 0x3F];
                dst[j++] = base64_map[((src[i] << 4) & 0x30) + ((src[i + 1] >> 4) & 0xF)];
                dst[j++] = base64_map[(src[i + 1] << 2) & 0x3C];
                dst[j++] = '=';
        }
 
        dst[j] = '\0';
}

void decode(char *src, int src_len, char *dst)
{
        int i = 0, j = 0;
        char base64_decode_map[256] = 
		{
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 62, 255, 255, 255, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255,
             255, 0, 255, 255, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255, 255, 26, 27, 28,
             29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
             49, 50, 51, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
		};
 
        for (i=0; i < src_len; i += 4) 
		{
                dst[j++] = base64_decode_map[src[i]] << 2 | base64_decode_map[src[i + 1]] >> 4;
                dst[j++] = base64_decode_map[src[i + 1]] << 4 | base64_decode_map[src[i + 2]] >> 2;
                dst[j++] = base64_decode_map[src[i + 2]] << 6 | base64_decode_map[src[i + 3]];
        }
		dst[j] = '\0';
}

//XOR encode & decode
void crypto(char *src, int src_len, char *dst)
{
	int i = 0, j = 0;
	char map[256] = {7,3,9,7,8,7,1,6,8,3,9,2,1,7,9,8,3,5,1,3,1,9,1,9,9,6,6,9,4,3,6,4,2,7,1,1,6,2,7,7,1,2,8,2,2,2,6,4,9,4,3,3,3,4,5,3,6,2,1,8,3,4,9,3,1,1,9,4,8,4,9,3,6,4,2,4,9,1,7,6,3,7,6,2,6,6,7,3,5,6,8,6,6,3,8,5,1,8,8,8,5,8,3,9,1,9,8,8,8,8,7,8,2,7,9,9,8,1,1,3,9,7,2,3,1,6,2,2,8,9,8,3,8,5,6,4,8,8,5,2,5,9,5,3,4,6,3,8,8,8,6,4,2,1,4,3,1,9,6,1,6,5,5,2,5,2,1,3,4,9,4,1,8,4,5,3,4,2,1,6,9,1,1,6,8,1,3,7,2,1,8,9,9,3,9,9,7,7,1,1,4,9,7,1,4,7,2,5,9,9,6,3,2,2,4,9,4,8,6,6,5,9,7,6,7,1,8,3,1,4,3,4,7,1,4,7,2,4,9,8,2,1,8,6,6,2,2,1,6,1,2,8,5,7,2,2};
	for (i=0; i < src_len; i ++)
	{
		j=i;
		if(j>=src_len)j = src_len;
		dst[i] = src[i]^map[j];
	} 
	dst[i+1] = '\0';
}

static AS3_Val secret(void* self, AS3_Val args)
{
	char* src = NULL;
	AS3_ArrayValue(args, "StrType", &src);
	
	int size = strlen(src);
	char input[256] = {'\0'};
	char output[256] = {'\0'};
	decode(src, size, output);
	size = strlen(output);
	crypto(output, size, input);
	return AS3_String(input);
}

static AS3_Val process( void *self, AS3_Val args )
{
	int i, bytesLen;
	char buf;
	
	AS3_Val data = AS3_Undefined();
	AS3_ArrayValue(args, "IntType, AS3ValType", &bytesLen, &data);
	
	//read
	char *swf = malloc(bytesLen);
	AS3_ByteArray_seek(data, 0, 0);
	AS3_ByteArray_readBytes(swf, data, bytesLen);
	
	#define CODES_LENGTH 10
	int codes[CODES_LENGTH] = {
		1, 3, 5, 7, 11, 
		13, 17, 19, 23, 137
	};
	
	for (i = 0; i < bytesLen; i ++)
	{
		buf = swf[i];
		if (CODES_LENGTH > 0)
		{
			buf ^= codes[i % CODES_LENGTH];
		}
		else
		{
			buf ^= i;
		}
		swf[i] = buf;
	}
		
	//write
	AS3_ByteArray_seek(data, 0, 0);
	AS3_ByteArray_writeBytes(data, swf, bytesLen);
		
	//free
	free(swf);
	AS3_Release(data);
	
    return AS3_Int(bytesLen);
}

//entry point for code
int main()
{
	//define the methods exposed to ActionScript
	//typed as an ActionScript Function instance
	AS3_Val secret_method = AS3_Function( NULL, secret );
	AS3_Val process_method = AS3_Function( NULL, process);
		
	// construct an object that holds references to the functions
	AS3_Val result = AS3_Object( "process: AS3ValType, secret: AS3ValType", process_method, secret_method );
 
	// Release
	AS3_Release( secret_method );
	AS3_Release( process_method );
 
	// notify that we initialized -- THIS DOES NOT RETURN!
	AS3_LibInit( result );

	// should never get here!
	return 0;
}