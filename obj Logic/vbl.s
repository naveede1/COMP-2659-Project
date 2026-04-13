        xdef    _vbl_isr                        ; Declare the VBL ISR to be used by the VBL interrupt vector
        xref    _do_vbl_isr                     ; Reference to the C function that will handle the VBL interrupt logic

_vbl_isr:                               
        movem.l d0-d7/a0-a6,-(sp)       
        jsr     _do_vbl_isr                     ; Call the helper C function 
        movem.l (sp)+,d0-d7/a0-a6
        rte
