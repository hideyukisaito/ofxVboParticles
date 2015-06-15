#version 120

varying float alpha;
attribute float size;

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
    
    alpha = gl_Normal.x;
    gl_PointSize = gl_Vertex.z * size;
}

