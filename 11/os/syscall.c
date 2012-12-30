#include "defines.h"
#include "kozos.h"
#include "syscall.h"

/*システム・コール*/
kz_thread_id_t kz_run(kz_func_t func, char *name, int priority, int stacksize, int argc, char *argv[])
{
  /*スタックはスレッドごとに確保されるので、パラメータ域は自動変数としてスタック上に確保する*/
  kz_syscall_param_t param;

  param.un.run.func = func;
  param.un.run.name = name;
  param.un.run.priority = priority;
  param.un.run.stacksize = stacksize;
  param.un.run.argc = argc;
  param.un.run.argv = argv;
  /*システムコールを呼び出す*/
  kz_syscall(KZ_SYSCALL_TYPE_RUN, &param);
  /*システムコールの応答が構造体に書くほうされているので戻りあたいとして返す*/
  return param.un.run.ret; 
}

void kz_exit(void)
{
  kz_syscall(KZ_SYSCALL_TYPE_EXIT, NULL);
}

int kz_wait(void)
{
  kz_syscall_param_t param;
  kz_syscall(KZ_SYSCALL_TYPE_WAIT, &param);
  return param.un.wait.ret;
}

int kz_sleep(void)
{
  kz_syscall_param_t param;
  kz_syscall(KZ_SYSCALL_TYPE_SLEEP, &param);
  return param.un.sleep.ret;
}

int kz_wakeup(kz_thread_id_t id)
{
  kz_syscall_param_t param;
  param.un.wakeup.id = id;
  kz_syscall(KZ_SYSCALL_TYPE_SLEEP, &param);
  return param.un.wakeup.ret;
}

kz_thread_id_t kz_getid(void)
{
  kz_syscall_param_t param;
  kz_syscall(KZ_SYSCALL_TYPE_GETID, &param);
  return param.un.getid.ret;
}

int kz_chpri(int priority)
{
  kz_syscall_param_t param;
  param.un.chpri.priority = priority;
  kz_syscall(KZ_SYSCALL_TYPE_CHPRI, &param);
  return param.un.chpri.ret;
}


void *kz_kmalloc(int size)
{
  kz_syscall_param_t param;
  param.un.kmalloc.size = size;
  kz_syscall(KZ_SYSCALL_TYPE_KMALLOC, &param);
  return param.un.kmalloc.ret;
}

int kz_kmfree(void *p)
{
  kz_syscall_param_t param;
  param.un.kmfree.p = p;
  kz_syscall(KZ_SYSCALL_TYPE_KMFREE, &param);
  return param.un.kmfree.ret;
}

int kz_send(kz_msgbox_id_t id, int size, char *p)
{
  kz_syscall_param_t param;
  param.un.send.id = id;
  param.un.send.size = size;
  kz_syscall(KZ_SYSCALL_TYPE_SEND, &param);
  return param.un.send.ret;
}

kz_thread_id_t kz_recv(kz_msgbox_id_t id, int *sizep, char **pp)
{
  kz_syscall_param_t param;
  param.un.recv.id = id;
  param.un.recv.sizep = sizep;
  param.un.recv.pp = pp;
  kz_syscall(KZ_SYSCALL_TYPE_RECV, &param);
  return param.un.recv.ret;
}