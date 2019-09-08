typedef struct {
    double x;
    double y;
    double z;
    double a;
    double b;
    double g;
} coordsys;

// TODO rotate
void rotate_frame(coordsys * frame, double a, double b, double gamma);

// TODO slide
void translate_frame(coordsys * frame, double x, double y, double z);

// Take the point in the reference frame 'frame' and put it into the world frame
void transform_point(coordsys * frame, double x, double y, double z);

// Take the point in the world reference frame and put it into the coord system 'frame'
void inv_transform_point(coordsys * frame, double x, double y, double z);

void print_frame(coordsys * frame);

