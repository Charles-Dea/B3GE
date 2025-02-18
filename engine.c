#define GLFW_USE_WAYLAND OFF
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<stdint.h>
#include<stdio.h>
enum{
    SUCCESS=0,
    ERR_VERT_FAIL=1,
    ERR_FRAG_FAIL=2,
    ERR_GLFW_INIT_FAIL=3,
    ERR_GLFW_WIN_FAIL=4,
};
static GLFWwindow*__restrict win;
static uint32_t compshad(uint32_t,const char*__restrict);
int init(){
    if(glfwInit()<0)return ERR_GLFW_INIT_FAIL;
    glfwWindowHint(GLFW_RESIZABLE,0);
    win=glfwCreateWindow(600,600,"B3GE",0,0);
    if(!win)return ERR_GLFW_WIN_FAIL;
    glfwMakeContextCurrent(win);
    glewExperimental=1;
    glewInit();
    uint32_t shad=glCreateProgram();
    uint32_t vert=compshad(GL_VERTEX_SHADER,"shaders/vert.glsl");
    if(!vert)return ERR_VERT_FAIL;
    glAttachShader(shad,vert);
    uint32_t frag=compshad(GL_FRAGMENT_SHADER,"shaders/frag.glsl");
    if(!frag)return ERR_FRAG_FAIL;
    glAttachShader(shad,frag);
    glLinkProgram(shad);
    glUseProgram(shad);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0,0,0,1);
    return SUCCESS;
}
static uint32_t compshad(uint32_t type,const char*__restrict path){
    uint32_t shad=glCreateShader(type);
    FILE*file=fopen(path,"r");
    if(!file)return 0;
    fseek(file,0,SEEK_END);
    uint64_t len=ftell(file);
    fseek(file,0,SEEK_SET);
    char code[len+1];
    code[len]=0;
    fread(code,1,len,file);
    fclose(file);
    const char*c=code;
    glShaderSource(shad,1,&c,0);
    glCompileShader(shad);
    int32_t cmpd;
    glGetShaderiv(shad,GL_COMPILE_STATUS,&cmpd);
    return cmpd?shad:0;
}
void draw(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    uint32_t vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    float data[]={
        -.5,-.5,0,
        0,.5,0,
        .5,-.5,0
    };
    glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);
    uint32_t vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,0,12,0);
    glDrawArrays(GL_TRIANGLE_STRIP,0,3);
    glDisableVertexAttribArray(0);
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
    glfwSwapBuffers(win);
}
