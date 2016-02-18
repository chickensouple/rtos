#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP

struct Context {
	void* stackPtr;
};

void saveContext(Context*) __attribute(( naked ));

void loadContext(Context*) __attribute(( naked ));

#endif /* _CONTEXT_HPP */
