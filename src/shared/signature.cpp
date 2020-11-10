// ./a.out < xochitl
// ./a.out < remarkable-shutdown

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace swtfb {
  int* locate_signature(int fd, const char* find, int N) {
    char buf[N];

    int r;
    int bytes = 0;
    int offset = 0x10000;
    while (true) {
      r = read(fd, buf, N);
      if (r != N) {
        fprintf(stderr, "READ < N BYTES: %i %i\n", r, errno);
        break;
      }

      if (strncmp(find, buf, N) == 0) {
        int* s = (int*) (bytes + offset - 4);
        return s;
      }
      bytes += r;
    }
    fprintf(stderr, "READ %i BYTES\n", bytes);

    return NULL;
  }

  int* locate_signature(string path, const char* find, int N) {
    int fd = open(path.c_str(), O_RDONLY);
    fprintf(stderr, "SEARCHING %s %i\n", path.c_str(), fd);
    int* ret = locate_signature(fd, find, N);
    close(fd);
    return ret;
  }
}
