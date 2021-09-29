#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <mutex>
#include <vector>

class SocketBuffer
{
public:
    std::vector<char> m_vector;
    mutable std::mutex m_mutex;

public:
    void push_back( const char& value );
    char operator[] (int) const;
    size_t size() const;
};
#endif // MYQUEUE_H
