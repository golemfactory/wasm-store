#include <stdio.h>

int main(int argc, char** argv) {
  char* name = argc >= 2 ? argv[1] : "anonymous";

  FILE* f_out = fopen("out.txt", "w");

  fprintf(f_out, "hello %s!\n", name);

  fclose(f_out);

  return 0;
}
