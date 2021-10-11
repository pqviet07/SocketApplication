#include <SocketDataStream.h>

void SocketDataStream::push_back(const char& value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_vector.push_back(value);
}
char SocketDataStream::operator[](int idx) const
{
    return m_vector[idx];
}
size_t SocketDataStream::size() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_vector.size();
}

