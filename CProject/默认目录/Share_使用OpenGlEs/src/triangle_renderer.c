#include "triangle_renderer.h"
#include <math.h>


#include <GLES2/gl2.h>
// OpenGL ES 2.0 uses shaders
const char *VERTEX_SHADER =
	"attribute vec4 position;\n"
	"attribute vec4 color;\n"
	"varying vec4 vcolor;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.xyz, 1.0);\n"
	"vcolor = color;\n"
	"}";

const char *FRAGMENT_SHADER =
	"precision mediump float;\n"
	"varying vec4 vcolor;\n"
	"void main()\n"
	"{\n"
	"gl_FragColor = vec4 (vcolor.xyz, 1.0);\n"
	"}";

static GLfloat vertexes[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};
static GLfloat colors[12] = {};

void triangle_init()
{
	// 加载着色器
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &VERTEX_SHADER, NULL);
	glCompileShader(vertex);

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &FRAGMENT_SHADER, NULL);
	glCompileShader(fragment);

	// 将着色器合并到程序中
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	// Use it
	glUseProgram(program);

	// 将点位置属性指向顶点
	GLint position = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, vertexes);
	// 将颜色属性设置为颜色
	GLint color = glGetAttribLocation(program, "color");
	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, colors);

}

void triangle_render(double timemillis)
{
	// 设置颜色动画
	for (int i = 0; i < 3; i++)
	{
		colors[i * 4 + 0] = sin(i * M_PI * 2 / 3 + timemillis / 1000) / 2 + 0.5f;
		colors[i * 4 + 1] = sin((i + 1) * M_PI * 2 / 3 + timemillis / 1000) / 2 + 0.5f;
		colors[i * 4 + 2] = sin((i + 2) * M_PI * 2 / 3 + timemillis / 1000) / 2 + 0.5f;
		colors[i * 4 + 3] = 1.0f;
	}
	// 清除屏幕
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 绘制三角形
	glDrawArrays(GL_TRIANGLES, 0, 3);
}