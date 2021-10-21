
#include <stdio.h>
#include <stdlib.h>

// OpenGL
#include <GL/glew.h>

// Window, Keyboard Manager lib
#include <GLFW/glfw3.h>

// for 3D Calculation
#include <GLM/glm.hpp>

using namespace glm;

int init(GLFWwindow **window)
{

  // ===== 초기화 ====== //

  // initializing GLFW
  if (!glfwInit())
  {
    fprintf(stderr, "Fail to initializing GLFW!");
    return -1;
  }

  // 4x 안티에일리어싱 (계단현상 방지 https://learnopengl.com/Advanced-OpenGL/Anti-Aliasing 참고)
  glfwWindowHint(GLFW_SAMPLES, 4);
  // OpenGL 3.x 사용
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  // OpenGL 3.x 사용
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Mac 호환 코드
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // 구버전 OpenGL 사용 거부
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // OpenGL 컨텍스트
  // 전역변수
  // glfwCreateWindow(width, height, Title, FullScreen, 자원 공유 window)
  // https://www.glfw.org/docs/3.3/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344 참고
  *window = glfwCreateWindow(1024, 768, "Tutorial 02", NULL, NULL);

  // window 생성 불가시
  if (window == NULL)
  {
    // 만약 intelGPU 사용시 OpenGL 3.x 지원 X
    fprintf(stderr, "Fail to OpenGLFW window");
    // 사용된 메모리 삭제
    glfwTerminate();
    return -1;
  }

  // GLFW 초기화
  // Double Buffer로 사용할 Window를 등록하는 함수이며, 등록되면 Thread로 설정되어 사용된다.
  // Dobule Buffer 가 뭔지 모름...
  glfwMakeContextCurrent(*window);
  // 삭제된 이전 함수를 사용하지 않겠다는 뜻
  glewExperimental = true;
  if (glewInit() != GLEW_OK)
  {
    // GLEW 초기화 실패
    fprintf(stderr, "Fail to initialize GLEW");
    return -1;
  }

  return 0;

  // ===== 초기화 끝 ====== //
}

int main()
{

  GLFWwindow *window;

  if (init(&window) < 0)
  {
    return -1;
  }

  // 여기서 코드를 끝마칠 경우 window가 생성후 바로 닫히게 됨

  // ==== 삼각형 만들기 ====

  // Window를 만들고 난 후 다음 코드를 입력
  // VAO에 관해 더 많은 정보를 알고 싶다면 다른 튜토리얼을 참고해 주세요.
  GLuint VertexArray1D;
  glGenVertexArrays(1, &VertexArray1D);
  glBindVertexArray(VertexArray1D);

  static const GLfloat g_vertex_buffer_data[] = {
      -1.0f, // X
      -1.0f, // Y
      +0.0f, // Z

      +1.0f, // X
      -1.0f, // Y
      +0.0f, // Z

      +0.0f, // X
      +1.0f, // Y
      +0.0f, // Z
  };

  // 아래는 버택스 버퍼를 생성하는 코드입니다.
  GLuint vertexbuffer;
  // 버퍼를 생성합니다. vertextBuffer 에 결과 식별자를 넣습니다.
  glGenBuffers(1, &vertexbuffer);
  // 아래의 명령어들은 우리의 "vertexbuffer" 버퍼에 대해서 다룰겁니다.
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  // 우리의 버텍스들을 OpenGL로 넘겨줍니다.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  // ==== 삼각형 만들기 끝 ====

  // 밑에서 Escape 키가 눌러지는 것을 감지할 수 있도록 할 것
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  do
  {

    // === 삼각형 그리기 ===

    // 버퍼의 첫번째 속성값(attribute) : 버텍스들
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // 삼각형 그리기

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    // === 삼각형 그리기 끝 ===

    // 버퍼들을 교체
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);
}