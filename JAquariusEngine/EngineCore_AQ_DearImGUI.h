/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class EngineCore_AQ_DearImGUI */

#ifndef _Included_EngineCore_AQ_DearImGUI
#define _Included_EngineCore_AQ_DearImGUI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    intializeImGUI
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_intializeImGUI
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    newFrame
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_newFrame
  (JNIEnv *, jobject);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    render
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_render
  (JNIEnv *, jobject);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    renderDrawData
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_renderDrawData
  (JNIEnv *, jobject);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    shutDown
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_shutDown
  (JNIEnv *, jobject);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    begin
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_begin
  (JNIEnv *, jobject, jstring);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    setWindowSize
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_setWindowSize
  (JNIEnv *, jobject, jfloat, jfloat);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    setWindowPos
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_setWindowPos
  (JNIEnv *, jobject, jfloat, jfloat);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    text
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_text
  (JNIEnv *, jobject, jstring);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    sliderFloat
 * Signature: (Ljava/lang/String;FF)F
 */
JNIEXPORT jfloat JNICALL Java_EngineCore_AQ_1DearImGUI_sliderFloat
  (JNIEnv *, jobject, jstring, jfloat, jfloat);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    colorEdit3
 * Signature: (Ljava/lang/String;)[F
 */
JNIEXPORT jfloatArray JNICALL Java_EngineCore_AQ_1DearImGUI_colorEdit3
  (JNIEnv *, jobject, jstring);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    button
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_EngineCore_AQ_1DearImGUI_button
  (JNIEnv *, jobject, jstring);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    sameLine
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_sameLine
  (JNIEnv *, jobject);

/*
 * Class:     EngineCore_AQ_DearImGUI
 * Method:    end
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_end
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif