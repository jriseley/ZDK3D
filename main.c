
#include "sprite3d.h"
#include "cab202_graphics.h"


int main(int argc, char ** argv){
 
   // setup_screen();
   // clear_screen();
    
    // Create a sprite3d
    sprite3d sprite; 
    sprite_init(&sprite, "/home/jenna/ZDK3D/mesh/Arwing_001.obj");
    
    print_sprite3d(&sprite);
    
    sprite_delete(&sprite);
    
    return 0;   
 
}
