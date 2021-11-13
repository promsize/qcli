#ifndef QCLI_H
#define QCLI_H

#include "qtty.h"

#define array_size(arr) (sizeof(arr) / sizeof((arr)[0]))

struct _qcli;
struct _qcli_cmd;
struct _qcli_tbl;

typedef struct _qcli     qcli_t;
typedef struct _qcli_cmd qcli_cmd_t;
typedef struct _qcli_tbl qcli_tbl_t;

typedef int (*qcli_fun_t) (qcli_t *c, int argc, char **argv);

struct _qcli_cmd {
  char       *cmd_name;
  char       *cmd_help;
  qcli_fun_t  cmd_fun;
  qcli_tbl_t *cmd_sub;
};

struct _qcli_tbl {
  int         cmdc;
  qcli_cmd_t *cmds;
};

#define QCLI_DEFINE(_sym)                       \
  static qcli_cmd_t _sym ## _cmds [];           \
  qcli_tbl_t _sym = {                           \
    .cmds = & _sym ## _cmds [0],                \
    .cmdc = array_size(_sym ## _cmds),          \
  };                                            \
  static qcli_cmd_t symbol ## _cmds[] =

static int qcli_quit(qcli_t *c, int argc, char **argv) {
  abort();
}

static qcli_cmd_t main_cmd[] = {
  {"quit", "quit qcli", qcli_quit, NULL}
};

static qcli_tbl_t main_tbl = {
                   .cmds = main_cmd,
                   .cmdc = array_size(main_cmd)
};

struct _qcli {
  qtty_t *tty;
  struct command_table *commands;
};

extern struct command_table cli_system_commands;

int qcli_init(qcli_t *c, qtty_t *tty);

int qcli_help(qcli_t *c, int argc, char **argv);
int qcli_exec(qcli_t *c, int argc, char **argv);

#endif /* !QCLI_H */