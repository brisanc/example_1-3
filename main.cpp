/**
 * @file main.cpp
 * @brief Este archivo contiene el pasaje de C++ a C.
 * @author Brisa Noguera
 */

#include "mbed.h"
#include "arm_book_lib.h"

#define __Cversion 13

int main(void)
{

#ifdef __Cversion

/**
 * @var gpio_t gpio_gasDetector_NV
 * @var gpio_t gpio_overTempDetector_NV
 * @var gpio_t gpio_alarmOffButton_NV
 * @var gpio_t gpio_alarmLed_NV
 * @brief Parámetros de configuración de los gpios.
 * 
 * Estas variables se utilizan para configurar:
 * - `gpio_gasDetector_NV`: Estado del detector de gas.
 * - `gpio_overTempDetector_NV`: Estado del detector de temperatura.
 * - `gpio_alarmOffButton_NV`: Resetear el estado de la alarma.
 * - `gpio_alarmLed_NV;`: Controlar el led de alarma.
 */

gpio_t gpio_gasDetector_NV, gpio_overTempDetector_NV, gpio_alarmOffButton_NV, gpio_alarmLed_NV;

/**
 * @struct DigitalIn_t
 * @brief Estructura que contiene parámetros de las entradas digitales.
 */
    typedef struct{
        PinName pin;
        PinMode mode;
    }DigitalIn_t;

/**
 * @struct DigitalOut_t
 * @brief Estructura que contiene parámetros de las salidas digitales.
 */
    typedef struct{
        PinName pin;
        int value;
    }DigitalOut_t;

// Declaracion de las estructuras
    DigitalIn_t gasDetector_NV,overTempDetector_NV,alarmOffButton_NV;
    DigitalOut_t alarmLed_NV;

// Se declara en que pin se realiza la conexion
    gasDetector_NV.pin = D2;
    overTempDetector_NV.pin = D3;
    alarmOffButton_NV.pin = BUTTON1;

    alarmLed_NV.pin = LED1;

// Se declaran los valores iniciales de los miembros de la estructura

    alarmLed_NV.value = OFF;
// Se configura la resistencia interna que tiene el micro
    gasDetector_NV.mode = PullDown;
    overTempDetector_NV.mode = PullDown;

// Especifico con que GPIOS  voy a estar trabajando y el en modo in o out segun corresponda

    gpio_init_in(&gpio_gasDetector_NV, gasDetector_NV.pin);
    gpio_init_in(&gpio_overTempDetector_NV, overTempDetector_NV.pin);
    gpio_init_in(&gpio_alarmOffButton_NV, alarmOffButton_NV.pin);
    gpio_init_out(&gpio_alarmLed_NV, alarmLed_NV.pin);

// a continuacion configuros los gpiossegun los datos que tienen las estructuras 

    gpio_init_in_ex(&gpio_gasDetector_NV, gasDetector_NV.pin,gasDetector_NV.mode);
    gpio_init_in_ex(&gpio_overTempDetector_NV, overTempDetector_NV.pin,overTempDetector_NV.mode);
    gpio_init_out_ex(&gpio_alarmLed_NV, alarmLed_NV.pin, alarmLed_NV.value);


#endif



#ifdef __cplusplus
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    DigitalIn alarmOffButton(BUTTON1);


    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);

    alarmLed = OFF;
#endif

    bool alarmState = OFF;

#ifdef __cplusplus
    while (true) {

        if ( gasDetector || overTempDetector ) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        if ( alarmOffButton ) {
            alarmState = OFF;
        }
    }
#endif

#ifdef __Cversion
    while (true) {

        if ( gpio_read(&gpio_gasDetector_NV) || gpio_read(&gpio_overTempDetector_NV) ) {
            alarmState = ON;
        }

        alarmLed_NV.value = alarmState;
        gpio_write(&gpio_alarmLed_NV, alarmLed_NV.value);

        if ( gpio_read(&gpio_alarmOffButton_NV)  ) {
            alarmState = OFF;
        }
    }
#endif

}