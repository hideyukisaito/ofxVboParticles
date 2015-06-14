#version 120

uniform sampler2D tex;
varying float alpha;

void main() {
   
    vec2 st = gl_TexCoord[0].st;
    
    vec4 color = texture2D(tex, st);
    color.a = alpha;
    
    gl_FragColor =  color * gl_Color;
    
}

