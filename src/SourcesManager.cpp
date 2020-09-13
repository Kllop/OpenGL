#include "SourcesManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

SourcesManager::SourcesManager(const std::string& executablePath)
{
    std::size_t found = executablePath.find_last_of("/\\");
    m_Path = executablePath.substr(0,found);
}
std::string SourcesManager::getFileString(const std::string& relativePath) const
{
    std::ifstream f;
    f.open(m_Path + "/" + relativePath, std::ios::in || std::ios::binary);
    if(!f.is_open())
    {
        std::cerr << "Faile open file: " << relativePath << std::endl;
        return std::string{};
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::string SourcesManager::getShaderFile(const std::string& shaderPath)
{
    return getFileString(shaderPath);
}
std::string SourcesManager::getTypeString(const GLint& type) const
{	
	switch (type)
	{
	case 35664:
		return std::string("vec2");
		break;
	case 35665:
		return std::string("vec3");
		break;
	case 35666:
		return std::string("vec4");
		break;
	case 35667:
		return std::string("vec2");
		break;
	case 35668:
		return std::string("vec3");
		break;
	case 35669:
		return std::string("vec4");
		break;
	case 35671:
		return std::string("vec2");
		break;
	case 35672:
		return std::string("vec3");
		break;
	case 35673:
		return std::string("vec3");
		break;
	default:
		return std::string();
		break;
	}
}

