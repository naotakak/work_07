#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int get_rand() {
  int random_file = 0;
  random_file = open("/dev/random", O_RDONLY);
  int rand = 0;
  if (!read(random_file, &rand, sizeof(rand))) {
    printf("%s", strerror(errno));
  }
  if (!close(random_file)) {
    printf("%s", strerror(errno));
  }
  return rand;
}

int main() {
  //need to check return values for errors
  
  printf("Generating random numbers:\n");
  int rands[11];
  int i = 0;
  for (i; i < 11; i ++) {
    rands[i] = get_rand();
    printf("\trandom %d: %d\n", i, rands[i]);
  }

  printf("\nWriting numbers to file...\n\n");
  int write_file = 0;
  write_file = open("numbers", O_CREAT | O_WRONLY, 0644);
  if (!write_file) { 
    printf("%s", strerror(errno));
  }
  if (!write(write_file, &rands, sizeof(rands))) {
    printf("%s", strerror(errno));
  }
  if (!close(write_file)) {
    printf("%s", strerror(errno));
  }

  printf("Reading numbers from file...\n\n");
  int read_file = 0;
  int read_rands[11];
  read_file = open("numbers", O_RDONLY);
  if (!read_file) {
    printf("%s", strerror(errno));
  }
  if (!read(read_file, &read_rands, sizeof(read_rands))) {
    printf("%s", strerror(errno));
  }
  if (!close(read_file)) {
    printf("%s", strerror(errno));
  }

  printf("Verification that written values were the same:\n");
  i = 0;
  for (i; i < 11; i ++) {
    printf("\trandom %d: %d\n", i, read_rands[i]);
  }

  return 0;
}
