#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include <iostream>

class Framebuffer
{
    public:
        Framebuffer(int width, int height);
        void bind();
        void unbind();
        void clear();
        GLuint get_texture_id();
        void swapTextures (GLuint &other);
        virtual ~Framebuffer();
    protected:
    private:
        int width, height;
        GLuint framebuffer_id;
        GLuint depthbuffer_id;
        GLuint texture_id;
        GLint viewport[4];
};

#endif // FRAMEBUFFER_H
