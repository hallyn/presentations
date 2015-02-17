#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// this is just a c program that execs itself with a different
// name and then sleeps for a long time.
int main(int argc, char* argv[]) {
   int sleeptime = 60 * 60 * 24;
   char *p;

   p = getenv("_MYNAME");
   if (p == NULL || (strcmp(argv[0], p) != 0)) {
      char myname[255];
      if (argc < 2) {
         fprintf(stderr, "Must give name");
         return(1);
      }
      sprintf(myname, "_MYNAME=%s", argv[1]);
      putenv(myname);
      execvp(argv[0], &argv[1]);
   }

   p = getenv("SLEEPTIME");
   if (p != NULL)
      sscanf(p, "%i", &sleeptime);

   fprintf(stderr, "[%s] pid=%i uid=%i gid=%i sleep=%i\n",
           argv[0], getpid(), getuid(), getgid(), sleeptime);

   return(sleep(sleeptime));
}
