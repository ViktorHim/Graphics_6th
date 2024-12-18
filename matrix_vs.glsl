#version 400
in vec3 vertex_position;
in vec3 vertex_color; // Новый вход для цвета

out vec3 f_pos;
out vec3 color; // Передача цвета во фрагментный шейдер

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    f_pos = vec3(model * vec4(vertex_position, 1.0));
    color = vertex_color; // Передача цвета
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}