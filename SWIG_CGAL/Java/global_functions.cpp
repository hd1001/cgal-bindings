#include <stdexcept>
#include <SWIG_CGAL/Java/global_functions.h>

//function called when library is loaded in Java
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
  get_cached_jvm() = jvm;
  return JNI_VERSION_1_2;
}

JavaVM* & get_cached_jvm(){
  static JavaVM* cached_jvm = NULL;
  return cached_jvm;
}

JNIEnv * JNU_GetEnv() {
  JNIEnv *env;
  CGAL_precondition(get_cached_jvm()!=NULL);
  jint rc = get_cached_jvm()->GetEnv((void **)&env, JNI_VERSION_1_2);
  if (rc == JNI_EDETACHED)
    throw std::runtime_error("current thread not attached");
  if (rc == JNI_EVERSION)
    throw std::runtime_error("jni version not supported");
  return env;
}

