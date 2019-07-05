#include "sha1.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define hex(c) ((*(c)>='a')?*(c)-'a'+10:(*(c)>='A')?*(c)-'A'+10:*(c)-'0') 
#define HASH_BYTE_LENGTH 20

/*
 * Searches for the next configuration of bytes in the region such that hash of str matches the given pattern.
 * It starts with current configuration of bytes in the region, increments the bytes until first match is found.
 * It modifies the region in str, actually the region in str is kind of state of the search for all matches.
 * The function is to be called multiple times.
 * The bytes in the region is interpreted as little endian representation of the number. 
 * Upon the first call it should be 0. The search is done when the number loops back to 0.
 * Not all configuration of bytes are eligible. Only one s-th part is eligible. Which part is set by param r.
 * @param poz_start first position of the region (inclusive)
 * @param poz_end last position of the region (exclusive)
 * @param r reminder
 * @param s denominator
 * @param first indicates if current configuration of bytes in the region is to be checked (1) or not (0); is it first call to SHA1Progress
 * @return 0 - if matching hash is found, 1 - if matching hash is not found and all eligible configurations of bytes in the region were checked
 */
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
    SHA1_CTX ctx1;
    int poz;
    poz = poz_start;
    if (!first) {
	str[poz] ++;  //move to the next configuration of bytes in the region
        if (str[poz] == (const unsigned char) 0) {
            poz ++;
        }
    }
    while (1) {
	if (poz > poz_start) {
	    if (poz == poz_end) {
		return 1; //all possible configurations of bytes in the region were checked
	    }
	} else if ( (poz_end-poz_start == 1 && str[poz_start] % s == r) || (poz_end-poz_start > 1 && ( (str[poz_start]+256*str[poz_start+1]) % s == r))) {
            ctx1 = *ctx;
            for (unsigned int ii=poz_start; ii<len; ii+=1)
                SHA1Update(&ctx1, (const unsigned char*)str + ii, 1);
            SHA1Final((unsigned char *)hash_out, &ctx1);

	    unsigned int jj;
	    for (jj = 0; jj < pattern_len; jj+=1 ) {
		if (hash_out[HASH_BYTE_LENGTH-pattern_len + jj] != pattern[jj]) 
		    break;
	    }
	    if (jj == pattern_len)
	        return 0; //matching hash is found
	}

	str[poz] ++;  //move to the next configuration of bytes in the region
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
    int reminder,
    int denominator,
    FILE * f_out)
{
    SHA1_CTX ctx;
    unsigned int ii;
    char result[HASH_BYTE_LENGTH+1];
    int char_pattern_len = pattern_len/2;
    char *char_pattern = malloc ( char_pattern_len * sizeof (char));

    for (int ii = 0; ii < char_pattern_len; ii += 1) {
	char_pattern[ii] = hex(pattern+2*ii)*16+hex(pattern+2*ii+1);
    }

    result[HASH_BYTE_LENGTH] = '\0';
    for (ii=poz_start; ii<poz_end; ii+=1)
        str[ii] = 0;

    SHA1Init(&ctx);
    for (ii=0; ii<poz_start; ii+=1)
        SHA1Update(&ctx, (const unsigned char*)str + ii, 1);

    int first = 1;
    while (SHA1Progress(result, str, len, poz_start, poz_end, &ctx, char_pattern, char_pattern_len, reminder, denominator, first) == 0) {
	    for ( int ii = poz_start; ii < poz_end; ii += 1 )
		fprintf(f_out, "%02x", str[ii]&0xff);
	    fprintf(f_out, " -> ");
	    for ( int ii = 0; ii < HASH_BYTE_LENGTH; ii++)
		fprintf(f_out, "%02x", result[ii]&0xff);
            fprintf(f_out, "\n");
	    first = 0;
    }
}


int main(
   int argc, char** argv 
)
{
  int reminder = (int) strtol(argv[1], (char **)NULL, 10);
  int denominator = (int) strtol(argv[2], (char **)NULL, 10);

  int region_start = (int) strtol(argv[3], (char **)NULL, 10);
  int region_end = (int) strtol(argv[4], (char **)NULL, 10);

  char *pattern = argv[5];

  char *f_in_name = argv[6];

  FILE *f_in = fopen(f_in_name, "rb");
  fseek(f_in, 0, SEEK_END);
  long fsize = ftell(f_in);
  fseek(f_in, 0, SEEK_SET);  /* same as rewind(f_in); */

  char *fcontent = malloc(fsize + 1);
  fread(fcontent, 1, fsize, f_in);
  fclose(f_in);

  fcontent[fsize] = 0;

  FILE* f_out;
  if (argc == 8) {
      char *f_out_name = argv[7];
      f_out = fopen(f_out_name, "w");
  } else {
      f_out = stdout;
  }

  /* calculate hash */
  SHA1Check( fcontent, fsize, region_start , region_end, pattern, strlen(pattern), reminder, denominator, f_out);

  if (argc == 8)
    fclose(f_out);

  return 0;
}


