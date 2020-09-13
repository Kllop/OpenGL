#include "OBJLoader.h"

std::vector<double>* OBJLoader::FileLoader(const std::string& ObjFile)
{
    creatArrayObj(ObjFile);
    for (size_t i = 0; i < file.size(); i++)
    {
        if(file[i][0] != '#')
        {
           if(file[i][0] == 'v' && file[i][1] == ' ')
           {
               float tempx = 0, tempy = 0, tempz = 0;
               sscanf(file[i].c_str(),"v %f %f %f \n", &tempx, &tempy, &tempz);
			   std::cout << tempx << "," << tempy << "," << tempz << std::endl;
               vertex.push_back(glm::vec3(tempx, tempy, tempz));
           }
           else if(file[i][0] == 'v' && file[i][1] == 't')
           {
               float tempx = 0, tempy = 0;
               sscanf(file[i].c_str(),"vt %f %f", &tempx, &tempy);
               textCord.push_back(glm::vec2(tempx, tempy));
           }
           else if(file[i][0] == 'v' && file[i][1] == 'n')
           {
               float tempx = 0, tempy = 0,tempz = 0;
               sscanf(file[i].c_str(),"vn %f %f %f", &tempx, &tempy, &tempz);
               normals.push_back(glm::vec3(tempx, tempy, tempz));
           }
            else if(file[i][0] == 'f' && file[i][1] == ' ')
           {
               Face::vertex f1, f2, f3;
               sscanf(file[i].c_str(),"f %n/%n/%n %n/%n/%n %n/%n/%n", &f1.v_i, &f1.vt_i, &f1.vn_i, &f2.v_i, &f2.vt_i, &f2.vn_i, &f3.v_i, &f3.vt_i, &f3.vn_i);
               faces.push_back(Face(f1,f2,f3));
           }
        }
    }
    return nullptr;
}
void OBJLoader::creatArrayObj(const std::string& tempObjFile)
{
	std::string temp;
	int begin_i = 0;
    for (int i = 0; i < tempObjFile.size(); i++)
    {
        if(tempObjFile[i] == '\n')
		{
			file.push_back(tempObjFile.substr(begin_i, i - begin_i));
            begin_i = i+1;
        }
    }
}
