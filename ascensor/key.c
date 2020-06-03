#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/select.h>
#include <termios.h>
int key_pressed(void)
{
  struct timeval timeout = {0, 0};
  fd_set rd_fdset;
  FD_ZERO(&rd_fdset);
  FD_SET(0, &rd_fdset);
  return select(1, &rd_fdset, NULL, NULL, &timeout) > 0;
}
void key_process(int ch)
{
  switch (ch)
  {
  case 'h':
    (flags_key |= FLAG_PULSADOR_P1);
    break;
  case 'j':
    (flags_key |= FLAG_PULSADOR_P2);
    break;
  case 'k':
    (flags_key |= FLAG_PULSADOR_C1);
    break;
  case 'l':
    (flags_key |= FLAG_PULSADOR_C2);
    break;
  case 'm':
    (flags_key |= FLAG_SENSOR_A1);
    break;
  case 'n':
    (flags_key |= FLAG_SENSOR_A2);
    break;

  case 'q':
    exit(0);
    break;
  }
}
/* RAW MODE */
static struct termios orig_termios;
void disable_raw_mode()
{
  if (tcsetattr(0, TCSAFLUSH, &orig_termios) == -1)
    perror("tcsetattr");
}
void enable_raw_mode()
{
  if (tcgetattr(0, &orig_termios) == -1)
    perror("tcgetattr");
  atexit(disable_raw_mode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(0, TCSAFLUSH, &raw) == -1)
    perror("tcsetattr");
}
