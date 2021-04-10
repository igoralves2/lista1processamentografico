/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr'afico - Jogos Digitais - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 15/08/2020
 *
 */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>
#include <corecrt_math_defines.h>


// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int setupShader();
int setupShader3a();
int setupShader3b();
int setupGeometry4();
int setupGeometry();
int setupGeometry2();
int setupGeometry3a();
int setupGeometry3b();
int setupGeometry5();
int setupGeometry7a();
int setupGeometry7b();
int setupGeometry7c();
int setupGeometry7d();
// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar* vertexShaderSource = "#version 450\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* vertexShaderSource3a = "#version 450\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 cor;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"vertexColor = vec4(cor.x, cor.y, cor.z, 1);\n"
"}\0";

const GLchar* vertexShaderSource3b = "#version 450\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 cor;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"vertexColor = vec4(cor.x, cor.y, cor.z, 1);\n"
"}\0";

//Códifo fonte do Fragment Shader (em GLSL): ainda hardcoded
const GLchar* fragmentShaderSource = "#version 450\n"
"uniform vec4 inputColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = inputColor;\n"
"}\n\0";

const GLchar* fragmentShaderSource3a = "#version 450\n"
"in vec4 vertexColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vertexColor;\n"
"}\n\0";

const GLchar* fragmentShaderSource3b = "#version 450\n"
"in vec4 vertexColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vertexColor;\n"
"}\n\0";

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);




	int opcao = 8;
	/*
	do {
	cin >> opcao;
	} while (opcao <= 0 || opcao > 8);
	*/
	switch (opcao) {
	case 1: {
		//Exercício 1:
		GLuint shaderID = setupShader();
		GLuint VAO = setupGeometry();
		GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
		assert(colorLoc > -1);
		glUseProgram(shaderID);
		while (!glfwWindowShouldClose(window)) {

			glfwPollEvents();

			// Limpa o buffer de cor
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f); //cor de fundo
			glClear(GL_COLOR_BUFFER_BIT);

			glLineWidth(10);
			glPointSize(10);

			// Chamada de desenho - drawcall
			// Poligono Preenchido - GL_TRIANGLES
			glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Chamada de desenho - drawcall
			// CONTORNO - GL_LINE_LOOP

			glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
			glDrawArrays(GL_LINE_LOOP, 0, 3);

			glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
			glDrawArrays(GL_LINE_LOOP, 3, 3);
			glBindVertexArray(0);

			glfwSwapBuffers(window);

		}
		//Fim do exercício 1
		glDeleteVertexArrays(1, &VAO);
		glfwTerminate();
		break; }
	case 2: {
		//Exercício 2:
		GLuint shaderID = setupShader();
		GLuint VAO = setupGeometry2();
		GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
		assert(colorLoc > -1);
		glUseProgram(shaderID);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			glClearColor(0.3f, 0.3f, 0.3f, 1.0f); //cor de fundo
			glClear(GL_COLOR_BUFFER_BIT);

			glLineWidth(10);
			glPointSize(10);

			glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
			glUseProgram(shaderID);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);


			glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
			glDrawArrays(GL_LINE_LOOP, 3, 3);

			glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
			glDrawArrays(GL_POINTS, 6, 3);
			glBindVertexArray(0);
			break;
			//Fim do exercício 2

			glfwSwapBuffers(window);

		}
		glDeleteVertexArrays(1, &VAO);
		glfwTerminate();
		break;
	}
	case 3: {
		//Exercício 3a:
		GLuint shaderID = setupShader3a();
		GLuint VAO = setupGeometry3a();
		glUseProgram(shaderID);
		while (!glfwWindowShouldClose(window)) {

			glfwPollEvents();

			glClearColor(0.3f, 0.3f, 0.3f, 1.0f); //cor de fundo
			glClear(GL_COLOR_BUFFER_BIT);

			glPointSize(10);

			glUseProgram(shaderID);
			glBindVertexArray(VAO);
			glDrawArrays(GL_POINTS, 0, 3);
			glBindVertexArray(0);

			glfwSwapBuffers(window);

			//Fim do exercício 3a
		}
		glDeleteVertexArrays(1, &VAO);
		glfwTerminate();
		break; 
	}
	case 4: {
		//Exercício 3b:
		GLuint shaderID = setupShader3b();
		GLuint VAO = setupGeometry3b();
		glUseProgram(shaderID);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			glClearColor(0.3f, 0.3f, 0.3f, 1.0f); //cor de fundo
			glClear(GL_COLOR_BUFFER_BIT);

			glPointSize(10);

			glUseProgram(shaderID);
			glBindVertexArray(VAO);
			glDrawArrays(GL_POINTS, 0, 3);
			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAO);
		glfwTerminate();
		break; }
	case 5: {
		//Exercício 4:
		GLuint shaderID = setupShader();
		GLuint VAO = setupGeometry4();
		GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
		assert(colorLoc > -1);
		glUseProgram(shaderID);
		while (!glfwWindowShouldClose(window)) {

			glfwPollEvents();

			glClearColor(0.3f, 0.3f, 0.3f, 1.0f); //cor de fundo
			glClear(GL_COLOR_BUFFER_BIT);
			glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);

			glLineWidth(10);
			glPointSize(10);

			glUseProgram(shaderID);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAO);
		glfwTerminate();
		break; 
	}
	case 6: {
		//Exercício 5:
		GLuint shaderID = setupShader();
		GLuint VAO = setupGeometry5();
		GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
		assert(colorLoc > -1);
		glUseProgram(shaderID);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
			glUseProgram(shaderID);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 180 + 2);
			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAO);
		glfwTerminate();
		break; 
	}
	case 7: {/*
		GLuint shaderID = setupShader();
		GLuint VAO = setupGeometry5();
		GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
		assert(colorLoc > -1);
		glUseProgram(shaderID);
		//Exercício 6:
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();


			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAO);
		glfwTerminate();*/
		break; 
	}
	case 8: {
		//Exercício 7
		GLuint shaderID = setupShader();
		GLuint VAOtopleft = setupGeometry7a();
		GLuint VAOtopright = setupGeometry7b();
		GLuint VAObottomleft = setupGeometry7c();
		GLuint VAObottomright = setupGeometry7d();
		GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
		assert(colorLoc > -1);
		glUseProgram(shaderID);
		while (!glfwWindowShouldClose(window)) {

			glfwPollEvents();

			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glLineWidth(10);
			glPointSize(10);

			glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
			glBindVertexArray(VAOtopleft);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawArrays(GL_TRIANGLES, 1, 3);


			glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
			glBindVertexArray(VAOtopright);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawArrays(GL_TRIANGLES, 1, 3);
			glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
			glBindVertexArray(VAObottomleft);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawArrays(GL_TRIANGLES, 1, 3);

			glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
			glBindVertexArray(VAObottomright);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawArrays(GL_TRIANGLES, 1, 3);
			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAOtopleft);
		glDeleteVertexArrays(1, &VAOtopright);
		glDeleteVertexArrays(1, &VAObottomleft);
		glDeleteVertexArrays(1, &VAObottomright);
		glfwTerminate();
		break; }
	default:
		break;
	}
	
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

//Esta função está basntante hardcoded - objetivo é compilar e "buildar" um programa de
// shader simples e único neste exemplo de código
// O código fonte do vertex e fragment shader está nos arrays vertexShaderSource e
// fragmentShader source no iniçio deste arquivo
// A função retorna o identificador do programa de shader
int setupShader()
{
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int setupShader3a()
{
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource3a, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource3a, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int setupShader3b()
{
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource3b, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource3b, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

// Esta função está bastante harcoded - objetivo é criar os buffers que armazenam a 
// geometria de um triângulo
// Apenas atributo coordenada nos vértices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A função retorna o identificador do VAO
int setupGeometry()
{//Exercício 1
	GLfloat vertices[] = { -1, 0, 0, -0.5, 0, 0, -0.25, -0.5, 0, 1, 0, 0, 0.5, 0, 0, 0.25, 0.5, 0};
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0); 

	return VAO;
}

int setupGeometry2()
{//Exercício 2
	GLfloat vertices[] = { -1, 0, 0, -0.5, 0, 0, -0.25, -0.5, 0, 
		1, 0, 0, 0.5, 0, 0, 0.25, 0.5, 0,
		-1, -1, 0, -1, -0.5,0, -0.5, -0.5, 0};
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

int setupGeometry3a()
{//Exercício 3a				//Posição/Cor
	GLfloat vertices[] = {0, 0, 0, 1, 0, 0,
						0.5, 0, 0, 0, 1, 0,
						0.5, 0.5, 0, 0, 0, 1};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}

int setupGeometry3b()
{//Exercício 3b				//Posições
	GLfloat vertices[] = { 0, 0, 0,
						0.5, 0, 0,
						0.5, 0.5, 0 };
	GLfloat cores[] = {1,0,0,
						0,1,0,
						0,0,1};
	
	GLuint VBO, colorsVBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	
	
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cores, GL_STATIC_DRAW);
	
	
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	//incluindo o buffer de vértices:
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	//incluindo o buffer de cores:
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}

int setupGeometry5() {
	const GLint nroLados = 180;
	const GLint nroVertices = nroLados + 2;
	GLint radius = 1;
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;
	GLfloat twicepi = 2.0f * M_PI;
	GLfloat verticesX[nroVertices];
	GLfloat verticesY[nroVertices];
	GLfloat verticesZ[nroVertices];
	verticesX[0] = x;
	verticesY[0] = y;
	verticesZ[0] = z;
	for (int i = 1; i < nroVertices; i++) {
		verticesX[i] = x + (radius * cos(i * twicepi / nroLados));
		verticesY[i] = y + (radius * sin(i * twicepi / nroLados));
		verticesZ[i] = z;
	}GLfloat verticesCirculo[nroVertices * 3];
	for (int i = 0; i < nroVertices; i++) {
		verticesCirculo[i * 3] = verticesX[i];
		verticesCirculo[(i * 3) + 1] = verticesY[i];
		verticesCirculo[(i * 3) + 2] = verticesZ[i];
	}
	GLuint VAO, VBO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCirculo), verticesCirculo, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

int setupGeometry4() {
	GLfloat pontos[] = {0, 0, 0,//Bottom left
						1, 0, 0,//Bottom right
						0, 1, 0,//Top left
						1, 1, 0//Top right
	};
	GLuint indices[] = {
							0, 1, 2,	//top left triangle
							2, 1, 3		//bottom right triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pontos), pontos, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);
	return VAO;
}

int setupGeometry7a()
{//Exercício 1
	GLfloat vertices[] = {-0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f};
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

int setupGeometry7b()
{//Exercício 7
	GLfloat vertices[] = { 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f, 
		0.0f, 0.0f, 0.0f, 
		0.5f, 0.0f, 0.0f };
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

int setupGeometry7c()
{//Exercício 7
	GLfloat vertices[] = { -0.5f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 
		0.0f, -0.5f, 0.0f };
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

int setupGeometry7d()
{//Exercício 7
	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f, 
		0.5f, 0.0f, 0.0f, 
		0.0f, -0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f };
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}
