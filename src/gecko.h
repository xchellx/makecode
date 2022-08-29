/*
 * MIT License
 * 
 * Copyright (c) 2022 Yonder
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _GECKO_H_
#define _GECKO_H_
#include <stdio.h>
#include <stdint.h>

/* ********************************************************************************************************************
 * print
 ******************************************************************************************************************* */
void printgecko(uint32_t a, uint32_t b) { printf("%08X %08X\n", a, b); }

void printppcasm(uint32_t ppcasm, uint8_t nl) { printf(nl ? "%08X\n" : "%08X ", ppcasm); }

/* ********************************************************************************************************************
 * if
 ******************************************************************************************************************* */
typedef enum __IfType {
    IF_EQU,
    IF_NEQ
} IfType;

void __if16(IfType it, uint8_t po, uint8_t endif, uint32_t addr, uint16_t val) {
    uint32_t op = 0x00000000;
    switch (it) {
        case IF_EQU:
            op = (po ? 0x38000000 : 0x28000000);
            break;
        case IF_NEQ:
            op = (po ? 0x3A000000 : 0x2A000000);
            break;
        default:
            return;
    }
    
    printgecko(((addr & ~0xFF000000) + (endif ? 1 : 0)) | op, 0x00000000 | val);
}

#define if16(it, po, addr, val) __if16(it, po, 0, addr, val)

#define if16e(it, po, addr, val) __if16(it, po, 1, addr, val)

void __if32(IfType it, uint8_t po, uint8_t endif, uint32_t addr, uint32_t val) {
    uint32_t op = 0x00000000;
    switch (it) {
        case IF_EQU:
            op = (po ? 0x30000000 : 0x20000000);
            break;
        case IF_NEQ:
            op = (po ? 0x32000000 : 0x22000000);
            break;
    }
    
    printgecko(((addr & ~0xFF000000) + (endif ? 1 : 0)) | op, val);
}

#define if32(it, po, addr, val) __if32(it, po, 0, addr, val)

#define if32e(it, po, addr, val) __if32(it, po, 1, addr, val)

void __endif(uint16_t n, uint8_t el, uint16_t ba, uint16_t po) {
    uint32_t op = 0xE2000000;
    if (el)
        op |= (1 << 20);
    uint32_t poba = 0x00000000;
    if (po != 0x00000000)
        poba |= po;
    if (ba != 0x00000000)
        poba |= (ba << 16);
    printgecko(n | op, poba);
}

#define endifnv(n, el, po, ba) __endif(n, el, po, ba)

#define endifn(n, el) __endif(n, el, 0x00000000, 0x00000000)

#define endifv(el, po, ba) __endif(1, el, po, ba)

#define endif(el) __endif(1, el, 0x00000000, 0x00000000)

/* ********************************************************************************************************************
 * write
 ******************************************************************************************************************* */
void write8(uint8_t po, uint32_t addr, uint8_t val) {
    printgecko(((uint32_t) (addr & ~0xFF000000)) | (po ? 0x10000000 : 0x00000000), (uint32_t) val);
}

void write16(uint8_t po, uint32_t addr, uint16_t val) {
    printgecko(((uint32_t) (addr & ~0xFF000000)) | (po ? 0x12000000 : 0x02000000), (uint32_t) val);
}

void write32(uint8_t po, uint32_t addr, uint32_t val) {
    printgecko(((uint32_t) (addr & ~0xFF000000)) | (po ? 0x14000000 : 0x04000000), val);
}

/* ********************************************************************************************************************
 * grN
 ******************************************************************************************************************* */
typedef enum __GeckoRegister {
    gr0,
    gr1,
    gr2,
    gr3,
    gr4,
    gr5,
    gr6,
    gr7,
    gr8,
    gr9
} GeckoRegister;

typedef enum __BaseType {
    GT_NONE,
    GT_BA,
    GT_PO
} BaseType;

void setgr(GeckoRegister gr, BaseType bt, uint8_t add, uint32_t val) {
    uint32_t op = (bt == GT_PO) ? 0x90000000 : 0x80000000;
    if (add)
        op |= (1 << 20);
    if (bt != GT_NONE)
        op |= (1 << 16);
    
    printgecko(((uint32_t) gr) | op, val);
}

typedef enum __DataSize {
    DS_8BITS,
    DS_16BITS,
    DS_32BITS
} DataSize;

void setintogr(GeckoRegister gr, BaseType bt, DataSize ds, uint32_t val) {
    uint32_t op = (bt == GT_PO) ? 0x92000000 : 0x82000000;
    op |= (((uint32_t) ds) << 20);
    if (bt != GT_NONE)
        op |= (1 << 16);
    
    printgecko(((uint32_t) gr) | op, val);
}

typedef enum __GeckoOp {
    GO_ADD,
    GO_MUL,
    GO_OR,
    GO_AND,
    GO_XOR,
    GO_SLW,
    GO_SRW,
    GO_ROL,
    GO_ASR,
    GO_FADDS,
    GO_FMULS
} GeckoOp;

typedef enum __GeckoOpValuesType {
    GV_SRCVALUE_DSTVALUE,
    GV_SRCREF_DSTVALUE,
    GV_SRCVALUE_DSTREF,
    GV_SRCREF_DSTREF
} GeckoOpValuesType;

void geckodirectop(GeckoRegister gr, GeckoOp go, GeckoOpValuesType gv, uint32_t val) {
    uint32_t op = 0x86000000;
    op |= (((uint8_t) go) << 20);
    op |= (((uint8_t) gv) << 16);
    
    printgecko(((uint32_t) gr) | op, val);
}

void geckoop(GeckoRegister grA, GeckoOp go, GeckoOpValuesType gv, GeckoRegister grB) {
    uint32_t op = 0x88000000;
    op |= (((uint8_t) go) << 20);
    op |= (((uint8_t) gv) << 16);
    
    printgecko(((uint32_t) grA) | op, (uint32_t) grB);
}

/* ********************************************************************************************************************
 * repeat
 ******************************************************************************************************************* */
typedef enum __RepeatBlock {
    b0,
    b1,
    b2,
    b3,
    b4,
    b5,
    b6,
    b7,
    b8,
    b9
} RepeatBlock;

void setrepeat(RepeatBlock rb, uint16_t nrep) {
    printgecko(((uint32_t) nrep) | 0x60000000, (uint32_t) rb);
}

void executerepeat(RepeatBlock rb) {
    printgecko(0x62000000, (uint32_t) rb);
}

/* ********************************************************************************************************************
 * po
 ******************************************************************************************************************* */
void __setpo(uint8_t fromref, GeckoRegister gr, BaseType bt, uint8_t bgr, uint8_t add, uint32_t val) {
    uint32_t op = fromref ? ((bt == GT_PO) ? 0x58000000 : 0x48000000) : ((bt == GT_PO) ? 0x5A000000 : 0x4A000000);
    if (add)
        op |= (1 << 20);
    if (bt != GT_NONE)
        op |= (1 << 16);
    if (bgr)
        op |= (1 << 12);
    
    printgecko(((uint32_t) gr) | op, val);
}

#define setpo(gr, bt, bgr, add, val) __setpo(0, gr, bt, bgr, add, val)

#define setintopo(gr, bt, bgr, add, val) __setpo(1, gr, bt, bgr, add, val)

/* ********************************************************************************************************************
 * ppcasm
 ******************************************************************************************************************* */
void runppcasm(int32_t ppcasmlen, uint32_t* ppcasm) {
    int32_t __ppcasmlen = ppcasmlen < 0 ? 0 : ppcasmlen;
    if (__ppcasmlen == 0)
        return;
    
    uint8_t evenppcasmlen = ((__ppcasmlen % 2) == 0);
    int32_t lnlen = evenppcasmlen ? (__ppcasmlen / 2) : (((__ppcasmlen + 1) / 2) + 1);
    printgecko(0xC0000000, lnlen);
    
    for (int32_t i = 0, j = __ppcasmlen; i < __ppcasmlen; i++, --j)
        printppcasm(ppcasm[i], evenppcasmlen ? ((j % 2) != 0) : ((j % 2) == 0));
    
    if (!evenppcasmlen)
        printppcasm(0x00000000, 1); // [padding]
}
#endif
