
#include <ctype.h>
#include "sprite3d.h"

#define BUFSIZE (30)

int sprite_init(sprite3d * sprite, char * filename){

    FILE *fptr;
    
    printf("Reading file %s .. \n", filename);
    
    if ((fptr = fopen(filename,"r")) == NULL){
        exit(1);
    }

    char ch = ' '; 
    char xbuf[BUFSIZE]; char ybuf[BUFSIZE]; char zbuf[BUFSIZE];
    char junk[BUFSIZE];
    
    memset(xbuf, '\0', BUFSIZE); memset(ybuf, '\0', BUFSIZE); memset(zbuf, '\0', BUFSIZE);
    
    enum parser_state state = inspect_first_char; // state of parser
    
    unsigned int n_v = 0; // vertex count 
    unsigned int n_f = 0; // facet count
    
    // First count facets and vertices so we know how much space to allocate  
    while( fscanf(fptr,"%c", &ch)==1){
        if (ch == 'v'){
            fscanf(fptr,"%c", &ch);
            if (ch == ' ') n_v++;
        } else if (ch == 'f') n_f++;
    }
    
    printf("Num vertices: %d, num facets: %d\n",n_v,n_f);
    
    // Allocate space in the struct for vertices and facets
    sprite->vertices = malloc(n_v * sizeof(double *));
    for (unsigned int i=0; i<n_v; i++){
        (sprite->vertices[i]) = malloc(3*sizeof(double));
    }
    
    
    sprite->facets = malloc(n_f * sizeof(unsigned int *));
    for (unsigned int i=0; i<n_f; i++){
        (sprite->facets[i]) = malloc(3*sizeof(unsigned int));
    }
    
    sprite->vertex_count = n_v;
    sprite->facet_count = n_f;
    
    // Reset the file pointer to the start 
    rewind(fptr);
    
    // Get index for vertices and facets 
    unsigned int v_i = 0;
    unsigned int f_i = 0;
    
    // Populate the vertex and facet lists 
    while(state != done){
        
        //memset(xbuf, '\0', BUFSIZE); memset(ybuf, '\0', BUFSIZE); memset(zbuf, '\0', BUFSIZE);
        
        switch (state) {
            
            case inspect_first_char:
                fscanf(fptr,"%c", &ch);

                if(ch=='v'){
                    
                    fscanf(fptr,"%c", &ch); // disambiguate from vn and vt
                    
                    if(ch==' '){
                        state = decode_vertex;
                    } else if (feof(fptr)!=0){
                        state = done;   
                    } else{
                     state = look_for_newline;   
                    }
                }
                 else if (ch=='f') {
                        state = decode_facet; 
                } else if (feof(fptr)!=0){
                 state = done;   
                } else {
                        state = look_for_newline;
                } 
                break;
            
            case look_for_newline:
                
                if(feof(fptr)!=0){
                    state = done;
                } else {
                    fscanf(fptr,"%c", &ch);

                    if (ch=='\n'){
                    state = inspect_first_char;
                    } 
                }
                break;
                
            case decode_vertex:

               fscanf(fptr, "%s %s %s\n", xbuf,ybuf,zbuf);
               //printf("%s %s %s\n", xbuf,ybuf,zbuf);
               double x = atof(xbuf); double y = atof(ybuf); double z = atof(zbuf);
               
               // Store vertex coordinates 
               sprite->vertices[v_i][0] = x; sprite->vertices[v_i][1] = y; sprite->vertices[v_i][2] = z;
               
               // Increment location of next vertex 
               v_i++;
               
                // Switch back to looking for a new line 
                state = inspect_first_char;
                break;
                
            case decode_facet:
                

                fscanf(fptr, " %s %s %s\n", xbuf, ybuf, zbuf);
                //printf("%s %s %s\n", xbuf, ybuf, zbuf);
                
                char * bufs[3]; bufs[0] = xbuf; bufs[1] = ybuf; bufs[2] = zbuf;
                
                // Just extract the vertices comprising each facet (up to 3), ignore texture and normals for now
                char sep = '/';
                for (unsigned int i=0; i<3; i++){
                    unsigned int j=0;
                    while( bufs[i][j] != sep) j++;
                    bufs[i][j] = '\0';
                }
                
                //printf("%s %s %s\n",xbuf, ybuf, zbuf);
                state = look_for_newline;

                // Store the facet information
                for (unsigned int i=0; i<3; i++){
                    sprite->facets[f_i][i] = atof(bufs[i]);
                }
                
                // Increment location of next facet 
               f_i++;
               
               state = look_for_newline;
               
             break;
                
        } // end state machine switch
    } // end loop over file

    // Finished parsing, test reading some values 
    
    printf("Vertex count after finished %d\n",v_i);
    fclose(fptr);

    return 0;
}




void print_sprite3d(sprite3d * sprite){
    unsigned int n = sprite->vertex_count;    
    printf("Sprite with %d vertices\n",sprite->vertex_count);
    printf("\t%f %f %f,\n",sprite->vertices[0][0],sprite->vertices[0][1],sprite->vertices[0][2]);
    printf("\t%f %f %f \n\t...\n",sprite->vertices[1][0],sprite->vertices[1][1],sprite->vertices[1][2]);
    printf("\t%f %f %f \n",sprite->vertices[n-2][0],sprite->vertices[n-2][1],sprite->vertices[n-2][2]);
    printf("\t%f %f %f \n",sprite->vertices[n-1][0],sprite->vertices[n-1][1],sprite->vertices[n-1][2]);
    
    n = sprite->facet_count;    
    printf("Sprite with %d facets\n",sprite->facet_count);
    printf("\t%d %d %d,\n",sprite->facets[0][0],sprite->facets[0][1],sprite->facets[0][2]);
    printf("\t%d %d %d \n\t...\n",sprite->facets[1][0],sprite->facets[1][1],sprite->facets[1][2]);
    printf("\t%d %d %d \n",sprite->facets[n-2][0],sprite->facets[n-2][1],sprite->facets[n-2][2]);
    printf("\t%d %d %d \n",sprite->facets[n-1][0],sprite->facets[n-1][1],sprite->facets[n-1][2]);
    
    // TODO FACETS
    return;
    
}


int sprite_delete(sprite3d * sprite){
    
    unsigned int n_v = sprite->vertex_count;

    for (unsigned int i=0; i<n_v; i++){
        free(sprite->vertices[i]);
    }
    
    free(sprite->vertices);
}
