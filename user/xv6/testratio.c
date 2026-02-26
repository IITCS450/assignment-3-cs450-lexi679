// testratio.c
#include "types.h"
#include "stat.h"
#include "user.h"

static volatile int sink;

// Do a small chunk of CPU work; returns 1 "work unit".
static int work_unit(void) {
  // Simple busy arithmetic to burn CPU.
  // sink is volatile so compiler can't optimize it away.
  for(int i = 0; i < 2000; i++){
    sink += (i ^ (sink << 1)) + 3;
  }
  return 1;
}

static void run_child(int tickets, int ms, int idx) {
  settickets(tickets);

  // uptime() is in ticks; in xv6 1 tick ~ 10ms (HZ=100)
  int ticks = ms / 10;
  if(ticks < 1) ticks = 1;

  int start = uptime();
  int units = 0;

  while(uptime() - start < ticks){
    units += work_unit();
  }

  sleep(20 * idx); // ensure that all children finish before any print

  printf(1, "pid %d tickets %d units %d\n", getpid(), tickets, units);
  exit();
}

int main(int argc, char *argv[]) {
  // Defaults: 3 children, run 2000ms, tickets 10/20/40
  int ms = 2000;
  int t0 = 10, t1 = 20, t2 = 40;

  if(argc >= 2) ms = atoi(argv[1]);
  if(argc >= 3) t0 = atoi(argv[2]);
  if(argc >= 4) t1 = atoi(argv[3]);
  if(argc >= 5) t2 = atoi(argv[4]);

  // Basic syscall validation (optional, but nice)
  if(settickets(0) != -1){
    printf(1, "FAIL: settickets validation\n");
    exit();
  }

  int tickets[3];
  tickets[0] = t0; tickets[1] = t1; tickets[2] = t2;

  printf(1, "testratio: ms=%d tickets=%d,%d,%d\n", ms, t0, t1, t2);

  for(int i = 0; i < 3; i++){
    int pid = fork();
    if(pid < 0){
      printf(1, "FAIL: fork\n");
      exit();
    }
    if(pid == 0){
      run_child(tickets[i], ms, i);
    }
  }

  // Wait for all children
  for(int i = 0; i < 3; i++)
    wait();

  printf(1, "testratio: done\n");
  exit();
}