package EngineCore;

public class AQ_DearImGUI {
    static{
        System.loadLibrary("AquariusJNIWrap");
    }
    public native void intializeImGUI(long currentWindow, String glslVersion);
    public native void newFrame();
    public native void render();
    public native void renderDrawData();
    public native void shutDown();

    public native void begin(String windowName);
    public native void setWindowSize(float scrWidth, float scrHeight);
    public native void setWindowPos(float x, float y);
    public native void text(String txtToDisplay);
    public native float sliderFloat(String label, float valueMin, float valueMax);
    public native float[] colorEdit3(String label);
    public native boolean button(String buttonName);
    public native void sameLine();
    public native void end();
}
