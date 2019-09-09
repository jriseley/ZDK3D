
#include "sprite3d.h"
#include "cab202_graphics.h"


int main(int argc, char ** argv){
 

    
    // Create a sprite3d
    sprite3d sprite; 
    sprite_init(&sprite, "/home/jenna/ZDK3D/mesh/Arwing_001.obj");
    
    // Move the sprite TODO add wrapper function
    transform_frame(sprite.frame, 1, 1, 15, 0, 0, 0);
    
    print_sprite3d(&sprite);
    
    
   
   //setup_screen();
   // SANDBOX - move to structs as appropes
   unsigned int width = 150; //screen_width();
   unsigned int height = 80; //screen_height();
   
   
   
   double ** fx = sprite.facets; 
   double ** vx = sprite.vertices; 
   
   // For each facet in the sprite...
   for(unsigned int i=0; i<sprite.facet_count; i++){
   
        int 1 =
        
        
        // For each pair of vertices in the sprite....
       for (unsigned int j=0; j<3; j++){
   
           // Index of first vertex
           int v1_i = j;
           
           // Index of 2nd vertex
           int v2_i = (j == 2) ? 0 : j+1;
   
        // Calculate the vertex coords in the screen buffer.
            double v1_x, v1_y, v1_z, v2_x, v2_y, v2_z;
            
            // TEST Print first vertex coords 
            
            // First point
            transform_point(sprite.frame,VX[v1_i][0] ,VX[v1_i][1] ,VX[v1_i][2] , &v1_x, &v1_y, &v1_z);   
            printf("%f,%f,%f\n",v1_x,v1_y,v1_z);
   
        // Draw a line between these two coords in the screen buffer.
           
           
           
       }
       
   }
   

   
   //clear_screen();
   
  // show_screen();
   
    //  timer_pause(1000);
   
    sprite_delete(&sprite);
    
    
    
    return 0;   
 
}
