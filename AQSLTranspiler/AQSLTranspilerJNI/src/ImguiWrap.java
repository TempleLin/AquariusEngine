public class ImguiWrap {
    public native void initializeImGUI(long currentWindow);
    public native void newFrame();
    public native void render(long currentWindow);
    public native void renderDrawData();
    public native void guiUpdate();
    public native void shutdown();
}
