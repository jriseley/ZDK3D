
#include <math.h>

#include "sprite3d.h"
#include "cab202_graphics.h"
#include "cab202_timers.h"

#define PIX_PER_M (15)


int main(int argc, char ** argv){
 

    
    // Create a sprite3d
    sprite3d sprite; 
    sprite_init(&sprite, "/home/jenna/ZDK3D/mesh/Arwing_001.obj");
     print_sprite3d(&sprite);
    
    // Move the sprite TODO add wrapper function
    transform_frame(sprite.frame, 10,0,15,0.1, M_PI, -M_PI/2.0);
    
    print_sprite3d(&sprite);
    
   setup_screen();
   clear_screen();
   // SANDBOX - move to structs as appropes
   double width = screen_width();
   double height =screen_height();
   
   double ** vx = sprite.vertices; 
   
   double f0 = 5.0; // distance from world reference frame to image plane
   
   // Scroll thru some values
   for (unsigned int k=0; k<100; k++){
   
       clear_screen();

    transform_frame(sprite.frame, 0, 0, -0.5, 0, 0.05, 0.0);   
   // print_sprite3d(&sprite);
    
   // For each facet in the sprite...
   for(unsigned int i=0; i<sprite.facet_count; i++){
   
        // For each pair of vertices in the sprite....
       for (unsigned int j=0; j<3; j++){
   
           //printf("\n\ni=%d,j=%d\n",i,j);
           // Index of first vertex
           int v1_i = sprite.facets[i][j]-1;
           // Index of 2nd vertex
           int v2_i = (j == 2) ? sprite.facets[i][0]-1 : sprite.facets[i][j+1]-1;
           //printf("v1_i=%d,v2_i=%d\n",v1_i,v2_i);
           
        // Calculate the vertex coords in the screen buffer.
            double v1x, v1y, v1z, v2x, v2y, v2z;
            
            // TEST Print first vertex coords 
            //printf("Original point: %f,%f,%f\n",vx[v1_i][0],vx[v1_i][1],vx[v1_i][2]);
            // First point
            transform_point(sprite.frame,vx[v1_i][0] ,vx[v1_i][1] ,vx[v1_i][2] , &v1x, &v1y, &v1z);   
            //printf("Transformed point: %f,%f,%f\n",v1x,v1y,v1z);
   
            // Second point
            transform_point(sprite.frame,vx[v2_i][0] ,vx[v2_i][1] ,vx[v2_i][2] , &v2x, &v2y, &v2z);   

            // Figure out x and y locations of these points in the screen buffer 
            // Adjust to u,v style coordinates by adding half screen height and width 
            int v1x_, v1y_, v2x_, v2y_;
            v1x_ = (int)round((v1x*f0/v1z)*PIX_PER_M + width/2.0);
            v1y_ = (int)round((v1y*f0/v1z)*PIX_PER_M + height / 2.0);
            v2x_ = (int)round((v2x*f0/v2z)*PIX_PER_M + width/2.0);
            v2y_ = (int)round((v2y*f0/v2z)*PIX_PER_M + height/2.0);
            //printf("(%d,%d)-->(%d,%d)\n",v1x_,v1y_,v2x_,v2y_);
            
            // Draw a line between these two coords in the screen buffer.
            // TODO CHECK IF IN SCREEN 
            draw_line(v1x_, v1y_, v2x_, v2y_, '~');
       }
   }
   
   

  show_screen();
   
    timer_pause(50);
   
   } // end loop over angles
   
   
    sprite_delete(&sprite);
    
    return 0;   
 
}
