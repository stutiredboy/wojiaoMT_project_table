
#pragma once

#include "jni.h"
#include <string>

/*
	��JNI���÷������쳣���׳����c++�쳣���ж�ִ�С�
*/
class JException
{
public:
	JException() { }
};

/*
	JNIEnv �쳣�����װ�࣬�����еĴ���ת���� c++ �쳣(JException)��
*/
class JEnv
{
private:
	JNIEnv * env;
	bool     nothrow;

public:
	/*
		��� JNI ���÷������쳣�����׳� c++ �쳣(JException)��
	*/
	inline void JExceptionCheck() const
	{
		if (this->env->ExceptionCheck()) throw JException();
	}

	/*
		�׳� c++ �쳣(JException)��
	*/
/*
	inline void JExceptionThrow() const
	{
		throw JException();
	}
*/
	/*
		��� throwNow Ϊ true���׳�JNI�쳣�������ж�ִ�����̣���Ȼ���׳� c++ �쳣(JException)��
		name and message are utf8 encoding
	*/
	inline void JExceptionThrowIf(bool throwNow, const char * name, const char * message) const
	{
		if (throwNow) { this->ThrowNew(name, message); throw JException(); }
	}

	/*
		��� throwNow Ϊ true���׳�JNI�쳣�������ж�ִ�����̣���Ȼ���׳� c++ �쳣(JException)��
		name is utf8 encoding.
	*/
	inline void JExceptionThrowIf(bool throwNow, const char * name, jthrowable cause) const
	{
		if (throwNow) { this->ThrowNew(name, cause); throw JException(); }
	}

public:
	/*
		nothrow
			���׳���Ҫ�� throws ���������쳣��
			����������쳣���� java.lang.Error��Ҳ���� java.lang.RuntimeException��
			�������Ϊ cause �׳� java.lang.RuntimeException��
	*/
	explicit JEnv(JNIEnv * env, bool nothrow = true)
	{
		this->env     = env;
		this->nothrow = nothrow;
	}

	~JEnv()
	{
		// �������������׳��쳣���������治ʹ�ô����װ������ֱ��ʹ��JNIEnv*�ķ�����

		if (false == nothrow)
			return;

		jthrowable occurred = this->env->ExceptionOccurred();
		if (NULL == occurred)
			return;

		if (jclass error = this->env->FindClass("java/lang/Error"))
		{
			if (this->env->IsInstanceOf(occurred, error))
				return;

			if (jclass runtime = this->env->FindClass("java/lang/RuntimeException"))
				if (this->env->IsInstanceOf(occurred, runtime))
					return;
		}
		/*
		ִ�е���������������
		1 not java.lang.Error; 
		2 not java.lang.RuntimeException; 
		3 FindClass error;
		*/
		FatalThrowNew("java/lang/RuntimeException", occurred);
	}

	/*
		�����ж����з���ֵ����ʹ�ð�װ�����������׳� c++ �쳣��
		������������˳� JVM��
	*/
	void FatalThrowNew(const char * name, jthrowable cause) throw()
	{
		if (jclass jcls = this->env->FindClass(name))
			if (jmethodID jmid = this->env->GetMethodID(jcls, "<init>", "(Ljava/lang/Throwable;)V"))
				if (jobject jobj = this->env->NewObject(jcls, jmid, cause))
				{
					this->env->Throw((jthrowable)jobj); // skip result
					return;
				}
		this->env->FatalError((std::string("_ThrowNew(") + name + ", [cause])").c_str());
	}

	/*
		�����ж����з���ֵ����ʹ�ð�װ�����������׳� c++ �쳣��
		������������˳� JVM��
	*/
	void FatalThrowNew(const char * name, const char * message) throw()
	{
		if (jclass jcls = this->env->FindClass(name))
		{
			this->env->ThrowNew(jcls, message);
			return;
		}
		this->env->FatalError((std::string("_ThrowNew(") + name + ", " + message + ")").c_str());
	}

	bool hasException() const
	{
		return JNI_TRUE == this->ExceptionCheck();
	}

	jboolean ExceptionCheck() const
	{
		return this->env->ExceptionCheck();
	}

	jthrowable ExceptionOccurred() const
	{
		return this->env->ExceptionOccurred();
	}

	void ThrowNewIfCause(const char * name, jthrowable cause) const
	{
		if (cause)
			ThrowNew(name, cause);
	}

	// sample: jenv->ThrowNew("java/lang/RuntimeException", jenv->ExceptionOccurred());
	void ThrowNew(const char * name, jthrowable cause) const
	{
		if (NULL == cause)
			return ThrowNew(name, "null cause");

		jclass    jcls = this->FindClass(name);
		jmethodID jmid = this->GetMethodID(jcls, "<init>", "(Ljava/lang/Throwable;)V");
		jobject   jobj = this->NewObject(jcls, jmid, cause);
		this->env->Throw((jthrowable)jobj);
	}

	void ThrowNew(const char * name, const char * message) const
	{
		this->env->ThrowNew(this->FindClass(name), message);
	}

	jclass FindClass(const char * name) const
	{
		jclass cls = this->env->FindClass(name);
		this->JExceptionCheck();
		return cls;
	}

	jobject NewObject(jclass clazz, jmethodID methodID, ...) const
	{
		va_list args;
		va_start(args, methodID);
		jobject result = this->env->NewObjectV(clazz, methodID, args);
		va_end(args);
		this->JExceptionCheck();
		return result;
	}

	/*
		sig
		���ֿ���ͨ�� javap -s classes �õ������ض��塣 -s ��ӡ�ڲ�ǩ�������Ͷ�Ӧǩ������:
		Java����       ��Ӧ��ǩ��
		boolean        Z
		byte           B
		char           C
		shrot          S
		int            I
		long           L
		float          F
		double         D
		void           V
		Object         L��/�ָ������������; �磺"Ljava/lang/String;"
		Array          [ǩ�� �磺"[I"��"[Ljava/lang/String;"
	*/
	jmethodID GetMethodID(jclass clazz, const char *name, const char *sig) const
	{
		jmethodID jmid = this->env->GetMethodID(clazz, name, sig);
		this->JExceptionCheck();
		return jmid;
	}

	jclass GetObjectClass(jobject obj) const
	{
		this->JExceptionThrowIf(NULL == obj, "java/lang/NullPointerException", "GetObjectClass object is null");
		return this->env->GetObjectClass(obj); // no throw
	}

	jboolean CallBooleanMethod(jobject obj, jmethodID methodID, ...) const
	{
		va_list args;
		va_start(args,methodID);
		jboolean result = this->env->CallBooleanMethodV(obj, methodID, args);
		va_end(args);
		this->JExceptionCheck();
		return result;
	}

	jsize GetArrayLength(jarray array) const
	{
		this->JExceptionThrowIf(NULL == array, "java/lang/NullPointerException", "GetArrayLength array is null");
		return this->env->GetArrayLength(array); // no throw
	}

	jbyte * GetByteArrayElements(jbyteArray array, jboolean *isCopy) const
	{
		this->JExceptionThrowIf(NULL == array, "java/lang/NullPointerException", "GetByteArrayElements array is null");
		jbyte * elements = this->env->GetByteArrayElements(array, isCopy);
		this->JExceptionThrowIf(NULL == elements, "java/lang/NullPointerException", "GetByteArrayElements elements is null");
		return elements;
	}

	void ReleaseByteArrayElements(jbyteArray array, jbyte *elems, jint mode) const
	{
		this->env->ReleaseByteArrayElements(array, elems, mode);
	}

	jbyteArray NewByteArray(jsize len) const
	{
		jbyteArray array = this->env->NewByteArray(len);
		this->JExceptionCheck();
		return array;
	}

	void SetByteArrayRegion(jbyteArray array, jsize start, jsize len, const jbyte *buf) const
	{
		this->JExceptionThrowIf(NULL == buf, "java/lang/NullPointerException", "SetByteArrayRegion buf is null");
		this->env->SetByteArrayRegion(array, 0, len, buf);
		this->JExceptionCheck();
	}

	jbyteArray NewByteArray(const void * data, size_t size) const
	{
		this->JExceptionThrowIf(NULL == data, "java/lang/NullPointerException", "NewByteArray data is null");
		jbyteArray array = this->NewByteArray(size);
		this->SetByteArrayRegion(array, 0, size, (const jbyte *)data);
		return array;
	}

	const char* GetStringUTFChars(jstring str, jboolean *isCopy) const
	{
		const char * chars = this->env->GetStringUTFChars(str, isCopy);
		this->JExceptionCheck();
		return chars;
	}

	void ReleaseStringUTFChars(jstring str, const char* chars) const
	{
		this->env->ReleaseStringUTFChars(str, chars);
	}

	void DeleteLocalRef(jobject localRef) const
	{
		this->env->DeleteLocalRef(localRef);
	}
};

class JByteArray
{
	const JEnv & jenv;
	jbyteArray   array;

	jbyte      * elements;
	jsize        length;
	jboolean     iscopy;

public:
	JByteArray(const JEnv & _jenv, jbyteArray array)
		: jenv(_jenv)
	{
		this->array    = array;
		this->length   = jenv.GetArrayLength(array);
		this->elements = jenv.GetByteArrayElements(array, &this->iscopy);
	}

	~JByteArray()
	{
		this->jenv.ReleaseByteArrayElements(this->array, this->elements, 0);
	}

	const void * data() const { return this->elements; }
	size_t size() const       { return this->length; }
	bool isCopy() const       { return this->iscopy == JNI_TRUE; }
};

class JUTFString
{
	const JEnv & jenv;
	jstring      str;

	const char * utf8;
	jboolean     iscopy;

public:
	JUTFString(const JEnv & _jenv, jstring str)
		: jenv(_jenv)
	{
		this->str  = str;
		this->utf8 = jenv.GetStringUTFChars(str, &iscopy);
	}

	~JUTFString()
	{
		this->jenv.ReleaseStringUTFChars(str, utf8);
	}

	const char * c_str() const { return utf8; }
	bool isCopy() const        { return iscopy == JNI_TRUE; }

	/*
	jstring New(const char * utf)
	{
		return env->NewStringUTF(utf);
	}
	*/
};

template<class T>
class JLocalRef
{
public:
	JLocalRef(const JEnv & _jenv, T localRef)
		: jenv(_jenv), ref(localRef)
	{
	}

	/*
	 * �ͷ����õ�����Ȩ���������á�
	 */
	T release()
	{
		T localRef = this->ref;
		this->ref = NULL;
		return localRef;
	}

	T get() const
	{
		return this->ref;
	}

	~JLocalRef()
	{
		if (NULL != this->ref)
		{
			jenv.DeleteLocalRef(this->ref);
		}
	}

private:
	// avoid copy and asign
	JLocalRef(const JLocalRef&);
	void operator=(const JLocalRef&);

	const JEnv & jenv;
	T ref;
};

/*
�쳣�������ꡣ
*/

#define __TRY__BEGIN__ \
	try {

#define __TRY__END__ \
	} catch (JException &) {                                                     \
		/* do nothing. jvm will throw the exception. */                          \
	} catch (std::bad_alloc & ) {                                                \
		jenv.FatalThrowNew("java/lang/OutOfMemoryError", "std::bad_alloc");      \
	} catch (std::exception & ex) {                                              \
		jenv.FatalThrowNew("java/lang/RuntimeException", ex.what());             \
	} catch (GNET::Marshal::Exception &) {                                       \
		jenv.FatalThrowNew("java/lang/RuntimeException", "Marshal::Exception");  \
	} catch (GNET::__db_helper::PageFile::Exception & ) {                        \
		jenv.FatalThrowNew("java/lang/RuntimeException", "PageFile::Exception"); \
	} catch (...) {                                                              \
		jenv.FatalThrowNew("java/lang/UnknownError", "catch(...)");              \
	}                                                                            \

//	} catch (Marshal & ) {
