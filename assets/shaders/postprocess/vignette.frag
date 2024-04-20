#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

// Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;

out vec4 frag_color;

// Vignette is a postprocessing effect that darkens the corners of the screen
// to grab the attention of the viewer towards the center of the screen

void main(){
    //TODO: Modify this shader to apply vignette
    // To apply vignette, divide the scene color
    // by 1 + the squared length of the 2D pixel location the NDC space
    // Hint: remember that the NDC space ranges from -1 to 1
    // while the texture coordinate space ranges from 0 to 1
    // We have the pixel's texture coordinate, how can we compute its location in the NDC space?
    vec2 tex_coord_NDC = vec2(2.0 * tex_coord - 1.0);
    //here we apply the equation 2*tex_coord -1 to transform from texture coordinate space to NDC space
    //then stores the transoformed coordinates in tex_coord_NDC
    frag_color=texture(tex,tex_coord)/(1+pow(length(tex_coord_NDC),2));
    //texture(tex, tex_coord):gets the color from the texture tex at the texture coordinates tex_coord.
    // length(tex_coord_NDC):the length of the texture coordinates in NDC space. The length of a vector in 2D space represents its distance from the origin (0,0).
    // 1 + pow(length(tex_coord_NDC), 2): Adding 1 to the squared length ensures that the denominator is always greater than 1.
    // /(1 + pow(length(tex_coord_NDC), 2)): This divides the texture color by 1 + the squared length of the 2D pixel location the NDC space to apply vignette.
    // As the distance from the center increases, the denominator grows larger, causing the result of the division to approach 0, attenuating the texture color.
}