#pragma once
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>


std::string get_file_contents(const char* filename);

class Shader {
public:
	GLuint ID;
	Shader(std::string name);

	void Activate();
	void Delete();
	void compileErrors(unsigned int shader, const char* type);
};

