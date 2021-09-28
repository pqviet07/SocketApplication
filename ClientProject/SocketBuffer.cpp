#include <SocketBuffer.h>


SocketBuffer::SocketBuffer()
{
}

void SocketBuffer::push_back(const char& value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_vector.push_back(value);
}
char SocketBuffer::operator[](int idx) const
{
    return m_vector[idx];
}
size_t SocketBuffer::size() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_vector.size();
}

