#include "RenderLayer.h"

using namespace SouthwestEngine;

RenderLayer::RenderLayer() {
    Updated = 2; // for debug purposes
    Shader = nullptr;

	glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // create a color attachment texture
    glGenTextures(1, &_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 960, 540, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _tex, 0);
    // create a renderbuffer object for depth and stencil attachment
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 960, 540); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

RenderLayer::~RenderLayer() {

}

void RenderLayer::Draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i = 0; i < Drawables2D.size(); i++) {
        Drawables2D[i]->Draw();
    }

    for (unsigned int i = 0; i < Drawables3D.size(); i++) {
        Drawables3D[i]->Draw();
    }
}

void RenderLayer::Bind() {
    glBindTexture(GL_TEXTURE_2D, _tex);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
}