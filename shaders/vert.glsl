#version 450
layout(location=0)in vec3 pos;
layout(location=1)in vec2 itc;
layout(location=0)uniform float r;
layout(location=1)uniform vec2 cp;
layout(location=0)out vec2 otc;
void main(){
    float sinr=sin(r);
    float cosr=cos(r);
    float xd=pos.x-cp.x;
    float yd=pos.y-cp.y;
    gl_Position=vec4(xd*cosr-yd*sinr+cp.x,yd*cosr+xd*sinr+cp.y,pos.z,1);
    otc=itc;
}
