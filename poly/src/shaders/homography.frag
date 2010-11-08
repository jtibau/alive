uniform vec4 lightPositionWorld;

const vec4 specular_color = vec4(1.0, 1.0, 1.0, 1.0);

uniform sampler2D Texture;
varying vec4 originalPos;
varying vec3 originalNorm;

void main(void) {

  vec4 vertex_position_camera = gl_ModelViewMatrix * originalPos;
	vec3 normal_camera = normalize(gl_NormalMatrix * originalNorm);
  vec4 light_position_camera = gl_ModelViewMatrix * lightPositionWorld;
  
  vec3 light_vert = normalize(vec3(light_position_camera - vertex_position_camera));
	vec3 light_refl = normalize(reflect(light_vert, normal_camera));
	
	// diffuse light
	float diffuse_intensity = max(dot(light_vert, normal_camera), 0.0);

	// specular light
	float specular_intensity = max(dot(light_refl, normalize(vec3(vertex_position_camera))), 0.0);
	specular_intensity = pow(specular_intensity, 10.0);

  vec4 diffuse_color = vec4(texture2D(Texture, gl_TexCoord[0].st));
	gl_FragColor = diffuse_color * diffuse_intensity + specular_color * specular_intensity ;
}
