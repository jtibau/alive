uniform mat4 homographyMatrix;
uniform vec4 lightPositionWorld;

varying vec4 originalPos;
varying vec3 originalNorm;

void main() {
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  //gl_Position = gl_Position / gl_Position.w;

  gl_Position = homographyMatrix* gl_Position;
  //gl_Position.xyw = gl_Position.xyw / gl_Position.w;

  gl_TexCoord[0] = gl_MultiTexCoord0;
  originalPos = gl_Vertex;
  originalNorm = gl_Normal;
}

