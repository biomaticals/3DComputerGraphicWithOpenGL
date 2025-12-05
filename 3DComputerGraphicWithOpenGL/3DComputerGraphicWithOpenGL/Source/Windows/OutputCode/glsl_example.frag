varying vec3 vertex_normal, light_vector;
varying float dist;

void main() 
{
    vec3 Kd = vec3(1.0, 1.0, 1.0);
    vec3 Id = vec3(gl_LightSource[0].diffuse);

    float d = max(dist, 0.001); // 0 나누기 방지
    float diffuse = max(dot(normalize(vertex_normal), normalize(light_vector)), 0.0);

    vec3 Dr = Kd * Id * diffuse / (0.3 * d);

    gl_FragColor = vec4(Dr, 1.0);
}
