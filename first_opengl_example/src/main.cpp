#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    //glViewport(x, y, 가로, 높이);
    glViewport(0, 0, width, height);
}

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, const char** argv){
    SPDLOG_INFO("Start, Program!");

    //glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if(!glfwInit()){
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }

    // ... glfwInit() 호출 후
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfw 윈도우 생성, 실패하면 에러 출력후 종료
    	SPDLOG_INFO("Create glfw window");
        auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
        if (!window) {
            SPDLOG_ERROR("failed to create glfw window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    SPDLOG_ERROR("failed to initialize glad");
    glfwTerminate();
    return -1;
    }
    auto glVersion = glGetString(GL_VERSION);
    //SPDLOG_INFO("OpenGL context version: {}", glVersion);로 적으면 빌드 오류가 날 것임. SPDLOG_INFO("OpenGL context version: {}", *glVersion);으로 적어야 함.
    SPDLOG_INFO("OpenGL context version: {}", *glVersion);

    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    SPDLOG_INFO("Start main loop");
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        //glClearColor 화면을 무슨색으로 채워버릴까? 이 친구는 한번만 셋팅하면 끝남. while문이 아니여도 된다. state-setting function
        glClearColor(0.0f, 0.1f, 0.2f, 0.0f);
        //state-using function
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    } 

    glfwTerminate();
    return 0;
}