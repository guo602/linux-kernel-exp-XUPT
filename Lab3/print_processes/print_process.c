//kernel 6.2.0

# include <linux/sched.h>
# include <linux/module.h>
# include <linux/kernel.h>
# include <linux/list.h>
# include <linux/init_task.h> // init_task

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Print PID of all processes");
MODULE_AUTHOR("Burger");

static int __init print_process_module_init(void){
    printk("process print module init\n");

    struct task_struct *p,*ts;
    struct list_head *pos;
    int p_count=0;
    p = &init_task;
    list_for_each(pos,&p->tasks){
        ts = list_entry(pos,struct task_struct,tasks);
        printk("%s pid:%d\n",ts->comm,ts->pid);   
        p_count+=1;
        // printk("process\n");

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

