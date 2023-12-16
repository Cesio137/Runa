//
// Created by natha on 10/10/2023.
//

#ifndef NANOMETRO_RENDERINGCONFIG_H
#define NANOMETRO_RENDERINGCONFIG_H

/* OpenGL */
#define SDL_INIT_OPENGL 0
inline bool AUTO_SELECT_OPENGL = true;
inline int OPENGL_MAJOR_VERSION = 3;
inline int OPENGL_MINOR_VERSION = 3;

inline void OpenGL_EnableAutoSelect(bool value)
{
    AUTO_SELECT_OPENGL = value;
}

inline void OpenGL_SetMinorSupportedVersion(int MAJOR, int MINOR)
{
    OPENGL_MAJOR_VERSION = MAJOR;
    OPENGL_MINOR_VERSION = MINOR;
}

#endif //NANOMETRO_RENDERINGCONFIG_H
