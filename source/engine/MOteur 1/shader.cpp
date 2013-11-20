/**
 *
 * @file   shader.cpp
 * @author Jerome Baril
 * @email  jerome.baril@labri.fr
 *
 */


#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;


string
Shader::shaderFileRead ( const string& filename )
{
    ifstream fichier(filename.c_str());
    stringstream buffer;

    if ( fichier )
    {
        buffer << fichier.rdbuf();
        fichier.close();
    }

    return buffer.str();
}


void
Shader::checkShaderCompilationError ( const GLuint shader )
{
    GLint compile;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compile);

    if (! compile )
    {
        GLint infologLength = 0;
        GLsizei charsWritten  = 0;
        char *infoLog;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

        string infoLogStr;
        if (infologLength > 0)
        {
            infoLog = new char[infologLength];
            glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
            infoLogStr = string(infoLog);
            delete [] infoLog;
        }
        throw ShaderException("shader compilation error \n" + infoLogStr );
    }
}


void
Shader::checkProgramLinkageError ( const GLuint program )
{
    GLint link;
    glGetProgramiv(program, GL_LINK_STATUS, &link);

    if (! link )
    {
        GLint infologLength = 0;
        GLsizei charsWritten  = 0;
        char *infoLog;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);

        string infoLogStr;
        if (infologLength > 0)
        {
            infoLog = new char[infologLength];
            glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
            infoLogStr = string(infoLog);
            delete [] infoLog;
        }
        throw ShaderException("shader program link error \n" + infoLogStr );
    }
}


GLuint
Shader::loadShader ( const string& vfile, const string& ffile )
{
    // create vertex and fragment shader
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

    // read source
    string vsrc = Shader::shaderFileRead(vfile);
    string fsrc = Shader::shaderFileRead(ffile);

    const char* cvsrc = vsrc.c_str();
    const char* cfsrc = fsrc.c_str();

//    std::cout << "vertex " << std::endl;
//    std::cout << vsrc << std::endl;

//    std::cout << "fragment " << std::endl;
//    std::cout << fsrc << std::endl;

    // associate shader and source
    glShaderSource( vshader, 1, &cvsrc, NULL );
    glShaderSource( fshader, 1, &cfsrc, NULL );

    // Compile vertex and fragment shader
    glCompileShader(vshader);
    glCompileShader(fshader);

    // Check compilation error
    Shader::checkShaderCompilationError(vshader);
    Shader::checkShaderCompilationError(fshader);

    // create program
    GLuint shaderProgram = glCreateProgram();

    // attach shader
    glAttachShader(shaderProgram,vshader);
    glAttachShader(shaderProgram,fshader);

    // link
    glLinkProgram(shaderProgram);

    // check linkage error
    Shader::checkProgramLinkageError(shaderProgram);

    return shaderProgram;
}
