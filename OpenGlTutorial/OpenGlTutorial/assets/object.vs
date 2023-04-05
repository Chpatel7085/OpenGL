#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


out vec2 TexCoord;

uniform mat4 model ; // set in code and this uniform variable are those which are not changed through out the code and we want them to be constant
uniform mat4 view ; // set in code and this uniform variable are those which are not changed through out the code and we want them to be constant
uniform mat4 projection ; // set in code and this uniform variable are those which are not changed through out the code and we want them to be constant


void main(){
   gl_Position = projection* view* model* vec4(aPos, 1.0);
   TexCoord = aTexCoord;
}