#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>
#include <vector>
#include <random>

#include <GL/glew.h>

#include <utility.h>


std::vector<GLuint> program_list;

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	program_list.push_back(ProgramID);

	return ProgramID;
}

GLuint GetShaderProgram(int index){
	return program_list[index];
}

GLuint GetGLTexID(){
	GLuint tex_id;
	glGenTextures(1, &tex_id);
	return tex_id;
}

void BindBlankTexture(){
	static bool initialised = false;
	static GLuint blank_texture;
	if(!initialised){
		std::cout << "Binding blank texture" << std::endl;
    	glGenTextures(1, &blank_texture);
		glBindTexture(GL_TEXTURE_2D, blank_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		GLfloat blank_tex_data[] = {0.0f, 0.0f, 0.0f};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, blank_tex_data);
		initialised = true;
	}
	glBindTexture(GL_TEXTURE_2D, blank_texture);
}

glm::ivec2* GetRandomIntPoints(int num_points, int min_x, int max_x, int min_y, int max_y){
	static std::random_device rd;
	static std::mt19937 rng(rd());
	std::uniform_int_distribution<int> x_gen(min_x, max_x);
	std::uniform_int_distribution<int> y_gen(min_y, max_y);

	glm::ivec2* points = new glm::ivec2[num_points];

	for(int i = 0; i < num_points; i++){
		int x = x_gen(rng);
		int y = y_gen(rng);
		points[i] = glm::ivec2(x, y);
	}

	return points;
};

bool rand_seeded = false;
float* GetRandomFloats(int num){
	if(!rand_seeded){
		srand(time(NULL));
		rand_seeded = true;
	}
	float* floats = new float[num];

	for(int i = 0; i < num; i++){
		floats[i] = rand();
	}
	return floats;
}

glm::vec3* GetRandomColours(int num_colours){
	if(!rand_seeded){
		srand(time(NULL));
		rand_seeded = true;
	}
	glm::vec3* colours = new glm::vec3[num_colours];
	for(int i = 0; i < num_colours; i++){
		colours[i] = glm::vec3(rand()/2, rand()/2, rand()/2);
	}
	return colours;
};

glm::vec3* GetRandomHues(int num_colours, float saturation, float value){
	if(!rand_seeded){
		srand(time(NULL));
		rand_seeded = true;
	}
	glm::vec3* colours = new glm::vec3[num_colours];
	for(int i = 0; i < num_colours; i++){
		colours[i] = glm::vec3((float)rand()/RAND_MAX, saturation, value);
	}
	return colours;
};

glm::vec3 ConvertHSVtoRGB(glm::vec3 hsv_colour){

	float h = hsv_colour.x;
	float s = hsv_colour.y;
	float v = hsv_colour.z;

	if(s == 0.0f){
		return glm::vec3(hsv_colour.z);
	}
	int i = (int)(h*6);
	float f = (h*6)-i;
	float p = v*(1.0f-s);
	float q = v*(1.0f-s*f);
	float t = v*(1.0f-s*(1.0f-f));
    i %= 6;
	switch (i){
		case 0:
			return glm::vec3(v, t, p);
		case 1:
			return glm::vec3(q, v, p);
		case 2:
			return glm::vec3(p, v, t);
		case 3:
			return glm::vec3(p, q, v);
		case 4:
			return glm::vec3(t, p, v);
		case 5:
			return glm::vec3(v, p, q);
	}
}