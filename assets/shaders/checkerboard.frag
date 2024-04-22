#version 330 core

out vec4 frag_color;

// In this shader, we want to draw a checkboard where the size of each tile is (size x size).
// The color of the top-left most tile should be "colors[0]" and the 2 tiles adjacent to it
// should have the color "colors[1]".

//TODO: (Req 1) Finish this shader.

uniform int size = 32;
uniform vec3 colors[2];

void main(){
    // to ensure that each square of length 1 
    int x = int(gl_FragCoord.x) / size;
    int y = int(gl_FragCoord.y) / size;
    // according to the result of the expression (x+y)%2  ==> 0 or 1
    // so the checkerboard can be constructed 
    // as if the sum is even then this cell is of color[0]
    // and if the sum is odd then this cell is of color[1]
    frag_color = vec4(colors[(x+y)%2], 1.0);
}