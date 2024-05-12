#ifndef RENDERINTERFACE_H
#define RENDERINTERFACE_H

#include "Opengl/SDL_Opengl.h"
#include <imgui.h>

namespace Nanometro {

    class RenderInterface
    {
    public:
        explicit RenderInterface(uint32_t flags);
        ~RenderInterface();

        int exec();

        virtual void PreInitialize(ImGuiIO& io){}
        virtual void Ready(){}
        virtual void EventHandle(SDL_Event event){};
        virtual void RenderImgui(double delta){}
        virtual void Render(double delta){}

        /*Application*/
        void CloseApp();

        /* SDL */
        std::pair<uint8_t, uint8_t> GetOpenglVersion() const;

        /* Errors */
        std::string GetErrorLog() const;
    private:
        /* Flags */
        uint32_t Flags = 0;

        /* SDL */
        SDL_Opengl Opengl;
        void Opengl_Render();
        /* SDL Events */
        bool WindowShouldClose = false;
    };

} // Nanometro

#endif //RENDERINTERFACE_H
