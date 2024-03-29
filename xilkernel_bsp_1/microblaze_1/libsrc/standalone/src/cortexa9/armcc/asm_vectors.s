;* $Id: asm_vectors.s,v 1.1.4.1 2011/10/24 09:35:17 sadanan Exp $
;******************************************************************************
;
; (c) Copyright 2009 Xilinx, Inc. All rights reserved.
;
; This file contains confidential and proprietary information of Xilinx, Inc.
; and is protected under U.S. and international copyright and other
; intellectual property laws.
;
; DISCLAIMER
; This disclaimer is not a license and does not grant any rights to the
; materials distributed herewith. Except as otherwise provided in a valid
; license issued to you by Xilinx, and to the maximum extent permitted by
; applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
; FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
; IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
; MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
; and (2) Xilinx shall not be liable (whether in contract or tort, including
; negligence, or under any other theory of liability) for any loss or damage
; of any kind or nature related to, arising under or in connection with these
; materials, including for any direct, or any indirect, special, incidental,
; or consequential loss or damage (including loss of data, profits, goodwill,
; or any type of loss or damage suffered as a result of any action brought by
; a third party) even if such damage or loss was reasonably foreseeable or
; Xilinx had been advised of the possibility of the same.
;
; CRITICAL APPLICATIONS
; Xilinx products are not designed or intended to be fail-safe, or for use in
; any application requiring fail-safe performance, such as life-support or
; safety devices or systems, Class III medical devices, nuclear facilities,
; applications related to the deployment of airbags, or any other applications
; that could lead to death, personal injury, or severe property or
; environmental damage (individually and collectively, "Critical
; Applications"). Customer assumes the sole risk and liability of any use of
; Xilinx products in Critical Applications, subject only to applicable laws
; and regulations governing limitations on product liability.
;
; THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
; AT ALL TIMES.
;
;****************************************************************************
;****************************************************************************
;**
; @file asm_vectors.s
;
; This file contains the initial vector table for the Cortex A9 processor
;
; <pre>
; MODIFICATION HISTORY:
;
; Ver	Who     Date	  Changes
; ----- ------- -------- ---------------------------------------------------
; 1.00a ecm/sdm 10/20/09 Initial version
; 3.11a asa	9/17/13	 Added support for neon.
; 4.00a pkp	22/01/14 Modified return addresses for interrupt 
;			 handlers 
;</pre>
;
; @note
;
; None.
;
;****************************************************************************

	EXPORT _vector_table
	EXPORT IRQHandler

	IMPORT _boot
	IMPORT _prestart
	IMPORT IRQInterrupt
	IMPORT FIQInterrupt
	IMPORT SWInterrupt
	IMPORT DataAbortInterrupt
	IMPORT PrefetchAbortInterrupt

	AREA |.vectors|, CODE
	REQUIRE8     {TRUE}
	PRESERVE8    {TRUE}
	ENTRY ; define this as an entry point
_vector_table
	B	_boot
	B	Undefined
	B	SVCHandler
	B	PrefetchAbortHandler
	B	DataAbortHandler
	NOP	; Placeholder for address exception vector
	B	IRQHandler
	B	FIQHandler


IRQHandler					; IRQ vector handler 
	
	stmdb	sp!,{r0-r3,r12,lr}		; state save from compiled code
	vpush {d0-d7}
	vpush {d16-d31}
	vmrs r1, FPSCR
	push {r1}
	vmrs r1, FPEXC
	push {r1}
	bl	IRQInterrupt			; IRQ vector
	pop 	{r1}
	vmsr    FPEXC, r1
	pop 	{r1}
	vmsr    FPSCR, r1
	vpop    {d16-d31}
	vpop    {d0-d7}
	ldmia	sp!,{r0-r3,r12,lr}		; state restore from compiled code 
	subs	pc, lr, #4			; adjust return 


FIQHandler					; FIQ vector handler 
	stmdb	sp!,{r0-r3,r12,lr}		; state save from compiled code 
	vpush {d0-d7}
	vpush {d16-d31}
	vmrs r1, FPSCR
	push {r1}
	vmrs r1, FPEXC
	push {r1}
FIQLoop
	bl	FIQInterrupt			; FIQ vector 
	pop 	{r1}
	vmsr    FPEXC, r1
	pop 	{r1}
	vmsr    FPSCR, r1
	vpop    {d16-d31}
	vpop    {d0-d7}
	ldmia	sp!,{r0-r3,r12,lr}		; state restore from compiled code 
	subs	pc, lr, #4			; adjust return 


Undefined					; Undefined handler 
	stmdb	sp!,{r0-r3,r12,lr}		; state save from compiled code 
	ldmia	sp!,{r0-r3,r12,lr}		; state restore from compiled code 
	b	_prestart			

	movs	pc, lr


SVCHandler					; SWI handler 
	stmdb	sp!,{r0-r3,r12,lr}		; state save from compiled code 
	tst	r0, #0x20			; check the T bit 
	ldrneh	r0, [lr,#-2]			; Thumb mode 
	bicne	r0, r0, #0xff00			; Thumb mode 
	ldreq	r0, [lr,#-4]			; ARM mode 
	biceq	r0, r0, #0xff000000		; ARM mode 
	bl	SWInterrupt			; SWInterrupt: call C function here 
	ldmia	sp!,{r0-r3,r12,lr}		; state restore from compiled code 
	movs	pc, lr				; adjust return 


DataAbortHandler				; Data Abort handler 
	stmdb	sp!,{r0-r3,r12,lr}		; state save from compiled code 
	bl	DataAbortInterrupt		;DataAbortInterrupt :call C function here 
	ldmia	sp!,{r0-r3,r12,lr}		; state restore from compiled code 
	subs	pc, lr, #8			; adjust return 

PrefetchAbortHandler				; Prefetch Abort handler 
	stmdb	sp!,{r0-r3,r12,lr}		; state save from compiled code 
	bl	PrefetchAbortInterrupt		; PrefetchAbortInterrupt: call C function here 
	ldmia	sp!,{r0-r3,r12,lr}		; state restore from compiled code 
	subs	pc, lr, #4			; adjust return 


	END
