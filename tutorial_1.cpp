
#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_NONE

// OpenGL
#include <GL/glew.h>

// Window, Keyboard Manager lib
#include <GLFW/glfw3.h>

// for 3D Calculation
#include <GLM/glm.hpp>

using namespace glm;

int main()
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
  GLFWwindow *window;
  // glfwCreateWindow(width, height, Title, FullScreen, 자원 공유 window)
  // https://www.glfw.org/docs/3.3/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344 참고
  window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);

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
  glfwMakeContextCurrent(window);
  // 삭제된 이전 함수를 사용하지 않겠다는 뜻
  glewExperimental = true;
  if (glewInit() != GLEW_OK)
  {
    // GLEW 초기화 실패
    fprintf(stderr, "Fail to initialize GLEW");
    return -1;
  }

  // ===== 초기화 끝 ====== //
  // 여기서 코드를 끝마칠 경우 window가 생성후 바로 닫히게 됨

  // 밑에서 Escape 키가 눌러지는 것을 감지할 수 있도록 할 것
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  do
  {

    // 버퍼들을 교체
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);
}