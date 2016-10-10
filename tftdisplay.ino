#include <application.h>
#include "RAIO8870.h"
#include "tft.h"

int _hour = 12;
int _minute = 0;
int _second = 0;

void setup() {
    
    
    
    TFT_init_board();
   
    
    
    TFT_hard_reset();
    
    RAIO_init();
    
}




void loop() {

   
    
    unsigned char text[] = "Hallo Jana, wie geht es Dir?";
    RAIO_clear_screen();
    
    RAIO_SetFontSizeFactor ( 0 );
    RAIO_print_text ( 10, 10, text, COLOR_WHITE , COLOR_BLACK );
    
    
    while(1)
    {
    delay(1000);
    
    }
   
}
