#include "texture-utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

our::Texture2D *our::texture_utils::empty(GLenum format, glm::ivec2 size)
{
    our::Texture2D *texture = new our::Texture2D();
    // TODO: (Req 11) Finish this function to create an empty texture with the given size and format
    texture->bind();    // binding the newly created texture using bind() funtion created in req5
    glTexStorage2D(GL_TEXTURE_2D, 1, format, size.x, size.y); // Allocate texture storage without initializing its contents
    // parametes:
    //  GL_TEXTURE_2D: Target texture
    //  1: Number of mipmap levels
    //  format: Specifies the internal format of the texture(the storage format for texels in the texture)
    //  size.x: width of the texture
    //  size.y: height of the texture
    return texture;
}

our::Texture2D *our::texture_utils::loadImage(const std::string &filename, bool generate_mipmap)
{
    glm::ivec2 size;
    int channels;
    // Since OpenGL puts the texture origin at the bottom left while images typically has the origin at the top left,
    // We need to till stb to flip images vertically after loading them
    stbi_set_flip_vertically_on_load(true);
    // Load image data and retrieve width, height and number of channels in the image
    // The last argument is the number of channels we want and it can have the following values:
    //- 0: Keep number of channels the same as in the image file
    //- 1: Grayscale only
    //- 2: Grayscale and Alpha
    //- 3: RGB
    //- 4: RGB and Alpha (RGBA)
    // Note: channels (the 4th argument) always returns the original number of channels in the file
    unsigned char *pixels = stbi_load(filename.c_str(), &size.x, &size.y, &channels, 4);
    if (pixels == nullptr)
    {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return nullptr;
    }
    // Create a texture
    our::Texture2D *texture = new our::Texture2D();
    // Bind the texture such that we upload the image data to its storage
    texture->bind();
    // TODO: (Req 5) Finish this function to fill the texture with the data found in "pixels"
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)pixels);
    // here we have the texture data in RAM in CPU, this line sends this data to GPU
    // GL_TEXTURE_2D -->the texture being modified is a 2D texture.
    // 0--> mimap level
    // GL_RGBA8--> Each texel is composed of four components (red, green, blue, alpha) and each component is stored as an 8-bit unsigned integer.
    // size.x and size.y-->width and height of the texture
    // 0--> the border width of the texture (must be 0)
    // GL_RGBA-->the format of the pixel data
    // GL_UNSIGNED_BYTE-->the data type of the pixel data
    // (void *)pixel--> a pointer to the image data in memory. This is the actual pixel data of the texture.
    if (generate_mipmap)
        glGenerateMipmap(GL_TEXTURE_2D);
    // a mip level is a smaller version of the texture that's averaged in fewer pixels.
    // used when the whole details are not needed
    stbi_image_free(pixels); // Free image data after uploading to GPU
    return texture;
}