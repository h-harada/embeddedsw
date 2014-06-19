/*******************************************************************************
 *
 * Copyright (C) 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect. 
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * XILINX CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
*******************************************************************************/
/******************************************************************************/
/**
 *
 * @file xdptx_selftest_example.c
 *
 * Contains a design example using the XDptx driver. It performs a self test on
 * the DisplayPort TX core by training the main link at the maximum common
 * capabilities between the TX and RX and checking the lane status.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -----------------------------------------------
 * 1.00a als  06/17/14 Initial creation.
 * </pre>
 *
*******************************************************************************/

/******************************* Include Files ********************************/

#include "xdptx.h"
#include "xdptx_example_common.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xstatus.h"

/**************************** Constant Definitions ****************************/

#define DPTX_DEVICE_ID XPAR_DISPLAYPORT_0_DEVICE_ID

/**************************** Function Prototypes *****************************/

static u32 Dptx_SelfTestExample(u16 DeviceId);

/**************************** Function Definitions ****************************/

int main(void)
{
        u32 Status;

        Status = Dptx_SelfTestExample(DPTX_DEVICE_ID);
        if (Status != XST_SUCCESS) {
                xil_printf("XDptx_SelfTest failed.\n");
                return XST_FAILURE;
        }
        xil_printf("XDptx_SelfTest passed.\n");
        return Status;
}

static u32 Dptx_SelfTestExample(u16 DeviceId)
{
        u32 Status;

        Status = Dptx_SetupExample(&DptxInstance, DeviceId);
        if (Status != XST_SUCCESS) {
                return XST_FAILURE;
        }

#if defined(TRAIN_ADAPTIVE)
        XDptx_EnableTrainAdaptive(&DptxInstance, 1);
#else
        XDptx_EnableTrainAdaptive(&DptxInstance, 0);
#endif
#if defined(TRAIN_HAS_REDRIVER)
        XDptx_SetHasRedriverInPath(&DptxInstance, 1);
#else
        XDptx_SetHasRedriverInPath(&DptxInstance, 0);
#endif

        /* Run the self test. */
        Status = XDptx_SelfTest(&DptxInstance);
        return Status;
}