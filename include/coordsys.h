#pragma once 

#include <stdlib.h>
#include <stdio.h>

// A 4x4 homogeneous transformation matrix.
// Bottom row of [0];1 has been omitted in storage for brevity.
typedef double ** T_mat;

// A coordinate system with its own frame of reference,
// velocity and acceleration.
typedef struct {
    T_mat transform; 
    // TODO add velocity 
} ref_frame;


// Return a pointer to a fresh reference frame 
ref_frame * init_ref_frame(void);

// Release the memory held by a reference frame 
int free_ref_frame(ref_frame * frame);

// Move the reference frame by x,y,z metres and pitch, roll, yaw degrees.
void transform_frame(ref_frame * frame, double x, double y, double z, double a, double b, double g);

// Take the point (x,y,z) in the reference frame 'frame' and put it into the world frame.
// Stores result in variables (x_,y_,z_).
void transform_point(ref_frame * frame, double x, double y, double z, double * x_, double * y_, double *z_);

// Take the point in the world reference frame and put it into the coord system 'frame'
// (Will involve computing inverse of frame)
void inv_transform_point(ref_frame * frame, double x, double y, double z);

void print_frame(ref_frame * frame);


