#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H
#include "GameInfo.h"
#include "HelpingHand.h"
#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//!The RenderTextureBase class is used to create a texture that you can render to. This is **not** a component
class RenderTextureBase {

public:
    RenderTextureBase() {}

    RenderTextureBase(const RenderTextureBase&) = delete;
    RenderTextureBase& operator=(const RenderTextureBase&) = delete;

    RenderTextureBase(RenderTextureBase&& other) noexcept
        : RenderTextureBase() {
        swap(*this, other);
        other.textureFBO  = 0;
        other.textureRBO  = 0;
        other.textureID   = 0;
        other.initialized = false;
    }

    RenderTextureBase& operator=(RenderTextureBase&& other) {
        if (this != &other) {
            freeGLIds();
            swap(*this, other);
        }
        return *this;
    }

    inline GLint getTextureID() const { return textureID; }
    inline GLuint getFBO() const { return textureFBO; }

    inline unsigned int getWidth() const { return width; }
    inline unsigned int getHeight() const { return height; }

    //!Initializes the texture
    virtual void initialize(unsigned int w, unsigned int h);

    //!Resizes the texture
    virtual void resize(unsigned int w, unsigned int h);

    virtual ~RenderTextureBase();

protected:
    //!Frees openGL id's
    void freeGLIds();

    unsigned int width  = 0;
    unsigned int height = 0;

    GLuint textureFBO = 0;
    GLuint textureID  = 0;
    GLuint textureRBO = 0;

    GLenum status    = 0;
    bool initialized = false;

    friend void swap(RenderTextureBase& first, RenderTextureBase& second) {
        std::swap(first.width, second.width);
        std::swap(first.height, second.height);
        std::swap(first.textureFBO, second.textureFBO);
        std::swap(first.textureID, second.textureID);
        std::swap(first.textureRBO, second.textureRBO);
        std::swap(first.status, second.status);
        std::swap(first.initialized, second.initialized);
    }
};

//!The RenderTexture class is used to create a texture that you can render to. This is a component.
class RenderTexture : public RenderTextureBase, public Component<RenderTexture> {
    virtual ~RenderTexture() {}
};

//!The RenderTextureMS class is used to create a multisampled texture that you can render to. This is a component.
class RenderTextureMS : public RenderTextureBase, public Component<RenderTextureMS> {

public:
    virtual ~RenderTextureMS() {}

    RenderTextureMS() {}

    RenderTextureMS(const RenderTextureMS&) = delete;
    RenderTextureMS& operator=(const RenderTextureMS&) = delete;

    RenderTextureMS(RenderTextureMS&& other) noexcept
        : RenderTextureMS() {

        //Call parent swap
        swap(*this, other);

        //swap derived variables
        std::swap(this->currentMultisamples, other.currentMultisamples);

        other.textureFBO  = 0;
        other.textureRBO  = 0;
        other.textureID   = 0;
        other.initialized = false;
    }
    RenderTextureMS& operator=(RenderTextureMS&& other) {
        if (this != &other) {
            freeGLIds();
            swap(*this, other);
            std::swap(this->currentMultisamples, other.currentMultisamples);
        }
        return *this;
    }

    //!Retrieves the max amount of multisamples the computer can handle if it hasn't already.
    static int getMaxMultisample();

    //!Resize the texture
    void resize(unsigned int w, unsigned int h);

    //!Resize the texture and set the multisamples
    void resize(unsigned int w, unsigned int h, unsigned int samples);

    //!Initialize
    void initialize(unsigned int w, unsigned int h);

    void initialize(unsigned int w, unsigned int h, unsigned int samples);

    inline int getCurrentMultisampleCount() const {
        return currentMultisamples > 0 ? currentMultisamples : 1;
    }

private:
    //!used for resizing.
    int currentMultisamples = -1;

    //!Doesn't check if samples are supported. (prevents recursion in getMaxMultisample()).
    void initializeUnsafe(unsigned int w, unsigned int h, unsigned int samples);
};

#endif
