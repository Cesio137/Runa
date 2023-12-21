#pragma once

namespace Nanometro
{
    /* OpenGL */
    static bool AUTO_SELECT_OPENGL = true;
    static int OPENGL_MAJOR_VERSION = 3;
    static int OPENGL_MINOR_VERSION = 3;

    static inline void OpenGL_EnableAutoSelect(bool value)
    {
        AUTO_SELECT_OPENGL = value;
    }

    static void OpenGL_SetMinorSupportedVersion(int MAJOR, int MINOR)
    {
        OPENGL_MAJOR_VERSION = MAJOR;
        OPENGL_MINOR_VERSION = MINOR;
    }
}
