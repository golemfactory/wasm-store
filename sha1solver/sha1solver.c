#include "sha1.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define hex(c) ((*(c)>='a')?*(c)-'a'+10:(*(c)>='A')?*(c)-'A'+10:*(c)-'0') 

int SHA1Progress(
    char *hash_out,
    char *str,
    int len,
    int poz_start,
    int poz_end,
    SHA1_CTX * ctx,
    char *pattern,
    int pattern_len,
    int r,
    int s,
    int first)
{
    unsigned int ii;

    SHA1Init(ctx);
    for (ii=0; ii<poz_start; ii+=1)
        SHA1Update(ctx, (const unsigned char*)str + ii, 1);

    SHA1_CTX ctx1;
    int poz;
    poz = poz_start;
    if (!first) {
	str[poz] ++;
        if (str[poz] == (const unsigned char) 0) {
            poz ++;
        }
    }
    while (1) {
	if (poz > poz_start) {
	    if (poz == poz_end) {
		return 1;
	    }
	} else if ( (poz_end-poz_start == 1 && str[poz_start] % s == r) || (poz_end-poz_start > 1 && ( (str[poz_start]+256*str[poz_start+1]) % s == r))) {
            ctx1 = *ctx;
            for (ii=poz_start; ii<len; ii+=1)
                SHA1Update(&ctx1, (const unsigned char*)str + ii, 1);
            SHA1Final((unsigned char *)hash_out, &ctx1);

	    for (ii = 0; ii < pattern_len; ii+=1 ) {
		if (hash_out[20-pattern_len + ii] != pattern[ii]) 
		    break;
	    }
	    if (ii == pattern_len)
	        return 0;
	}

	str[poz] ++;
        if (str[poz] == (const unsigned char) 0) {
            poz ++;
        } else {
	    poz = poz_start;
	}
    }
}

void SHA1Check(
    char *str,
    int len,
    int poz_start,
    int poz_end,
    char *pattern,
    int pattern_len,
    int r,
    int s,
    FILE * f_out)
{
    SHA1_CTX ctx;
    unsigned int ii;
    char result[21];
    char hexresult[41];
    hexresult[40] = '\0';
    size_t offset;
    int char_pattern_len = pattern_len/2;
    char *char_pattern = (char*)malloc ( (char_pattern_len) * sizeof (char));

    for (int ii = 0; ii < char_pattern_len; ii += 1) {
	char_pattern[ii] = hex(pattern+2*ii)*16+hex(pattern+2*ii+1);
    }

    result[20] = '\0';
    for (ii=poz_start; ii<poz_end; ii+=1)
        str[ii] = (const unsigned char) 0;

    SHA1Init(&ctx);
    for (ii=0; ii<poz_start; ii+=1)
        SHA1Update(&ctx, (const unsigned char*)str + ii, 1);

    int first = 1;
    while (SHA1Progress(result, str, len, poz_start, poz_end, &ctx, char_pattern, char_pattern_len, r, s, first) == 0) {
            for ( offset = 0; offset < 20; offset++)
                sprintf( ( hexresult + (2*offset)), "%02x", result[offset]&0xff);
	    for ( int ii = poz_start; ii < poz_end; ii += 1 )
		fprintf(f_out, "%c", str[ii]);
            fprintf(f_out, " -> %s\n", hexresult);
	    first = 0;
    }
}


int main(
   int argc, char** argv 
)
{
  int r = (int) strtol(argv[1], (char **)NULL, 10);
  int s = (int) strtol(argv[2], (char **)NULL, 10);

  int region_start = (int) strtol(argv[3], (char **)NULL, 10);
  int region_end = (int) strtol(argv[4], (char **)NULL, 10);

  char *pattern = argv[5];

  FILE *f_in = fopen("infile", "rb");
  fseek(f_in, 0, SEEK_END);
  long fsize = ftell(f_in);
  fseek(f_in, 0, SEEK_SET);  /* same as rewind(f_in); */

  char *fcontent = malloc(fsize + 1);
  fread(fcontent, 1, fsize, f_in);
  fclose(f_in);

  fcontent[fsize] = 0;

  FILE* f_out = fopen("out.txt", "w");

  /* calculate hash */
  SHA1Check( fcontent, fsize, region_start , region_end, pattern, strlen(pattern), r, s, f_out);

  fclose(f_out);

  return 0;
}


