public class GLWrap {
    public native void defaultOpenGLSettings();
    public native long createWindow(String windowName, int width, int height);
    public native boolean glfwWindowShouldClose(long currentWindow);
    public native void glfwPollEvents();
    public native void glClearColor(float r, float g, float b, float a);
    public native void glClearColorDepthBuffer();
    public native void glfwSwapBuffers(long currentWindow);
    public native void glfwTernimate();
}
