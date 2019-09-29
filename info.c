#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/syscalls.h>
#include <uapi/asm-generic/errno-base.h>

asmlinkage long sys_sh_task_info(pid_t pid, char *name){
	if(pid <=0) {
	return -EINVAL;
	}
	struct task_struct *task;
	struct file *file;
	loff_t pos  = 0;
	int fd;
	char data[1000];
	char add[1000];
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);
	fd = sys_open(name, O_WRONLY|O_CREAT, 0644);
	for_each_process(task){
	if((long)task_pid_nr(task) == (long)pid){

		printk(	"Process : %s\n PID_Number : %ld\n Process State : %ld\n Priority : %ld\n RT_Priority: %ld\n Nornal Priority : %ld\n", task->comm,(long)task->pid,(long)task->state, (long)task->prio, 	(long)task->rt_priority, (long)task->normal_prio );
		strcat(data, "Process: ");
		strcat(data , task->comm);
		strcat(data, "\n");
		strcat(data, "PID NUMBER: ");
		sprintf(add, "%ld\n", (long)task->pid);
		strcat(data,add);
		strcat(data, "Process State: ");
		sprintf(add,"%ld\n", (long)task->state);
		strcat(data,add);
		strcat(data, "Priority: ");
		sprintf(add, "%ld\n", (long)task->prio);
		strcat(data, add);
		strcat(data, "RT_Priority: ");
		sprintf(add,"%ld\n",(long)task->rt_priority);
		strcat(data,add);
		strcat(data, "Normal Priority: ");
		sprintf(add, "%ld\n", (long)task->normal_prio);
		strcat(data,add);

		if(fd<0){
			return -EISDIR;
		}
		if(fd>=0){
			sys_write(fd,data,1000);
			file = fget(fd);
			if(file){
				vfs_write(file,data,1000,&pos);
				fput(file);
			}
			sys_close(fd);
		}
		set_fs(old_fs);
	}

}
return 0;
}
