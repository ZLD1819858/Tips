#include <stdio.h>

#define COLOR_(msg, color, ctl) \
  "\033[38;5;" #ctl ";" #color "m" msg "\033[0m"

#define COLOR(msg, color) \
  "\033[38;5;" #color "m" msg "\033[0m"

#define BLACK(msg)  COLOR(msg, 30)
#define RED(msg)    COLOR(msg, 31)
#define GREEN(msg)  COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg)   COLOR(msg, 34)
#define PURPLE(msg) COLOR(msg, 35)
#define CYAN(msg)   COLOR(msg, 36)
#define WHITE(msg)  COLOR(msg, 37)

#define BBLACK(msg)  COLOR_(msg, 30, 5)
#define BRED(msg)    COLOR_(msg, 31, 5)
#define BGREEN(msg)  COLOR_(msg, 32, 5)
#define BYELLOW(msg) COLOR_(msg, 33, 5)
#define BBLUE(msg)   COLOR_(msg, 34, 5)
#define BPURPLE(msg) COLOR_(msg, 35, 5)
#define BCYAN(msg)   COLOR_(msg, 36, 5)
#define BWHITE(msg)  COLOR_(msg, 37, 5)

#define UBLACK(msg)  COLOR_(msg, 30, 5)
#define URED(msg)    COLOR_(msg, 31, 5)
#define UGREEN(msg)  COLOR_(msg, 32, 5)
#define UYELLOW(msg) COLOR_(msg, 33, 5)
#define UBLUE(msg)   COLOR_(msg, 34, 5)
#define UPURPLE(msg) COLOR_(msg, 35, 5)
#define UCYAN(msg)   COLOR_(msg, 36, 5)
#define UWHITE(msg)  COLOR_(msg, 37, 5)

int main() {
  printf(YELLOW("red")BLACK  ("BLACK\n"));
  printf(RED    ("RED\n"));
  printf(GREEN  ("GREEN\n"));
  printf(YELLOW ("YELLOW\n"));
  printf(BLUE   ("BLUE\n"));
  printf(PURPLE ("PURPLE\n"));
  printf(CYAN   ("CYAN\n"));
  printf(WHITE  ("WHITE\n"));

  printf(BBLACK ("Bold BLACK\n"));
  printf(BRED   ("Bold RED\n"));
  printf(BGREEN ("Bold GREEN\n"));
  printf(BYELLOW("Bold YELLOW\n"));
  printf(BBLUE  ("Bold BLUE\n"));
  printf(BPURPLE("Bold PURPLE\n"));
  printf(BCYAN  ("Bold CYAN\n"));
  printf(BWHITE ("Bold WHITE\n"));

  printf(UBLACK ("Underline BLACK\n"));
  printf(URED   ("Underline RED\n"));
  printf(UGREEN ("Underline GREEN\n"));
  printf(UYELLOW("Underline YELLOW\n"));
  printf(UBLUE  ("Underline BLUE\n"));
  printf(UPURPLE("Underline PURPLE\n"));
  printf(UCYAN  ("Underline CYAN\n"));
  printf(UWHITE ("Underline WHITE\n"));

  return 0;
}
