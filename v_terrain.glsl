#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal;

//Zmienne interpolowane
out vec2 iTexCoord0;
out vec4 iNormal;

out vec4 l;
out vec4 v;

void main(void) {
    vec4 lp = vec4(-50000, 10000, 0, 1); //przestrze? ?wiata
    l = normalize(V * lp - V*M*vertex); //wektor do ?wiat?a w przestrzeni oka
    v = normalize(vec4(0,0,0,1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    iNormal = normalize(V * M * normal); //wektor normalny w przestrzeni oka

    iTexCoord0 = vertex.xz*0.4;

    gl_Position=P*V*M*vertex;
}