//kernel 6.2.0

# include <linux/sched.h>
# include <linux/module.h>
# include <linux/kernel.h>
# include <linux/list.h>
# include <linux/init_task.h> // init_task
# include <linux/fs_struct.h>
# include <linux/fdtable.h>
# include <asm/atomic.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Print PID of all processes");
MODULE_AUTHOR("Burger");

static int __init print_process_module_init(void){

    struct task_struct *p,*ts;
    struct list_head *pos;
    int p_count=0;
    p = &init_task;
    
    printk("process print module init\n");

    list_for_each(pos,&p->tasks){
        ts = list_entry(pos,struct task_struct,tasks);
        printk("%s ; pid:%d ; state:%u ; prio:%d ; static_prio:%d ; parent'pid:%d ; file counts:%d ; umask:%d;", \
                ts->comm,ts->pid,ts->__state,ts->prio,ts->static_prio,(ts->parent)->pid,atomic_read(&(ts->files)->count),(ts->fs)->umask);   
        p_count+=1;
        if(ts->mm != NULL){
            printk("total vm:%ld;\n",(ts->mm)->total_vm);
        }

    }
    printk("Total process-count:%d\n",p_count);
    return 0;

}


static void __exit print_process_module_exit(void){
    printk("process print module exit\n");

}
/// 
///
module_init(print_process_module_init);
module_exit(print_process_module_exit);

