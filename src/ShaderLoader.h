//
// Created by Robert on 18.10.2022.
//

#ifndef CGE_SHADERLOADER_H
#define CGE_SHADERLOADER_H

#include <map>
#include <vector>
#include <glad/glad.h>

class ShaderLoader {
protected:
    ShaderLoader()
    {
        shaderNumber = 0;
    }

    static ShaderLoader* singleton_;
    static int shaderNumber;

    std::map<int, GLuint> shaderPrograms;
    std::vector<GLuint> shaderStack;
public:

    enum ShaderType { VERTEX, FRAGMENT };

    void LoadShaderSource(ShaderType type, const char* source);
    int CreateProgramFromLoadedSources();
    void DeleteAllPrograms();

    virtual ~ShaderLoader();

    /**
     * ShaderLoaders should not be cloneable.
     */
    ShaderLoader(ShaderLoader &other) = delete;
    /**
     * ShaderLoaders should not be assignable.
     */
    void operator=(const ShaderLoader &) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static ShaderLoader *GetInstance();

};


#endif //CGE_SHADERLOADER_H
