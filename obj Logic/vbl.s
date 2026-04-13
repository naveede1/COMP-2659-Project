        xdef    _vbl_isr
        xref    _do_vbl_isr

_vbl_isr:
        movem.l d0-d7/a0-a6,-(sp)
        jsr     _do_vbl_isr
        movem.l (sp)+,d0-d7/a0-a6
        rte
