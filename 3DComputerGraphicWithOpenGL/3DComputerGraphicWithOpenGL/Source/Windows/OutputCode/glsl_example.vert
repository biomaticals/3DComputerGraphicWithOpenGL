varying vec3 vertex_normal, light_vector;
varying float dist;

void main() {
    // 정상적인 normal 변환
    vertex_normal = normalize(gl_NormalMatrix * gl_Normal);

    // 표준 변환
    gl_Position = ftransform();

    // 월드 공간 또는 eye 공간에서의 vertex 위치
    vec3 vertex_position = vec3(gl_ModelViewMatrix * gl_Vertex);

    // 빛의 위치도 같은 공간으로 변환
    vec3 light_position = vec3(gl_LightSource[0].position);

    // 빛 방향
    light_vector = normalize(light_position - vertex_position);

    // 거리
    dist = distance(vertex_position, light_position);
}