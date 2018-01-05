#include "framebuffer.h"

Framebuffer::Framebuffer (int width, int height) : width (width), height (height)
{
    glGetIntegerv(GL_VIEWPORT, viewport);

    //generare framebuffer
    glGenFramebuffers(1, &framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

    //genereaza textura pe care desenez scena
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glDrawBuffer (GL_COLOR_ATTACHMENT0);

    //alocare memorie pentru textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, (GLvoid *) 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);

    unbind();
}

void Framebuffer::swapTextures (GLuint &other) {
    GLuint aux;

    aux = other;
    other = texture_id;
    texture_id = aux;

    bind();
    glFramebufferTexture (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);
    unbind();
}

void Framebuffer::clear() {
    bind();
    glClearColor (0, 0, 0, 1);
    glClear (GL_COLOR_BUFFER_BIT);
    unbind();
}

void Framebuffer::bind() {
    glBindFramebuffer (GL_FRAMEBUFFER, framebuffer_id);
    glDrawBuffer (GL_COLOR_ATTACHMENT0);
    glBindTexture (GL_TEXTURE_2D, 0);
    glViewport(0, 0, width, height);
}

void Framebuffer::unbind() {
    glBindFramebuffer (GL_FRAMEBUFFER, 0);
    glBindTexture (GL_TEXTURE_2D, 0);
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

GLuint Framebuffer::get_texture_id(){
    return texture_id;
}

Framebuffer::~Framebuffer()
{

}
