#include "levmarjni.h"
#include "Test.h"

JNIEXPORT void JNICALL Java_com_example_levmartest_HelloJni_test
  (JNIEnv *env, jobject object, jint nSample)
{
	Test::ExpFit(nSample);


}
