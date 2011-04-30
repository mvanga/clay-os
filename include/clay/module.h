#ifndef CLAY_MODULE_H
#define CLAY_MODULE_H

typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);

extern initcall_t __init_start;
extern initcall_t __init_end;
extern exitcall_t __exit_start;
extern exitcall_t __exit_end;

#define __used			__attribute__((__used__))
#define __section(S)	__attribute__ ((__section__(#S)))

#define __define_initcall(level,fn,id) \
	static initcall_t __initcall_##fn##id __used \
	__attribute__((__section__(".module" level ".init"))) = fn

#define __define_exitcall(level,fn,id) \
	static exitcall_t __exitcall_##fn##id __used \
	__attribute__((__section__(".module" level ".exit"))) = fn

/*
 * core are basic functionality. eg. board init
 * modules provide some functionality. eg. addon board inits
 * tasks are user written programs
 */
#define core_init(fn)		__define_initcall("0",fn,0)
#define module_init(fn)		__define_initcall("1",fn,1)
#define task_init(fn)		__define_initcall("2",fn,2)

#define core_exit(fn)		__define_exitcall("0",fn,0)
#define module_exit(fn)		__define_exitcall("1",fn,1)
#define task_exit(fn)		__define_exitcall("2",fn,2)

#endif
