#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>

#define READ_SIZE 256
#define VERSION_STRING(state) state == 1 ? "VERSION_MODIFIED" : "VERSION_RESET"

int read_file(int fd, char *buffer, int buffer_size, int read_size)
{
  int    rd;
  int    position;
  
  position = 0;
  rd = 0;
  do {
    if (position + read_size > buffer_size)
      read_size = position + read_size - buffer_size;
    position += rd;
  } while ((rd = read(fd, &buffer[position], read_size)) > 0);
  
  if (rd == -1)
    return -1;
  return position;
}

int write_file(int fd, char *string, int string_size, int write_size)
{
  int    wd;
  int    position;
  
  position = 0;
  wd = 0;
  do {
    if (position + write_size > string_size)
      write_size = position + write_size - string_size;
//      printf("try to write %d bytes at position %d, previously wrote %d\n", write_size, position, wd);
    position += wd;
  } while ((wd = write(fd, &string[position], write_size)) > 0 && position < string_size);
  
  if (wd == -1)
    return -1;
  return position;
}

int open_file(char *file)
{
  int fd;

  fd = open("/dev/version", O_RDWR);
  if (fd < 0)
  {
    printf("Cannot open the file\n");
    return 1;
  }
  
  return fd;
}

int test_read(int fd, int read_size)
{
  char string[255];
  int  byte_read; 

  if ((byte_read = read_file(fd, string, 255, read_size)) < 0)
  {
    printf("Error when reading file");
    return -1;
  }
  
  printf("Successfully read content, %d bytes\n", byte_read);
  printf("Content of /dev/version :%s\n", string);
  
  return byte_read;
}

int check_state(int fd)
{
  int state;
  int ret = ioctl(fd, 1, &state);
  if (ret < 0)
  {
    printf("ioctl failed\n");
    exit(1);
  }
  printf("Successfully asked state on device, it returned %s\n", VERSION_STRING(state));

  return ret;
}

int main() 
{
  int     fd; 
  int     byte_write;
  
  fd = open_file("/dev/version");
  assert(fd > 0);
  
  printf("Test reading operation:\n");
  assert(test_read(fd, 4) > 0);
  
  close(fd);
  fd = open_file("/dev/version");

  printf("\nTest writing operation:\n");
  if ((byte_write = write_file(fd, "test", 5, 4)) < 0)
  {
    printf("Error when writing file\n");
    return 1;
  }
    
  printf("Successfully write \"test\" on device, %d bytes\n", byte_write);
  //printf("Content of /dev/version :%s\n", string);

  close(fd);
  fd = open_file("/dev/version");
  assert(test_read(fd, 4) > 0);
  
  printf("\nTest ioctl operation:\n");
  check_state(fd);
  
  int ret = ioctl(fd, 0);
  if (ret < 0)
  {
    printf("ioctl failed\n");
    exit(1);
  }
  printf("Successfully reset version on device, read again the content...\n");
  
  close(fd);
  fd = open_file("/dev/version");
  assert(test_read(fd, 4) > 0);
  
  check_state(fd);
  
}