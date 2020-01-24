// SPDX-License-Identifier: MIT
/*
 * MIT License
 * Copyright (c) 2019 Renesas Electronics Corporation
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "mbed.h"
#include "SHT30_DIS_B.h"
#include "OPT3001DNP.h"
#include "BARO_2SMPB_02E.h"
#include "LIS2DW12.h"

#define CONV_RAW_TO_MG(x) (int)((double)(x) * 4000.0 / 32767.0)

SHT30_DIS_B sht30(I2C_SDA, I2C_SCL);                    // [SHT30-DIS-B] : Temperature / humidity sensor
OPT3001DNP opt3001(I2C_SDA, I2C_SCL);                   // [OPT3001DNP]  : Ambient light sensor
BARO_2SMPB_02E baro_2smpb(I2C_SDA, I2C_SCL);            // [2SMPB-02E]   : MEMS digital barometric pressure sensor
LIS2DW12 lis2dw(SPI_MOSI, SPI_MISO, SPI_SCKL, SPI_SSL); // [LIS2DW12]    : MEMS digital motion sensor

int main(void) {
    int32_t humi, temp32;
    uint32_t illm;
    uint32_t pres, dp, dt;
    int16_t temp16;
    int16_t accl[3];

    printf("\x1b[2J");  // Clear screen

    // setup sensors
    baro_2smpb.setup();
    sht30.setup();
    opt3001.setup();
    lis2dw.setup();

    ThisThread::sleep_for(150);

    while (1) {
        printf("\x1b[%d;%dH", 0, 0);  // Move cursor (y , x)
        printf("GR-MANGO x Omron 2JCIE-EV01 Demo\r\n\r\n");

        sht30.read(&humi, &temp32);
        printf("[SHT30-DIS-B] Temperature / humidity sensor\r\n");
        printf("   temperature : %5.2f [degC]\r\n", temp32 / 100.0);
        printf("   humidity    : %5.2f [%%RH]\r\n", humi / 100.0);
        printf("\r\n");

        opt3001.read(&illm);
        printf("[OPT3001DNP] Ambient light sensor\r\n");
        printf("   illuminance : %5.2f [lx]\r\n", illm / 100.0);
        printf("\r\n");

        baro_2smpb.read(&pres, &temp16, &dp, &dt);
        printf("[2SMPB-02E] MEMS digital barometric pressure sensor\r\n");
        printf("   pressure    : %7.1f [Pa] (%08Xh)\r\n", pres / 10.0 , (unsigned int)dp);
        printf("   temperature : %5.2f [degC] (%08Xh)\r\n", temp16 / 100.0, (unsigned int)dt);
        printf("\r\n");

        lis2dw.read(accl);
        printf("[LIS2DW12] MEMS digital motion sensor\r\n");
        printf("   x : %5d [mg]\r\n", CONV_RAW_TO_MG(accl[0]));
        printf("   y : %5d [mg]\r\n", CONV_RAW_TO_MG(accl[1]));
        printf("   z : %5d [mg]\r\n", CONV_RAW_TO_MG(accl[2]));
        printf("\r\n");

        ThisThread::sleep_for(200);
    }
}

