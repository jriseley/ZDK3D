% Wireframe renderer.

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

%
% Simple case to start with - just try and draw every vertex in the
% image plane.

% Image plane width and height in pixels
width = 300;
height = 220;

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

% Loop over all vertices in the mesh and print their location in world
% coords

% Locations
% Clear screen buffer
figure(1)

SPACING = 0.05; % spacing for interpolation(lazy line rendering) [m]


% Load an image for flair

logo = imread("logo.png");
logo = sum(logo,3);
logo = logo/max(logo(:));

logo_width = size(logo,2);
logo_height = size(logo,1);

for j=0:0.1:2*pi
    
    screen_buffer = zeros(height,width); %(v,u)
     screen_buffer(5:logo_height+4, 5:logo_width+4) = logo;
     
    a = pi/2 + cos(j)*1/11;
    theta = -pi/2*7/6 ;
    tau = cos(j)*5/11;
    x = cos(j);
    y = 1;
    z = 6;
    
    T_obj = [-sin(theta)*sin(a)*cos(tau) + cos(theta)*sin(tau),...
        sin(theta)*sin(a)*sin(tau) + cos(theta)*cos(tau),...
        sin(theta)*cos(a), x;
        cos(theta)*sin(a)*cos(tau) + sin(theta)*sin(tau),...
        -cos(theta)*sin(a)*sin(tau)+sin(theta)*cos(tau),...
        -cos(theta)*cos(a), y;
        -cos(a)*cos(tau), cos(a)*sin(tau), -sin(a), z;
        0, 0, 0, 1];
    

    % For each face...
    for i=1:length(obj.f.v)
        % For each pair of vertices in the face...
        face = obj.f.v{i};
        for j=1:length(face)
            
            % Get the two vertices
            vertex_1_i = face(j);
            if j+1 > length(face)
                vertex_2_i = face(1);
            else
                vertex_2_i = face(j+1);
            end
            
            % Extract the local coord frame points of these vertices.
            vertex_1 = obj.v(vertex_1_i,:);
            vertex_2 = obj.v(vertex_2_i,:);
            
            % Convert to world coords.
            v_1 = [vertex_1';1];
            v_2 = [vertex_2';1];
            v_1 = T_obj*v_1;
            v_2 = T_obj*v_2;
            
            % Get a set of points interpolated between these two.
            % Distance between points
            dist = sqrt((v_1(1)-v_2(1))^2+(v_1(2)-v_2(2))^2+(v_1(3)-v_2(3))^2);
            
            
            if dist > SPACING
                
                % Figure out how many points to put between them
                num_interpolated_points = ceil(dist/SPACING);
                
                % Get spacing in each dimension
                spacing = (v_2 - v_1)/num_interpolated_points;
                
                % Get points on line
                xes = v_1(1):spacing(1):v_2(1);
                ys = v_1(2):spacing(2):v_2(2);
                zs = v_1(3):spacing(3):v_2(3);
                
                % If some points are in same.. place..
                if isempty(xes)
                    xes = repmat(v_1(1), num_interpolated_points+1,1);
                end
                if isempty(ys)
                    ys = repmat(v_1(2), num_interpolated_points+1,1);
                end
                if isempty(zs)
                    zs = repmat(v_1(3), num_interpolated_points+1,1);
                end
                
            else
                xes = [v_1(1),v_2(1)];
                ys = [v_1(2),v_2(2)];
                zs = [v_1(3),v_2(3)];
            end
            
            % Render each point.
            for k=1:length(xes)
                point = [xes(k), ys(k), zs(k), 1]';
                
                %    % Project into image plane
                x_p = f0*point(1)/point(3); % x location of point in image plane, in a reference frame centre in image plane
                y_p = f0*point(2)/point(3);
                
                % convert to u,v
                x_p = x_p + w_plane/2;
                y_p = y_p + h_plane/2;
                u = x_p*pix_per_m;
                v = y_p*pix_per_m;
                
                u = round(u);
                v = round(v);
                % take nearest integer and store
                if u>0 && v>0 && u<width &&v<height
                    screen_buffer(v,u)=1;
                end
            end
        end
    end
    
    % Copy logo into buffer
    
   
    
    imagesc(screen_buffer)
    
    pause(0.1)
    
end

%% 4x4 matrix product
syms a b c d e f g h i j k l m n o p q r s t u v w x y z a2 b2 c2 d2 e2 ;

A = [a b c d;
    e f g h;
    i j k l;
    l m n o];

B = [p q r s;
    t u v w;
    x y z a2;
    b2 c2 d2 e2];

A*B

%% Figure out the transformation of taking one frame and
% translating it x, y, z and rotating a, b g

syms a b g x y z
syms T00 T01 T02 T03 T10 T11 T12 T13 T20 T21 T22 T23;
A = [T00 T01 T02 T03;
    T10 T11 T12 T13;
    T20 T21 T22 T23;
    0 0 0 1];

T = [-sin(b)*sin(a)*cos(g) + cos(b)*sin(g), sin(b)*sin(a)*sin(g) + cos(b)*cos(g), sin(b)*cos(a), x;
        cos(b)*sin(a)*cos(g) + sin(b)*sin(g), -cos(b)*sin(a)*sin(g)+sin(b)*cos(g), -cos(b)*cos(a), y;
        -cos(a)*cos(g), cos(a)*sin(g), -sin(a), z;
        0, 0, 0, 1];
    
result = T*A;

%% Get the expression for a point in a new ref frame
clear all
syms a b g x y z
syms T00 T01 T02 T03 T10 T11 T12 T13 T20 T21 T22 T23;
A = [T00 T01 T02 T03;
    T10 T11 T12 T13;
    T20 T21 T22 T23;
    0 0 0 1];
X = [x; y; z; 1];

result = A*X
