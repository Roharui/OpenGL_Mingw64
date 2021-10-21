
// glfw를 include 하기 전에 glad를 먼저 include 해야함
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// window 사이즈가 변경될때마다 실행되는 CallBack
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  // window 내부 화면의 크기를 설정하는 함수
  glViewport(0, 0, width, height);
}

// ESC 입력을 받는 함수
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// 쉐이더
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// 프레그먼트
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Window 생성
  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    // 메모리 제거 (Free)
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // window 사이즈가 변경될때마다 실행되는 CallBack
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // OpenGL용 데이터를 초기화
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Engine 준비

  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = {
      -0.5f,
      -0.5f,
      0.0f,
      0.5f,
      -0.5f,
      0.0f,
      0.0f,
      0.5f,
      0.0f,
  };

  // vertex buffer (Array) object 생성
  unsigned int VBO, VAO;
  // GPU에 Array 객체 생성
  glGenVertexArrays(1, &VAO);
  // GPU에 Buffer 객체 생성
  glGenBuffers(1, &VBO);
  // VAO로 할당
  glBindVertexArray(VAO);

  // GL_ARRAY_BUFFER로 할당
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // 다음 함수는 미리 생성되어있던 정점 데이터를 버퍼의 메모리에 복서합니다.
  /*
    1 : GL 객체명
    2 : 객체의 크기
    3 : 데이터
    4 : 그래픽 카드가 주어진 데이터를 관리하는 방법

    GL_STATIC_DRAW: 데이터가 거의 변하지 않습니다.
    GL_DYNAMIC_DRAW: 데이터가 자주 변경됩니다.
    GL_STREAM_DRAW: 데이터가 그려질때마다 변경됩니다.

  */
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 다음 함수는 Vetex 데이터를 어떻게 해석해야되는지 알려줍니다.
  /*
    1: 설정할 vertex 속성
    2: vertex 속성의 크기
    3: 데이터 타입
    4: 데이터 정규화 여부
    5: Stride
    6: Offset
  */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  // 설정할 속성의 사용 여부를 결정
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 화면이 종료되었는지 확인하는 함수
  while (!glfwWindowShouldClose(window))
  {

    // ESC 키보드 입력시 창을 닫음
    processInput(window);

    // ==== 랜더링 영역 ===

    // 다음 색상으로 배경색 칠하기
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // ==== 랜더링 영역 끝 ===

    // 컬러버퍼 교체
    // 컬러버퍼는 반복중에 이미지를 그리고 화면에 출력하는 기능을 담당
    glfwSwapBuffers(window);

    // 이벤트 발생 확인 함수
    // 윈도우 상태를 업데이트 하고 콜백을 호출
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  // 메모리 제거
  glfwTerminate();
  return 0;
}