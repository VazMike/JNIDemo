#include <jni.h>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include "JNIMain.h"

JNIEXPORT void JNICALL Java_JNIMain_sayHelloToC(JNIEnv* env, jobject thisObj)
{
	std::cout << "In C++ | Hello, World!\n";
}

JNIEXPORT jdouble JNICALL Java_JNIMain_average(JNIEnv* env, jobject thisObj, jint a, jint b)
{
	return 1.0 * (a + b) / 2;
}

JNIEXPORT jstring JNICALL Java_JNIMain_reverse(JNIEnv* env, jobject thisObj, jstring javaLine)
{
	auto cLine = env->GetStringUTFChars(javaLine, NULL);
	if (cLine == nullptr)
		return nullptr;

	auto line = std::string{""};
	for (auto i = (int)strlen(cLine) - 1; i >= 0; --i)
		line += cLine[i];
	env->ReleaseStringUTFChars(javaLine, cLine);
	return env->NewStringUTF(line.c_str());
}

JNIEXPORT jdouble JNICALL Java_JNIMain_median(JNIEnv* env, jobject thisObj, jdoubleArray javaArray)
{
	auto arrPtr = env->GetDoubleArrayElements(javaArray, NULL);
	if (arrPtr == nullptr)
		return 0;
	auto length = env->GetArrayLength(javaArray);
	
	auto v = std::vector<double>(length);
	for (auto i = 0; i < length; ++i)
		v[i] = arrPtr[i];
	env->ReleaseDoubleArrayElements(javaArray, arrPtr, 0);

	auto mid = v.size() / 2;
	std::nth_element(std::begin(v), std::begin(v) + mid, std::end(v));

	return v[mid];
}

JNIEXPORT void JNICALL Java_JNIMain_modifyFields(JNIEnv* env, jobject thisObj)
{
	auto thisClass = env->GetObjectClass(thisObj);

	auto intField = env->GetFieldID(thisClass, "numberField", "I");
	if (intField == nullptr)
		return;

	auto number = env->GetIntField(thisObj, intField);
	std::cout << "In C++ | Number received: " << number << "\n";

	number = 100;
	env->SetIntField(thisObj, intField, number);

	auto stringField = env->GetFieldID(thisClass, "secretMessageField", "Ljava/lang/String;");
	if (stringField == nullptr)
		return;

	auto javaMessage = static_cast<jstring>(env->GetObjectField(thisObj, stringField));
	auto cMessage = env->GetStringUTFChars(javaMessage, NULL);
	if (cMessage == nullptr)
		return;

	std::cout << "In C++ | String received: " << cMessage << "\n";
	env->ReleaseStringUTFChars(javaMessage, cMessage);

	javaMessage = env->NewStringUTF("night");
	if (javaMessage == nullptr)
		return;
	env->SetObjectField(thisObj, stringField, javaMessage);
}