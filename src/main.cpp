#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <string>

#include "SourcesManager.h"
#include "../src/Loader/OBJLoader.h"

float positionData[] = {
    -0.8f, -0.8f, 0.0f,
	 0.8f, -0.8f, 0.0f,
	 0.0f,  0.8f, 0.0f};

float ColorData[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f};

int main(int argc, char** argv)
{
	//Проверка библеотеки GLFW
	if (!glfwInit())
	{
		std::cout<<"glfwInit failed"<<std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//Создание окна
	GLFWwindow* pWindow = glfwCreateWindow(640, 480, "MyWindow", nullptr, nullptr);
	glfwMakeContextCurrent(pWindow);

	//Проверка окна
	if (!pWindow)
	{
		std::cout<<"CreatWindow Failed"<<std::endl;
		glfwTerminate();
		return -1;
	}

	//Проверка библеотеки GLAD
	if(!gladLoadGL())
	{
		std::cout << "Eror Glad" << std::endl;
		return -1;
	}
	
	SourcesManager resourcesManager(argv[0]);
	OBJLoader objload;

	//Выделения память для создания VertexShader
	GLint vertShader = glCreateShader( GL_VERTEX_SHADER);
	if (0==vertShader)
	{
		std::cout <<  "Error creating vertex shader" << std::endl;
		return -1;
	}

	const std::string vertexShader = resourcesManager.getShaderFile("res/shaders/VertexShader.txt");
	const GLchar* vertCode = {vertexShader.c_str()};

	//Загрузка в выделеную память VertexShader
	glShaderSource(vertShader, 1, &vertCode, nullptr);

	//Компиляция шейдера
	glCompileShader(vertShader);
	{
		GLint result; 
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
		if(GL_FALSE == result)
		{
			std::cerr << "Vertex shader compilation failed!" << std::endl;
			return -1;
		}
	}

	//Выделения память для создания FragmentShader
	GLint fragShader = glCreateShader( GL_FRAGMENT_SHADER);
	if (0 == fragShader)
	{
		std::cout <<  "Error creating fragment shader" << std::endl;
		return -1;
	}

	const std::string fragmentShader = resourcesManager.getShaderFile("res/shaders/FragmentShader.txt");
	const GLchar* fragCode = {fragmentShader.c_str()};
	const std::string ObjFile = resourcesManager.getShaderFile("res/object/box.obj");
	objload.FileLoader(ObjFile);
	

	//Загрузка в выделеную память FragmentShader
	glShaderSource(fragShader, 1, &fragCode, nullptr);

	//Компиляция шейдера
	glCompileShader(fragShader);
	{
		GLint result; 
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
	
		if(GL_FALSE == result)
		{
			std::cerr << "Fragment shader compilation failed!" << std::endl;
			return -1;
		}
	}

	//Выделяем память для шейдерного обьекта
	GLuint programHandle = glCreateProgram();
	if(0 == programHandle)
	{
		std::cerr << "Error creating program object" << std::endl;
		return -1;
	}

	//Задаем цвет очистки экрана
	glClearColor(0.4f, 0.4f, 0.4f, 1);

	//Загружаем в шейдерный обьект Vertex Shader
	glAttachShader(programHandle, vertShader);

	//Загружаем в шейдерный обьект Fragment Shader
	glAttachShader(programHandle, fragShader);

	//Стыкуем шейдеры между собой
	glLinkProgram(programHandle);
	{
		GLint status;  
		glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::cerr << "Failed to link shader program" << std::endl;
			return -1;
		}
	}
	//Делаем активным шейдерный обьект
	glUseProgram(programHandle);

	GLuint vaoHandle;
	GLuint vboHandles[2];

	//Создание двух буферных обьектов
	glGenBuffers(2, vboHandles);

	//Дескрипторы(Сылки для обрашения) в отдельные переменые
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];

	//Связывание буферного обьекта с точкой привязки(GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);

	//Загружем в буффер масив Vertex указывая его размерность****GL_STATIC_DRAW(Говорит OpenGL куда лучше положить наши данные)
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), positionData, GL_STATIC_DRAW);

	//Связывание буферного обьекта с точкой привязки(GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);

	//Загружем в буффер масив Color(RGB) указывая его размерность****GL_STATIC_DRAW(Говорит OpenGL куда лучше положить наши данные)
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), ColorData, GL_STATIC_DRAW);

	//Создание обьекта массива вершин(VAO)
	glGenVertexArrays(1, &vaoHandle);

	//Делаем активным VAO
	glBindVertexArray(vaoHandle);

	//Активация атбирутов вершин
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//Связывание буферного обьекта с точкой привязки(GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);

	//Сапоставление индекса соответствиеищим данным
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Связывание буферного обьекта с точкой привязки(GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);

	//Сапоставление индекса соответствиеищим данным
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Цикл отрисовки кадра
	while(!glfwWindowShouldClose(pWindow))
	{
		//Очишаем экран цветом
		glClear(GL_COLOR_BUFFER_BIT);

		//Установка связи с VAO
		glBindVertexArray(vaoHandle);

		//Инициализирует вывод примитивов выполняя обход по всему буферу
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Отображение на экран буфера 
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}