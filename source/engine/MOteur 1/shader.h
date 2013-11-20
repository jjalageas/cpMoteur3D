#ifndef SHADERS_H
#define SHADERS_H

/**
 *
 * @file   shader.h
 * @author Jerome Baril
 * @email  jerome.baril@labri.fr
 *
 */
// OpenGL platform species
#ifdef _WIN64

#elif _WIN32
#include <windows.h>

#elif __APPLE__
#include <GL/glew.h>
#include<GLUT/glut.h>
#include<GL/glu.h>
#include <OpenGL/gl.h>
#include <GL/glext.h>

#else //Linux
#include <GL/glew.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include <GL/gl.h>
#include <GL/glext.h>

#endif

#include <iostream>
#include <string>


class ShaderException
{
    public :
        ShaderException (const std::string & msg) : message (msg)
          {}
        virtual  ~ShaderException ()
            {}
        const std::string getMessage () const
            { return "[ShaderException] " + message; }
    private:
        std::string message;
};


class Shader
{
    public:

        static std::string shaderFileRead ( const std::string& filename );
        static void checkShaderCompilationError ( const GLuint shader );
        static void checkProgramLinkageError ( const GLuint program );

        static GLuint loadShader ( const std::string& vfile, const std::string& ffile );

};



#endif
