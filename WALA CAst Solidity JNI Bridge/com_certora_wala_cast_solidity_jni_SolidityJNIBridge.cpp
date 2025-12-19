//
//  File.cpp
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/18/25.
//
#include "solidityBridge.h"
#include "translator.h"
#include "com_certora_wala_cast_solidity_jni_SolidityJNIBridge.h"

#include "Exceptions.h"
#include "CAstWrapper.h"

std::map<int, solidity::frontend::CompilerStack *> compilers;

void Java_com_certora_wala_cast_solidity_jni_SolidityJNIBridge_init(
   JNIEnv *env,
   jobject self)
{
    int id = env->GetIntField(self, env->GetFieldID(env->GetObjectClass(self), "id", "I"));
    compilers[id] = new solidity::frontend::CompilerStack();
}

void Java_com_certora_wala_cast_solidity_jni_SolidityJNIBridge_close(
   JNIEnv *env,
   jobject self)
{
    int id = env->GetIntField(self, env->GetFieldID(env->GetObjectClass(self), "id", "I"));
    CompilerStack *c = compilers[id];
    compilers.erase(id);
    delete c;
}

void Java_com_certora_wala_cast_solidity_jni_SolidityJNIBridge_loadFiles(
    JNIEnv *env,
    jobject self,
    jobjectArray filesAndNames)
{
    int id = env->GetIntField(self, env->GetFieldID(env->GetObjectClass(self), "id", "I"));
    
    int len = env->GetArrayLength(filesAndNames);
    const char *data[len];
    for(int i = 0; i < len; i++) {
        data[i] = env->GetStringUTFChars((jstring)env->GetObjectArrayElement(filesAndNames, i), 0);
    }

    solidity::StringMap sources = gatherSources(len, data);
    
    compileSources(*compilers[id], sources);

    for(int i = 0; i < len; i++) {
        env->ReleaseStringUTFChars(
            (jstring)env->GetObjectArrayElement(filesAndNames, i),
            data[i]);
    }
}

jobject Java_com_certora_wala_cast_solidity_jni_SolidityJNIBridge_files(
    JNIEnv *env,
    jobject self)
{
    jclass arraylist = env->FindClass("java/util/ArrayList");
    jmethodID ctor = env->GetMethodID(arraylist, "<init>", "()V");
    jobject result = env->NewObject(arraylist, ctor);
    
    jmethodID add = env->GetMethodID(arraylist, "add", "(Ljava/lang/Object;)Z");
    
    int id = env->GetIntField(self, env->GetFieldID(env->GetObjectClass(self), "id", "I"));
    std::vector<std::string> sourceASTs = compilers[id]->sourceNames();
    for (std::vector<std::string>::iterator t=sourceASTs.begin(); t!=sourceASTs.end(); ++t) {
        env->CallBooleanMethod(result, add, env->NewStringUTF(t->c_str()));
    }
    
    return result;
}

void Java_com_certora_wala_cast_solidity_jni_SolidityJNIBridge_translate
  (JNIEnv *env, jobject self, jstring fileName)
{
    TRY(exp, env)

    const char *fn = env->GetStringUTFChars(fileName, 0);
    
    int id = env->GetIntField(self, env->GetFieldID(env->GetObjectClass(self), "id", "I"));
    
    Translator xlator(env, exp, self);
    compilers[id]->ast(std::string(fn)).accept(xlator);
  
    env->ReleaseStringUTFChars(fileName, fn);

    CATCH()
 }

