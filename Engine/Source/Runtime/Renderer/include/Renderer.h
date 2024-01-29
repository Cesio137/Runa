#pragma once

#ifdef __cplusplus
namespace Nanometro
{
#endif
    /* OpenGL */
    static int AUTO_SELECT_OPENGL = 1;
    static int OPENGL_MAJOR_VERSION = 3;
    static int OPENGL_MINOR_VERSION = 3;

    void Opengl_EnableAutoSelect(int value);
    void Opengl_SetMinorSupportedVersion(int MAJOR, int MINOR);

#ifdef __cplusplus
}
#endif