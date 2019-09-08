#pragma once


#include <stdint.h>
#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h>

#include "sprite3d.h"
#include "string.h"


typedef struct {
    double ** vertices; // points of a vertex in local coord frame 
    unsigned int vertex_count;
    unsigned int ** facets; // a facet references the indices of vertices. Only supports triangular facets.
    unsigned int facet_count; 
    // TODO transformation matrix 
    // TODO velocity 
} sprite3d;

// State machine for obj parser
enum parser_state {look_for_newline, inspect_first_char, decode_vertex, decode_facet, done};

// Input: pointer to 3d sprite, and absolute path to mesh
// Side effect: populates the sprite with vertex and facet lists
int sprite_init(sprite3d * sprite, char * filename);

// Prints data about the sprite
void print_sprite3d(sprite3d * sprite);

// Free sprite
int sprite_delete(sprite3d * sprite);



