#version 120

varying float alpha;

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
    
    alpha = gl_Normal.x;
    gl_PointSize = gl_Vertex.z * 0.5;
}

