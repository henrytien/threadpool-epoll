cmake_minimum_required(VERSION 3.9)
project(threadpool_epoll)

set(CMAKE_CXX_STANDARD 11)

add_executable(threadpool_epoll include/net/EpollPoller.h include/net/Socket.h include/net/TcpServer.h include/net/InetAddress.h include/net/SocketIO.h include/net/TcpConnection.h src/net/Epollpoller.cpp include/threadpool/Noncopyable.h include/threadpool/MutexLock.h include/threadpool/Pthread.h include/threadpool/Buffer.h include/threadpool/Condition.h src/threadpool/Buffer.cpp src/threadpool/Condition.cpp src/threadpool/MutexLock.cpp src/threadpool/Pthread.cpp include/threadpool/ThreadPool.h src/threadpool/ThreadPool.cpp src/main.cpp include/FileName.h include/Configuration.h include/String2UpperServer.h src/Configuration.cpp src/String2UpperServer.cpp include/threadpool/Task.h)