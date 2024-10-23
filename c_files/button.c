#include "button.h"

uint32_t ticks = 0;
//uint8_t previous_state = 0;


/****************************************************************************

Function:           unsigned short Get_Button_State(void);
Input:              Tipke

Output:             Vrne stanja tipk v LSB bitih short st   1 -> pritisnjeno

PreCondition:
Related Parameters:
Overview:



******************************************************************************/

uint8_t Get_Button_State(void){
     uint8_t result = 0;
     static uint8_t button_1_state = 0;          // treba dat v static
     static uint8_t button_2_state = 0;

   if (BUTTON1){
      //static unsigned short debounce_count_now = debounce_count;
      if(debounce_count >= 2 && BUTTON1){
          button_1_state = 1;
          debounce_count = 0;
      }
   }
     
   else if (BUTTON2){
      //static unsigned short debounce_count_now = debounce_count;
      if(debounce_count >= 2 && BUTTON2){
          button_2_state = 1;
          debounce_count = 0;
      }
   }
   else {
       debounce_count = 0;
       button_1_state = 0;
       button_2_state = 0;
   }

   result |= button_1_state | button_2_state << 1;

   return result;
}

/****************************************************************************

Function:           unsigned short Get_Button_Press(void);
Input:              Tipke

Output:             Vrne stanja tipk v LSB bitih short st   1 -> pritisnjeno

PreCondition:
Related Parameters:
Overview:           Preveri ali je gumb bil pritisnjen 1x



******************************************************************************/


uint8_t Get_Button_Press(void){
     uint8_t result = 0;
     uint8_t state = 0;
     static uint8_t previous_state = 0;

     state = Get_Button_State();
     result = ~state & previous_state;
     previous_state = state;
     return result;
     
}


/****************************************************************************

Function:           unsigned short Both_Button_Pressed(void);
Input:              Tipke

Output:             Vrne stanje tipk v LSB bitu short st   1 -> pritisnjeno
                    Oba moreta biti pritisnjena za 2s da vrne 1
PreCondition:
Related Parameters:
Overview:



******************************************************************************/

uint8_t Both_Button_Pressed(void){

    uint8_t  result = 0;
    
    if(BUTTON1 && BUTTON2){
         if(multitaskTimer - ticks >= 300){
             result = 1;
             ticks = multitaskTimer;
         }
    }
    else{
         ticks = multitaskTimer;
    }

    return result;
}
