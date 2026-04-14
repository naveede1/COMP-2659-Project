#ifndef VBL_H
#define VBL_H

typedef void (*Vector)();


/* Global variables used by the VBL handler and main game loop to coordinate rendering and track time.*/
extern volatile int render_request;
extern volatile unsigned long vbl_ticks;

/*---- Function: init_vbl -------

  Purpose: Initalizes the VBL interrupt by installing our custom handler. Also resets the tick counter and render request flag.
  Inputs: None
  Returns: None
*/
void init_vbl();


/*---- Function: shutdown_vbl -------

  Purpose: Restores the original VBL interrupt handler.
  Inputs: None
  Returns: None
*/
void shutdown_vbl();


/* ---- Function: do_vbl_isr -------

  Purpose: The function called by the VBL interrupt handler. Increments the tick counter, updates music, and sets the render request flag.
  Inputs: None
  Returns: None
*/
void do_vbl_isr();

/*--- Function: vbl_isr -------
  Purpose: The interrupt service routine for the VBL interrupt.
  Inputs: None
  Returns: None

*/
void vbl_isr();


Vector install_vector(int num, Vector vector);

#endif