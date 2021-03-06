#version 330

uniform sampler2D textureMap0;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec2 iTexCoord0;
in vec4 iNormal;
in vec4 l;
in vec4 v;

void main(void) {

	vec4 ml = normalize(l);
	vec4 mn = normalize(iNormal);
	vec4 mv = normalize(v);

	vec4 kd = texture(textureMap0,iTexCoord0);

	float nl = clamp(dot(mn, ml), 0, 1);
	pixelColor= vec4(kd.rgb * nl, kd.a);
}