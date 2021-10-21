# MinGW를 이용한 OPENGL

> 이 빌드는 `Visual Studio Code`를 이용하였습니다.

OpenGL을 MinGW로 한번 만들어 보아요. 근데 웬만하면 그냥 Visual Studio 쓰는걸 추천드립니다.

## MSYS2 설치

[MSYS2](https://www.msys2.org/) 설치하기

## 모듈 설치

아래의 내용을 실행하세요.

```
setup.bat
```

## Compile 하기

`VSCode`로 Ctrl+Shift+B를 누르고 제일 위의 `Build : OpenGL`를 실행시키세요.

## Glad 설치 (Learn_OpenGL용)

> Learn_OpenGL을 사용하실때만 다음 내용을 따라해 주세요.

[여기](https://glad.dav1d.de/)에서 언어를 C++로 설정하고 API 섹션에서 3.3 이상의 OpenGL 버전을 선택합니다. 또한 프로파일이 Core로 설정되있고 Generate a loader 옵션이 선택되어있는지 확인하세요. 지금은 확장(extension)을 무시하고 생성(Generate) 을 클릭하여 라이브러리 파일을 생성하세요.

압축파일을 풀어 `glad.h`는 `C:\msys64\mingw64\include\glad`에 두고 `glad.c`는 현재 디렉토리에 `lib` 폴더를 만들어 안에 넣어둡니다.

## 실행하기

`F5` 실행하기
