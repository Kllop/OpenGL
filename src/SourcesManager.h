#pragma once

#include <string>
#include <memory>
#include <glad/glad.h>

namespace Renderer
{
    class ShaderProgram;
}

class SourcesManager
{
public:
    SourcesManager(const std::string& executablePath);
    ~SourcesManager() = default;

    SourcesManager(const SourcesManager&) =  delete;
    SourcesManager(SourcesManager&&) =  delete;
    SourcesManager& operator = (const SourcesManager&) = delete;
    SourcesManager& operator = (const SourcesManager&&) = delete;

    std::string getShaderFile(const std::string& shaderPath);
    std::string getTypeString(const GLint& type) const;

private:
    std::string m_Path;
    std::string getFileString(const std::string& relativePath) const; 
};
