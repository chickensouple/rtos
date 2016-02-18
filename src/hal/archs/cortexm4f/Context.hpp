#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP

struct Context {
	void* stackPtr;
};

void saveContext(Context*) __attribute(( naked ));

void loadContext(Context*) __attribute(( naked ));

void yield(void);

#endif /* _CONTEXT_HPP */
