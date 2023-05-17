/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */
#include "chip.h"
#include <stdbool.h>
#include "digital.h"
#include "bsp.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

int main(void) {
    /*digital_output_t led_azul;
    digital_output_t led_rojo;
    digital_output_t led_amarillo;
    digital_output_t led_verde;

    digital_input_t boton_prueba;
    digital_input_t boton_cambiar;
    digital_input_t boton_prender;
    digital_input_t boton_apagar;*/

    board_t board=BoardCreate();

    int divisor = 0;
    bool current_state, last_state = false;


    while (true) {

        if (DigitalInputGetState(board->boton_prueba)) {
            DigitalOutputActivate(board->led_azul);
           /* Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_B_GPIO, LED_B_BIT, true);*/
        } else {
            /*Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_B_GPIO, LED_B_BIT, false);*/
            DigitalOutputDesactivate(board->led_azul);
        }

        current_state = DigitalInputGetState(board->boton_cambiar);
        if ((current_state) && (!last_state)) {
            /*Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED_1_GPIO, LED_1_BIT);*/
            DigitalOutputToggle(board->led_rojo);
        }
        last_state = current_state;

        if (DigitalInputGetState(board->boton_prender)) {
            /*Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_2_GPIO, LED_2_BIT, true);*/
            DigitalOutputActivate(board->led_amarillo);
        }
        if (DigitalInputGetState(board->boton_apagar)) {
            /*Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_2_GPIO, LED_2_BIT, false);*/
            DigitalOutputDesactivate(board->led_amarillo);
        }

        divisor++;
        if (divisor == 5) {
            divisor = 0;
            DigitalOutputToggle(board->led_verde);
        }

        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 25000; delay++) {
                __asm("NOP");
            }
        }
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */