#include <stdio.h>
#include <stdlib.h>

int randInt(int min, int max) {
  return min + rand() % (max - min + 1);
}

void randIP(char *buf, size_t bufsize) {
  snprintf(buf, bufsize, "%d.%d.%d.%d",
           randInt(0, 255), randInt(0, 255),
           randInt(0, 255), randInt(0, 255));
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  int n;
  char buf[16];
  printf("Enter number of IPs to generate : ");
  fgets(buf, sizeof(buf), stdin);

  if (sscanf(buf, "%d", &n) != 1) {
    fprintf(stderr, "Error: Invalid input.\n");
    return 1;
  }

  FILE *fp = fopen("ips.txt", "w");
  if (!fp) {
    fprintf(stderr, "Error: failed to open file.\n");
    return 1;
  }

  char ip[16];
  for (int i = 0; i < n; i++) {
    randIP(ip, sizeof(ip));

    if (fprintf(fp, "%s\n", ip) < 0) {
      fprintf(stderr, "Error: Failed to write.\n");
      return 1;
    }
  }

  fclose(fp);

  printf("\n[+] IPs Generated.\n");

  printf("\nPress any key to exit...");
  getchar();

  return 0;
}
