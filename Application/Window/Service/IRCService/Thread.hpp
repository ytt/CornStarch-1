﻿//
//  Thread.h
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _Thread_h
#define _Thread_h
#include <wx/wxprec.h>
#include <wx/wx.h>

namespace CornStarch
{
// スレッドを実行するためのクラス
class Thread: public wxThread
{

private:

	// スレッドを実行するための基本クラス
	class ThreadDataBase
	{
	protected:
	public:
		ThreadDataBase()
		{
		}
		virtual ~ThreadDataBase()
		{
		}
		// メソッドを実行します。
		virtual void invoke()=0;
	};
	/*
	 * スレッドで実行するインスタンスとメソッドを保持するクラス
	 */
	template<typename T>
	class ThreadData: public ThreadDataBase
	{

	public:
        //　メソッドを実行するインスタンスです。
        T* m_instance;
        // 実行するメソッドです。
        void* m_method;
		ThreadData(T* instance) :
				m_instance(instance)
		{

		}
		virtual ~ThreadData()
		{
			free(m_method);
		}
        //override メソッドを実行します。
		void invoke()
		{
			typedef void (T::*method_t)(void);

			method_t method_ = *(method_t*) m_method;
			(m_instance->*method_)();
		}
	};
	template<typename T, typename TArg,typename TArgActual>
	class ThreadDataFunc: public ThreadData<T>
	{
	public:
	    ThreadDataFunc(T* instance) :
	        ThreadData<T>(instance)
	            {

	            }
		virtual ~ThreadDataFunc()
		{
		}
        TArgActual arg;
        //override メソッドを実行します。
		void invoke()
		{
			typedef void (T::*method_t)(TArg);
			method_t method_ = *(method_t*)this->m_method;
			(this->m_instance->*method_)(arg);
		}
	};
	template<typename T, typename TArg,typename TArgActual, typename TArg2,typename TArgActual2>
	class ThreadDataFunc2: public ThreadDataFunc<T,TArg,TArgActual>
	{
	public:
	    ThreadDataFunc2(T* instance) :
	        ThreadDataFunc<T,TArg,TArgActual>(instance)
                {

                }
		virtual ~ThreadDataFunc2()
		{
		}
        TArgActual2 arg2;
        //override メソッドを実行します。
		void invoke()
		{
			typedef void (T::*method_t)(TArg,TArg2);
			method_t method_ = *(method_t*)this->m_method;
			(this->m_instance->*method_)(this->arg,arg2);
		}
	};
	// Thread実行のための要素です。
	ThreadDataBase* m_threadData;

public:

	// スレッドを開始します。
	void start()
	{
		this->Create();
		this->Run();
	}

	// wxThreadのエントリポイントです。
	wxThread::ExitCode Entry(void)
	{
		m_threadData->invoke();
		delete m_threadData;
		if (TestDestroy()){
			return (wxThread::ExitCode) -1;
		}
		return (wxThread::ExitCode) 0;
	}

	// インスタンスとメソッドを指定する
	template<typename T>
	Thread(T *obje, void (T::*method)(void),
            wxThreadKind kind = wxTHREAD_DETACHED): wxThread(kind)
	{
		ThreadData<T> *data = new ThreadData<T>(obje);
		typedef void (T::*method_t)(void);
		int size = sizeof(method_t);
		data->m_method = malloc(size);
		*(method_t*) data->m_method = method;

		m_threadData = data;
	}
	// インスタンスとメソッドを指定する
	template<typename T, typename TArg, typename TArgActual>
	Thread(T *obje, void (T::*method)(TArg), TArgActual arg,
            wxThreadKind kind = wxTHREAD_DETACHED): wxThread(kind)
	{
	    ThreadDataFunc<T, TArg, TArgActual> *data = new ThreadDataFunc<T,TArg, TArgActual>(obje);
		data->arg = arg;
		typedef void (T::*method_t)(TArg);
		int size = sizeof(method_t);
		data->m_method = malloc(size);
		*(method_t*) data->m_method = method;
		m_threadData = data;
	}
	// インスタンスとメソッドを指定する
	template<typename T, typename TArg,typename TArgActual,typename TArg2,typename TArgActual2>
	Thread(T *obje, void (T::*method)(TArg,TArg2), TArgActual arg,TArgActual2 arg2,
	        wxThreadKind kind = wxTHREAD_DETACHED): wxThread(kind)
	{
	    ThreadDataFunc2<T, TArg,TArgActual,TArg2, TArgActual2> *data =
		        new ThreadDataFunc2<T, TArg,TArgActual,TArg2, TArgActual2>(obje);
		data->arg = arg;
		data->arg2 = arg2;
		typedef void (T::*method_t)(TArg,TArg2);
		int size = sizeof(method_t);
		data->m_method = malloc(size);
		*(method_t*) data->m_method = method;
		m_threadData = data;
	}
	virtual ~Thread()
	{
	}
};
}

#endif
