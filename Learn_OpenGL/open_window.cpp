/*
  OpenGL 3.3 버전 이상이 시스템/하드웨어에 설치되어 있는지 확인하세요. 
  그렇지 않다면 응용 프로그램이 충돌하거나 예기치 못한 동작을 야기할 수 있습니다. 
  OpenGL 버전을 확인하려면 
  리눅스에서 glxinfo를 호출하거나 
  윈도우에서 OpenGL Extension Viewer와 같은 유틸리티를 사용하세요. 
  지원되는 버전이 낮다면 그래픽 카드가 OpenGL 3.3 버전 이상을 지원하는지 
  확인(그렇지 않다면 정말 오래된 그래픽 카드입니다)한 후 드라이버를 업데이트하세요.
*/

// glfw를 include 하기 전에 glad를 먼저 include 해야함
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// window 사이즈가 변경될때마다 실행되는 CallBack
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

// ESC 입력을 받는 함수
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main()
{
  // glfw 초기화
  glfwInit();
  // glfw 버전 3 이용
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Core Profile 이용 / 기능 최소화
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // MacOS 에서는 다음 코드가 있어야지만 동작함
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

  // OpenGL용 데이터를 초기화
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // window 내부 화면의 크기를 설정하는 함수
  glViewport(0, 0, 800, 600);

  // window 사이즈가 변경될때마다 실행되는 CallBack
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Engine 준비

  // 화면이 종료되었는지 확인하는 함수
  while (!glfwWindowShouldClose(window))
  {

    // ESC 키보드 입력시 창을 닫음
    processInput(window);

    // ==== 랜더링 영역 ===

    // 다음 색상으로 배경색 칠하기
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // ==== 랜더링 영역 끝 ===

    // 컬러버퍼 교체
    // 컬러버퍼는 반복중에 이미지를 그리고 화면에 출력하는 기능을 담당
    glfwSwapBuffers(window);

    // 이벤트 발생 확인 함수
    // 윈도우 상태를 업데이트 하고 콜백을 호출
    glfwPollEvents();
  }

  // 메모리 제거
  glfwTerminate();
  return 0;
}