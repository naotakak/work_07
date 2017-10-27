#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  int random_file = 0;
  random_file = open("/dev/random", O_RDONLY);
  int rand = 0;
  read(random_file, &rand, sizeof(rand));

  printf("random: %d\n", rand);
  close(random_file);

  int write_file = 0;
  write_file = open("numbers", O_CREAT | O_WRONLY);
  write(write_file, &rand, sizeof(rand));
  close(write_file);
  
  return 0;
}
