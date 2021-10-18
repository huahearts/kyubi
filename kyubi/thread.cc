#include "thread.h"
#include "log.h"
#include "util.h"
namespace kyubi{

static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_thread_name = "UNKNOW";

static kyubi::Logger::ptr g_logger = KYUBI_LOG_NAME("system");

Semaphore::Semaphore(uint32_t count) {
    if(sem_init(&m_semaphore,0,count)) {
        throw std::logic_error("sem_init error");
    }
}
Semaphore::~Semaphore(){
    sem_destroy(&m_semaphore);
}

void Semaphore::wait(){
    while(true) {
        if(sem_wait(&m_semaphore)) {
            throw std::logic_error("sem_post error");
        }
    }
}

void Semaphore::notify(){
    if(sem_post(&m_semaphore)) {
        throw std::logic_error("sem_post error");
    }
}

Thread* Thread::GetThis(){
    return t_thread;
}

const std::string& Thread::GetName() {
    return t_thread_name;
}

void Thread::SetName(const std::string& name) {
    if(t_thread) {
        t_thread->m_name = name;
    }
    
    t_thread_name = name;
}
Thread::Thread(std::function<void()> cb,const std::string& name)
    :m_cb(cb)
    ,m_name(name)
{
    if(name.empty()) {
        m_name = "UNKNOW";
    }
    int rt = pthread_create(&m_thread,nullptr,&Thread::run,this);
    if(rt) {
        KYUBI_LOG_ERROR(g_logger) << "pthread_create thread fail,rt=" << rt << " name=" << name;
        throw std::logic_error("pthread_create error");
    }
    //m_semaphore.wait();
}

Thread::~Thread() {
    if(m_thread) {
        pthread_detach(m_thread);
    }
}

void* Thread::run(void* args) {
    Thread* thread = (Thread*)args;
    t_thread = thread;
    thread->m_id = kyubi::GetThreadId();
    pthread_setname_np(pthread_self(),thread->m_name.substr(0,15).c_str());
    std::function<void()> cb;
    cb.swap(thread->m_cb);
    cb();
    //thread->m_semaphore.notify();
    return 0;
}

void Thread::join() {
    if(m_thread) {
        int rt = pthread_join(m_thread,nullptr);
        if (rt) {
            KYUBI_LOG_ERROR(g_logger) << "pthread_join thread fail,rt=" << rt << " name=" << m_name;
            throw std::logic_error("pthread_join error");
        }
        m_thread = 0;
    }
}

}