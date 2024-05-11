#version 330

uniform sampler2D tex;      // The texture holding the scene pixels
in vec2 tex_coord;          // Texture coordinates passed from the vertex shader
out vec4 frag_color;        // Output color of the pixel

uniform float time;         // Uniform to pass in the elapsed time
const float shake_intensity = 0.003; // Intensity of the shake

// Function to generate pseudo-random numbers
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
    // Generate a random offset based on time and texture coordinates
    vec2 random_offset = vec2(rand(tex_coord + time), rand(tex_coord - time)) * 2.0 - 1.0;
    random_offset *= shake_intensity;

    // Use the offset to alter the texture coordinates
    vec2 shaken_tex_coord = tex_coord + random_offset;

    // Sample the texture at the new coordinates
    frag_color = texture(tex, shaken_tex_coord);
}
