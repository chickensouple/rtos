#ifndef _MAIN_IRQ_HPP
#define _MAIN_IRQ_HPP

extern "C" {

void PendSVHandler(void) __attribute(( naked ));

void SysTickHandler(void);

void SetPendSV(void);

}

#endif /* _MAIN_IRQ_HPP */
