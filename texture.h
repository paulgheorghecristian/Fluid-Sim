#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>

class Texture
{
    public:
        Texture (std::string);
        Texture (GLuint);
        Texture (GLint internalFormat,
                 GLsizei width,
                 GLsizei height,
                 GLenum format,
                 GLenum type,
                 const GLvoid *data);
        GLuint &get_texture_id ();
        virtual ~Texture ();
        void use (unsigned int);
        void bind ();
        void unbind ();
    protected:
    private:
        GLuint texture_id;
};

#endif // TEXTURE_H
