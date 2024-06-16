#pragma once

namespace Nanometro
{
    /* OpenGL */
    static int AUTO_SELECT_OPENGL = 1;
    static int OPENGL_MAJOR_VERSION = 3;
    static int OPENGL_MINOR_VERSION = 3;

    static void Opengl_EnableAutoSelect(int value)
    {
        AUTO_SELECT_OPENGL = value;
    }
    static void Opengl_SetMinorSupportedVersion(int MAJOR, int MINOR)
    {
        OPENGL_MAJOR_VERSION = MAJOR;
        OPENGL_MINOR_VERSION = MINOR;
    }

}
