#define GLFW_USE_WAYLAND OFF
#define STB_IMAGE_IMPLEMENTATION
#ifndef __APPLE__
#include<GL/glew.h>
#else
#include<OpenGL/glew.h>
#endif
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
enum{
    SUCCESS=0,
    ERR_VERT_FAIL=-1,
    ERR_FRAG_FAIL=-2,
    ERR_GLFW_INIT_FAIL=-3,
    ERR_GLFW_WIN_FAIL=-4,
    ERR_LOAD_TEX_FAIL=-5,
    ERR_VERT_NOT_FOUND=-6,
    ERR_FRAG_NOT_FOUND=-7,
    ERR_FILE_NOT_FOUND=-8,
    ERR_COMPILE_FAIL=-9
};
typedef struct{
    double x,y,z;
    double w,h;
    int t;
}sprite_t;
static GLFWwindow*__restrict win;
static bool initialized;
static int32_t compshad(uint32_t,const char*__restrict);
int init(int32_t sl,const char*__restrict name){
    if(glfwInit()<0)return ERR_GLFW_INIT_FAIL;
    glfwWindowHint(GLFW_RESIZABLE,0);
    glfwWindowHint(GLFW_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_VERSION_MINOR,1);
    uint64_t len=strlen(name)+1;
    char*__restrict n=malloc(len);
    memcpy(n,name,len);
    win=glfwCreateWindow(sl,sl,n,0,0);
    if(!win)return ERR_GLFW_WIN_FAIL;
    glfwMakeContextCurrent(win);
    glewExperimental=1;
    glewInit();
    uint32_t shad=glCreateProgram();
    int32_t vert=compshad(GL_VERTEX_SHADER,"shaders/vert.glsl");
    if(vert==ERR_FILE_NOT_FOUND)return ERR_VERT_NOT_FOUND;
    if(vert==ERR_COMPILE_FAIL)return ERR_VERT_FAIL;
    glAttachShader(shad,vert);
    int32_t frag=compshad(GL_FRAGMENT_SHADER,"shaders/frag.glsl");
    if(frag==ERR_FILE_NOT_FOUND)return ERR_FRAG_NOT_FOUND;
    if(frag==ERR_COMPILE_FAIL)return ERR_FRAG_FAIL;
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
static int32_t compshad(uint32_t type,const char*__restrict path){
    uint32_t shad=glCreateShader(type);
    FILE*file=fopen(path,"r");
    if(!file)return ERR_FILE_NOT_FOUND;
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
    return cmpd?shad:ERR_COMPILE_FAIL;
}
int loadtex(const char*__restrict file){
    int32_t w,h,c;
    const uint8_t*__restrict img=stbi_load(file,&w,&h,&c,4);
    if(!img)return ERR_FILE_NOT_FOUND;
    uint32_t t;
    glGenTextures(1,&t);
    glBindTexture(GL_TEXTURE_2D,t);
    glTextureParameteri(t,GL_TEXTURE_MAX_LEVEL,0);
    glTextureParameteri(t,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTextureParameteri(t,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,img);
    return t;
}
void draw(const sprite_t*__restrict sprites,int nsprites){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<nsprites;i++){
        glBindTexture(GL_TEXTURE_2D,sprites[i].t);
        uint32_t vbo;
        glGenBuffers(1,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        double hw=sprites[i].w/2;
        double hh=sprites[i].h/2;
        double l=sprites[i].x-hw;
        double r=sprites[i].x+hw;
        double t=sprites[i].y+hh;
        double b=sprites[i].y-hh;
        float data[]={
            l,t,sprites[i].z,0,1,
            r,t,sprites[i].z,1,1,
            l,b,sprites[i].z,0,0,
            r,b,sprites[i].z,1,0
        };
        glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);
        uint32_t vao;
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,0,20,0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,2,GL_FLOAT,0,20,(void*)12);
        glDrawArrays(GL_TRIANGLE_STRIP,0,4);
        glDisableVertexAttribArray(0);
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&vbo);
    }
    glfwSwapBuffers(win);
}
