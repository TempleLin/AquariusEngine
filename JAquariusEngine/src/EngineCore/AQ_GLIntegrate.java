package EngineCore;

public class AQ_GLIntegrate {
    private Settings settings;
    private long boundWindow;

    public AQ_GLIntegrate(){
        settings = null;
    }
    public Settings setOpenGL(){
        if (settings == null){
            settings = new Settings(this);
        }
        return settings;
    }
    public long getWindow(){
        return boundWindow;
    }

    private class Settings{
        AQ_GLIntegrate aq_glIntegrate;
        private Settings(AQ_GLIntegrate aq_glIntegrate){
            this.aq_glIntegrate = aq_glIntegrate;
        }
        private native void _ver_Profile(int major, int minor);
        private native long _createWindow(int width, int height, String windowName);
        private native void _setCurrentThreadWindow(long window);
        private native void _initializeGLAD();

        public Settings ver_Profile(int major, int minor){
            _ver_Profile(major, minor);
            return this;
        }
        public Settings createWindow(int width, int height, String windowName){
            long window = _createWindow(width, height, windowName);
            aq_glIntegrate.boundWindow = window;
            return this;
        }
        public Settings setCurrentThreadWindow(long window){
            _setCurrentThreadWindow(window);
            return this;
        }
        public Settings initializeGLAD(){
            _initializeGLAD();
            return this;
        }
        public void finishSettings(){
            aq_glIntegrate.settings = null;
            aq_glIntegrate = null;
        }
    }
}
