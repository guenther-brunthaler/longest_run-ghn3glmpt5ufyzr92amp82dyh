#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
   char const *error= 0;
   unsigned long run, longest;
   int c, last, best;
   run= longest= 0; last= best= EOF;
   while ((c= getchar()) != EOF) {
      if (c == last) {
         ++run;
      } else {
         if (run > longest) {
            longest= run;
            best= last;
         }
         last= c;
         run= 1;
      }
   }
   if (run > longest) {
      longest= run;
      best= last;
   }
   if (ferror(stdin)) {
      error= "Read error!";
      goto fail;
   }
   if (longest && fprintf(stderr, "byte value: %#02x\n", best) <= 0) {
      goto write_error;
   }
   if (fputs("run length: ", stderr) < 0) goto write_error;
   if (printf("%lu\n", longest) <= 0) goto write_error;
   if (fflush(0)) {
      write_error:
      error= "Write error!";
      fail:
      (void)fputs(error, stderr);
      (void)fputc('\n', stderr);
   }
   return error ? EXIT_FAILURE : EXIT_SUCCESS;
}
