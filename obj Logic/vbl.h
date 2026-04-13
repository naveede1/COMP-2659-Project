#ifndef VBL_H
#define VBL_H

typedef void (*Vector)();

void init_vbl(void);
void shutdown_vbl(void);
void do_vbl(void);
void vbl_isr(void);
Vector install_vector(int num, Vector vector);

extern volatile int render_request;
extern volatile unsigned long vbl_ticks;

#endif