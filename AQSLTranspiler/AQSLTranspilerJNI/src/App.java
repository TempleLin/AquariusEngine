public class App {
    static{
        // System.loadLibrary("../../JNICppMain/x64/Release/JNICppMain");
    }

    public static void main(String[] args) throws Exception {
        GLWrap glWrap = new GLWrap();
        ImguiWrap imguiWrap = new ImguiWrap();

        glWrap.defaultOpenGLSettings();
        long currentWindow = glWrap.createWindow("AQSLTranspiler", 1600, 900);

        imguiWrap.initializeImGUI(currentWindow);

        while (!glWrap.glfwWindowShouldClose(currentWindow)) {
            imguiWrap.newFrame();
            
            glWrap.glClearColor(.05f, .05f, .05f, 1.f);
            glWrap.glClearColorDepthBuffer();
            
            imguiWrap.guiUpdate();

            imguiWrap.render();
            imguiWrap.renderDrawData();

            glWrap.glfwSwapBuffers(currentWindow);
        }

        imguiWrap.shutdown();
        glWrap.glfwTernimate();
    }
}
