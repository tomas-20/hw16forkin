#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void identify() {
  printf("I'm %d, child of %d,", getpid(), getppid());
}

int get_sleep_time() {
  unsigned int rand;
  int file = open("/dev/random", O_RDONLY);
  read(file, &rand, sizeof(rand));
  close(file);
  return rand % 4 + 2;
}

int child_stuff() {
  int sleep_time = get_sleep_time();
  printf("waaa ");
  identify();
  printf(" and I'm about to sleep for %d seconds\n", sleep_time);
  sleep(sleep_time);
  return sleep_time;
}

int main() {
  identify();
  printf(" and I'm about to fork\n");
  if (!fork()) {
    return child_stuff();
  }
  else if (!fork()) {
    return child_stuff();
  }
  else {
    int status;
    int child = wait(&status);
    identify();
    printf(" and my child %d has just died after sleeping for %d seconds\n", child, WEXITSTATUS(status));
  }
  return 0;
}
