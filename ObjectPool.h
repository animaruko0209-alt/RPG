#pragma once

#include <vector>
#include <memory>
#include <functional>

// 汎用オブジェクトプール (shared_ptr<ObjectPool<T>> で保持し、Acquire は unique_ptr を返す)
template<typename T>
class ObjectPool : public std::enable_shared_from_this<ObjectPool<T>>
{
public:
    ObjectPool(size_t initial = 0)
    {
        for (size_t i = 0; i < initial; ++i)
            pool_.push_back(new T());
    }

    // unique_ptr にカスタムデリータを付けて返す（デリータはオブジェクトをプールに返却）
    std::unique_ptr<T, std::function<void(T*)>> Acquire()
    {
        T* obj = nullptr;
        if (pool_.empty())
            obj = new T();
        else
        {
            obj = pool_.back();
            pool_.pop_back();
        }

        std::weak_ptr<ObjectPool<T>> wp = this->shared_from_this();
        auto deleter = [wp](T* p) {
            if (auto sp = wp.lock())
            {
                sp->ReleaseRaw(p);
            }
            else
            {
                delete p;
            }
        };

        return std::unique_ptr<T, std::function<void(T*)>>(obj, deleter);
    }

    // プールに戻す（内部使用）
    void ReleaseRaw(T* p)
    {
        if (!p) return;
        p->Reset();
        pool_.push_back(p);
    }

    ~ObjectPool()
    {
        for (T* p : pool_) delete p;
        pool_.clear();
    }

private:
    std::vector<T*> pool_;
};

