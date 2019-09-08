% Proof of concept: a 3d mesh renderer using low-resolution
% bitmap graphics.
% Eg screen width, height of 100,60 or similar.
% Simply deposits a dark pixel wherever a vertex appears in the image
% plane,
% then rotates the mesh around.

clear all close all clc

% "Hey @Emily Corser I've got next semester's cab202 assignment ready for
% you. Now, I know this looks a smidge trickier than previous assignments
% but honestly the hardest part will be installing CUDA, it's all  downhill from
% there

% What units of measurement to use?

% Find a sprite to render.
% Does MATLAB load sprites?

obj = readObj("Arwing_001.obj");
%
% OUTPUT: obj.v - mesh vertices
%       : obj.vt - texture coordinates
%       : obj.vn - normal coordinates
%       : obj.f - face definition assuming faces are made of of 3 vertices

%%

% Simple case to start with - just try and draw every vertex in the
% image plane.

% Image plane width and height in pixels
width = 100;
height = 60;

% Construct a screen grid.
screen_buffer = zeros(height,width); %(v,u)

% Use image pixel coordinates. (0,0) top left. [u,v] where u increases to left,
% v increases downwards.

% World coordinates are different. 
% We need homogeneous transforms.
% World, camera, and object all have their own reference frames.
% We need a camera position, a distance from camera to image plane,
% An image plane size (in metres), 
% and object local coord frame.

% Actually start by assuming the camera is at the origin.
pix_per_m = 60;

% Width of image plane in metres
w_plane = width/pix_per_m; %[m]
h_plane = height/pix_per_m; %[m]

% Distance to image plane from camera (focal distance)
f0 = 3;

% Transformation to go from object coords to world


%T_obj = [cos(a)*cos(b), cos(a)*sin(b)*sin(c) - sin(a)*cos(c), cos(a)*sin(b)*cos(c) + sin(a)*sin(c), x;
%    sin(a)*cos(b), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), sin(a)*sin(b)*cos(c) - cos(a)*sin(c), y;
%    -sin(b), cos(b)*sin(c), cos(b)*cos(c), z;
%    0, 0, 0, 1];


% Loop over all vertices in the mesh and print their location in world
% coords

% Locations
% Clear screen buffer
figure(1)

for j=0:0.1:6*pi

screen_buffer = zeros(height,width); %(v,u)

a = j;
theta = j;
tau = j;
x = 0;
y = 0;
z = 20;

T_obj = [-sin(theta)*sin(a)*cos(tau) + cos(theta)*sin(tau),...
sin(theta)*sin(a)*sin(tau) + cos(theta)*cos(tau),...
sin(theta)*cos(a), x;
cos(theta)*sin(a)*cos(tau) + sin(theta)*sin(tau),...
-cos(theta)*sin(a)*sin(tau)+sin(theta)*cos(tau),...
-cos(theta)*cos(a), y;
-cos(a)*cos(tau), cos(a)*sin(tau), -sin(a), z;
0, 0, 0, 1];

for i=1:length(obj.v)

   v_i = obj.v(i,:); % the ith vertex
   
   % Put this point into homogeneous coords
   v_i = [v_i';1];
   
   % Put it into world coords
   v_i = T_obj*v_i;
   
   % Project into image plane
   % TODO
   x_p = f0*v_i(1)/v_i(3); % x location of point in image plane, in a reference frame centre in image plane
   y_p = f0*v_i(2)/v_i(3);

   % convert to u,v
   x_p = x_p + w_plane/2;
   y_p = y_p + h_plane/2;
   
   u = x_p*pix_per_m;
   v = y_p*pix_per_m;
   
   disp(v_i) 
   disp(u)
   disp(v)
   
   u = round(u);
   v = round(v);
   % take nearest integer and store
   if u>0 && v>0 && u<width &&v<height
    screen_buffer(v,u)=1;
   end
    % TODO
end

imagesc(screen_buffer)

pause(0.3)

end

%%

