#include "digital.h"
#include "chip.h"
#include <stdint.h>
#include <stdbool.h>


#ifndef OUTPUT_INSTANCES
    #define OUTPUT_INSTANCES 4
#endif
#ifndef INPUT_INSTANCES
    #define INPUT_INSTANCES 4
#endif


struct  digital_input_s {
    uint8_t port;
    uint8_t pin;
    bool inverted;
    bool allocated:1;
};


struct  digital_output_s {
    uint8_t port;
    uint8_t pin;
    bool allocated;
};


digital_input_t DigitalInputAllocate(void);

digital_output_t DigitalOutputAllocate(void);




digital_input_t DigitalInputAllocate(void){
    digital_input_t input = NULL;



    static struct digital_input_s instances [INPUT_INSTANCES] = {0};


    for (int index = 0; index < INPUT_INSTANCES; index++) {
        if (!instances[index].allocated){
            instances[index].allocated = true;
            input = &instances[index];
            break;
        }
    }
    return input;
}




digital_output_t DigitalOutputAllocate(void){
    digital_output_t output = NULL;



    static struct digital_output_s instances [OUTPUT_INSTANCES] = {0};


    for (int index = 0; index < OUTPUT_INSTANCES; index++) {
        if (!instances[index].allocated){
            instances[index].allocated = true;
            output = &instances[index];
            break;
        }
    }
    return output;
}




digital_input_t DigitalInputCreate(uint8_t port,uint8_t pin){
    digital_input_t input = DigitalInputAllocate();

    if(input){
        input->port = port;
        input->pin = pin;
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, input->port,input->pin, true);
    }
    return input;
}



bool DigitalInputGetState(digital_input_t input){
    return input->inverted ^ Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->port,input->pin);
}

bool DigitalInputHasChanged(digital_input_t input){
    return false;
}

bool DigitalInputHasActivated(digital_input_t input){
    return false;
}

bool DigitalInputHasDesactivated(digital_input_t input){
    return false;
}




digital_output_t DigitalOutputCreate(uint8_t port,uint8_t pin){
    digital_output_t output = DigitalOutputAllocate();

    if(output){
        output->port = port;
        output->pin = pin;
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port,output->pin,false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->port,output->pin, true);
    }
    return output;
}

void DigitalOutputActivate(digital_output_t output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port,output->pin,true);
}

void DigitalOutputDesactivate(digital_output_t output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port,output->pin,false);
}

void DigitalOutputToggle(digital_output_t output){
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port,output->pin);
}


/*
void Digital
    static struct digital_output_s output;

    output.port = port;
    output.pin = pin;
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output.port, output.pin, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output.port, output.pin, true);

    return &output;
}
*/




/*
void DigitalOutputToggle(digital_output_t output){
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port, output->pin);


}
*/