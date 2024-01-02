#ifndef David_Haver_deque_hpp 
#define David_Haver_deque_hpp 

#include <memory>//shared_ptr
#include <stdexcept>//out_of_range

namespace david_haver 
{ 
template<class T>
class Deque //add iterators begin end insert emplace erase std::swap std::erase _if
{
public:
    Deque(size_t itemsInChunk = 8);//add overloading std::initializer_list
    ~Deque() noexcept = default;
    Deque(const Deque &other);
    Deque &operator=(const Deque &rhs);
    Deque(Deque &&other) = default;
    Deque &operator=(Deque &&rhs) = default;

    T &At(size_t position);
    const T &At(size_t position) const;
    T &operator[](size_t position);
    const T &operator[](size_t position) const;
    T &Front();
    const T &Front() const;
    T &Back();
    const T &Back() const;
    bool Empty() const noexcept;
    size_t Size()const noexcept;
    void Clear() noexcept;
    void PushBack(const T& value);
    void PushBack(T&& value);
    void PopBack();
    void PushFront(const T& value);
    void PushFront(T&& value);
    void PopFront();
    template<class... Args >
    void EmplaceBack(Args&&... args );
    template<class... Args >
    void EmplaceFront(Args&&... args );
    void Swap(Deque& other );
private:
    struct ItemsArray;
    std::shared_ptr<ItemsArray> m_first;
    std::shared_ptr<ItemsArray> m_last;
    size_t m_itemsInChunk;
    
    std::shared_ptr<ItemsArray> CopyList(const std::shared_ptr<ItemsArray> &from, std::shared_ptr<ItemsArray> *too);

    struct ItemsArray
    {
        ItemsArray(size_t arraySize, std::shared_ptr<ItemsArray> prev = 0,
        std::shared_ptr<ItemsArray> next = 0);
        ItemsArray(const ItemsArray &other);
        std::shared_ptr<ItemsArray> m_next;
        std::shared_ptr<ItemsArray> m_prev;
        std::shared_ptr<T> m_items;
        size_t m_arraySize;
        size_t m_itemsStored;
    };
};

template<class T>
bool operator==(const Deque<T> &lhs, const Deque<T> &rhs);
template<class T>
bool operator!=(const Deque<T> &lhs, const Deque<T> &rhs);
template<class T>
bool operator<(const Deque<T> &lhs, const Deque<T> &rhs);
template<class T>
bool operator>(const Deque<T> &lhs, const Deque<T> &rhs);
template<class T>
bool operator<=(const Deque<T> &lhs, const Deque<T> &rhs);
template<class T>
bool operator>=(const Deque<T> &lhs, const Deque<T> &rhs);

template <class T>
Deque<T>::Deque(size_t itemsInChunk) : m_first(new ItemsArray(itemsInChunk)), 
m_last(m_first), m_itemsInChunk(itemsInChunk)
{
    //empty
}

template <class T>
Deque<T>::Deque(const Deque &other) : m_itemsInChunk(other.m_itemsInChunk)
{
    m_last = CopyList(other.m_first, &m_first);
}

template <class T>
Deque<T> &Deque<T>::operator=(const Deque &rhs)
{
    std::shared_ptr<ItemsArray> failSafe;
    m_last = CopyList(rhs.m_first, &failSafe);
    m_first = failSafe;
    m_itemsInChunk = rhs.m_itemsInChunk;
    return *this;
}

template <class T>
T &Deque<T>::At(size_t position)
{
    return const_cast<T &>(static_cast<const Deque *>(this)->At(position));
}

template <class T>
const T &Deque<T>::At(size_t position) const
{
    if(m_first->m_itemsStored <= position)
    {
        position += m_itemsInChunk - m_first->m_itemsStored;
    }
    std::shared_ptr<ItemsArray> runner = m_first;
    for(size_t i = 0; (position / m_itemsInChunk > i) && runner; ++i)
    {
        runner = runner->m_next;
    }
    
    if(!runner || runner->m_itemsStored <= position % m_itemsInChunk)
    {
        throw std::out_of_range("position out of range");
    }
    
    return runner->m_items.get()[position % m_itemsInChunk];
}

template <class T>
T &Deque<T>::operator[](size_t position)
{
    return const_cast<T &>(static_cast<const Deque *>(this)->operator[](position));
}

template <class T>
const T &Deque<T>::operator[](size_t position) const
{
    if(m_first->m_itemsStored <= position)
    {
        position += m_itemsInChunk - m_first->m_itemsStored;
    }
    std::shared_ptr<ItemsArray> runner = m_first;
    for(size_t i = 0; position / m_itemsInChunk > i; ++i)
    {
        runner = runner->m_next;
    }
    
    return runner->m_items.get()[position % m_itemsInChunk];
}

template <class T>
T &Deque<T>::Front()
{
    return const_cast<T &>(static_cast<const Deque *>(this)->Front());
}

template <class T>
const T &Deque<T>::Front() const
{
    return m_first->m_items.get()[0];
}

template <class T>
T &Deque<T>::Back()
{
    return const_cast<T &>(static_cast<const Deque *>(this)->Back());
}

template <class T>
const T &Deque<T>::Back() const
{
    return m_last->m_items.get()[m_last->m_itemsStored - 1];
}

template <class T>
bool Deque<T>::Empty() const noexcept
{
    return (0 == m_first->m_itemsStored);
}

template <class T>
void Deque<T>::PushBack(const T &value)
{
    T temp = value;
    PushBack(std::move(temp));
}

template <class T>
void Deque<T>::PushBack(T &&value)
{
    if(m_last->m_itemsStored == m_itemsInChunk)
    {
        m_last->m_next = std::shared_ptr<ItemsArray>
        (new ItemsArray(m_itemsInChunk, m_last));
        m_last = m_last->m_next;
    }
    
    m_last->m_items.get()[m_last->m_itemsStored] = value;
    ++(m_last->m_itemsStored);
}

template <class T>
void Deque<T>::PushFront(const T &value)
{
    T temp = value;
    PushFront(std::move(temp));
}

template <class T>
void Deque<T>::PushFront(T &&value)
{
    if(m_first->m_itemsStored == m_itemsInChunk)
    {
        m_first->m_prev = std::shared_ptr<ItemsArray>
        (new ItemsArray(m_itemsInChunk, 0, m_first));
        m_first = m_first->m_prev;
    }

    for(size_t i = m_first->m_itemsStored; 0 < i; --i)
    {
        m_first->m_items.get()[i] = m_first->m_items.get()[i - 1];
    }

    m_first->m_items.get()[0] = value;
    ++(m_first->m_itemsStored);
}

template <class T>
std::shared_ptr<typename Deque<T>::ItemsArray> Deque<T>::CopyList(const std::shared_ptr<ItemsArray> &from, std::shared_ptr<ItemsArray> *too)
{
    *too = std::shared_ptr<ItemsArray>(new ItemsArray(*from));
    std::shared_ptr<ItemsArray> fromRunner = from;
    std::shared_ptr<ItemsArray> tooRunner = *too;
    while(0 != fromRunner->m_next)
    {
        fromRunner = fromRunner->m_next;
        tooRunner->m_next = std::shared_ptr<ItemsArray>(new ItemsArray(*fromRunner));
        tooRunner->m_next->m_prev = tooRunner;
        tooRunner = tooRunner->m_next;
    }
    return tooRunner;
}

template <class T>
Deque<T>::ItemsArray::ItemsArray(size_t arraySize,
std::shared_ptr<ItemsArray> prev, std::shared_ptr<ItemsArray> next)
: m_next(next), m_prev(prev), m_items(new T[arraySize], std::default_delete<T[]>()), 
m_arraySize(arraySize), m_itemsStored(0)
{
    //empty
}

template <class T>
Deque<T>::ItemsArray::ItemsArray(const ItemsArray &other) : m_next(0), m_prev(0),
m_items(new T[other.m_arraySize], std::default_delete<T[]>()), m_arraySize(other.m_arraySize), 
m_itemsStored(other.m_itemsStored)
{
    for(size_t i = 0; m_itemsStored > i; ++i)
    {
        m_items.get()[i] = other.m_items.get()[i];
    }
}
 
} // david_haver

#endif //David_Haver_deque_hpp
