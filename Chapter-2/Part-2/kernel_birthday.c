// Fun with kernel data structures

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};


int kb_init(void)
{
    struct birthday *person, *p;
    int i;

    printk(KERN_INFO "Initialising Kernel List Head \n");
    LIST_HEAD(&kbhead);

    printk(KERN_INFO "Adding nodes to birthday list \n");
    for(i = 0; i < 5; i++)
    {
        person = kmalloc(sizeof(person), GFP_KERNEL);
        person->day = 20+i;
        person->month = 5+i;
        person->year = 1989+i;

        INIT_LIST_HEAD(&person->list);

        list_add_tail(&(person->list), &(kbhead));
    }
    printk(KERN_INFO "Added nodes to birthday list \n");

    printk(KERN_INFO "Traversing Kernel Birthday list \n");
    list_for_each_entry(p, &kbhead, list)
    {
        printk(KERN_INFO "Birthday -> Day: %d, Month: %d, Year: %d \n", p->day, p->month, p->year);
    }

    return 0;
}

void kb_cleanup(void)
{
    struct birthday *person, *tmp;

    printk(KERN_INFO "Starting cleanup \n");

    list_for_each_entry_safe(person, tmp, &kbhead, list)
    {
        printk(KERN_INFO "Removing Node: %d-%d-%d \n", person->day, person->month, person->year);

        list_del(&person->list);
        kfree(person);
    }
}

module_init(kb_init);
module_exit(kb_cleanup);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Birthday List");
MODULE_AUTHOR("SVK");
