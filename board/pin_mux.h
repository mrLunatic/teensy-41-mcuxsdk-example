#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include <stdbool.h>

typedef enum _pin_mux_direction
{
    kPIN_MUX_DirectionInput = 0U,
    kPIN_MUX_DirectionOutput = 1U,
    kPIN_MUX_DirectionInputOrOutput = 2U
} pin_mux_direction_t;

#if defined(__cplusplus)
extern "C"
{
#endif

    void BOARD_InitPins(void);

    void BOARD_LED_Set(bool value);

#if defined(__cplusplus)
}
#endif

#endif
