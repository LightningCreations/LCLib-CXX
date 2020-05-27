//
// Created by chorm on 2019-12-12.
//

#ifndef LCLIB_POLYMORPHIC_HPP
#define LCLIB_POLYMORPHIC_HPP

#include <cstddef>
#include <type_traits>
#include <numeric>
#include <algorithm>
#include <utility>
#include <typeinfo>

#include <lclib-c++/TypeTraits.hpp>



namespace lightningcreations::lclib::polymorphic{
    template<typename T> struct PolymorphicWrapper final{
        static_assert(std::has_virtual_destructor_v<T>,"PolymorphicWrapper Requires a polymorphic type");
        static_assert(alignof(T)<=alignof(std::max_align_t),"PolymorphicWrapper does not support over-aligned types");
    private:
        T* m_ptr;
    public:
        using type = T;
        template<typename U> using derived_type = std::enable_if_t<std::is_base_of_v<T,U>,U>;
        using can_move_value = std::false_type;

        constexpr PolymorphicWrapper() noexcept:m_ptr{}{}
        ~PolymorphicWrapper() noexcept(std::is_nothrow_destructible_v<T>){
            if(m_ptr)
                delete m_ptr;
        }
        PolymorphicWrapper(PolymorphicWrapper&& w) noexcept:m_ptr{std::exchange(w.m_ptr,nullptr)}{}
        PolymorphicWrapper(const PolymorphicWrapper&)=delete;
        template<typename U,std::enable_if_t<std::is_copy_constructible_v<U>&&std::is_base_of_v<T,U>&&(alignof(U)<=alignof(std::max_align_t))&&!lightningcreations::lclib::type_traits::is_specialization_v<PolymorphicWrapper,U>&&!lightningcreations::lclib::type_traits::is_specialization_v<std::in_place_type_t,U>>* =0>
            PolymorphicWrapper(const U& u) noexcept(std::is_nothrow_copy_constructible_v<U>)
            :m_ptr{new(std::nothrow) U{u}}{}
        template<typename U,std::enable_if_t<!(std::is_copy_constructible_v<U>&&std::is_base_of_v<T,U>&&(alignof(U)<=alignof(std::max_align_t)))&&!lightningcreations::lclib::type_traits::is_specialization_v<PolymorphicWrapper,U>&&!lightningcreations::lclib::type_traits::is_specialization_v<std::in_place_type_t,U>>* =0>
            PolymorphicWrapper(const U& u)=delete;
        template<typename U,std::enable_if_t<std::is_move_constructible_v<U>&&std::is_base_of_v<T,U>&&(alignof(U)<=alignof(std::max_align_t))&&!lightningcreations::lclib::type_traits::is_specialization_v<PolymorphicWrapper,U>&&!lightningcreations::lclib::type_traits::is_specialization_v<std::in_place_type_t,U>>* =0>
        PolymorphicWrapper(U&& u) noexcept(std::is_nothrow_move_constructible_v<U>)
                :m_ptr{new(std::nothrow) U{std::move(u)}}{}
        template<typename U,std::enable_if_t<!(std::is_move_constructible_v<U>&&std::is_base_of_v<T,U>&&(alignof(U)<=alignof(std::max_align_t)))&&!lightningcreations::lclib::type_traits::is_specialization_v<PolymorphicWrapper,U>&&!lightningcreations::lclib::type_traits::is_specialization_v<std::in_place_type_t,U>>* =0>
            PolymorphicWrapper(U&& u)=delete;
        template<typename U,std::enable_if_t<std::is_base_of_v<T,U>>* =0>
            constexpr PolymorphicWrapper(PolymorphicWrapper<U>&& w) noexcept:m_ptr{std::exchange(w.m_ptr,nullptr)}{}
        /**
         * Preforms a polymorphic (checked) upcast of a PolymorphicWrapper and moves from it.
         *  If
         * @tparam U
         * @param w
         */
        template<typename U,std::enable_if_t<std::is_base_of_v<U,T>&&!std::is_same_v<U,T>>* =0>
            explicit constexpr PolymorphicWrapper(PolymorphicWrapper<U>&& w){
                if(!w.m_ptr)
                    m_ptr = nullptr;
                else if((m_ptr = dynamic_cast<T*>(w.m_ptr)))
                    w.m_ptr = nullptr;
                else
                    throw std::bad_cast{};
            }

        template<typename U,typename... Args,std::enable_if_t<std::is_base_of_v<T,U>&&std::is_constructible_v<U,Args&&...>&&(alignof(U)<=alignof(std::max_align_t))&&!lightningcreations::lclib::type_traits::is_specialization_v<PolymorphicWrapper,U>>* = 0>
            explicit PolymorphicWrapper(std::in_place_type_t<U>,Args&&... args) noexcept(std::is_nothrow_constructible_v<U,Args&&...>)
                :m_ptr{new(std::nothrow) U(std::forward<Args>(args)...)}{}

        //These conversions are intentional clang-tidy.
        operator T&()&{
            return *m_ptr;
        }
        operator const T&()const{
            return *m_ptr;
        }
        operator T&&()&&{
            return *m_ptr;
        }

        T* operator->()noexcept{
            return m_ptr;
        }
        const T* operator->()const noexcept{
            return m_ptr;
        }

        T& operator*()&{
            return *m_ptr;
        }
        const T& operator*()const&{
            return *m_ptr;
        }
        T&& operator *()&&{
            return static_cast<T&&>(*m_ptr);
        }
        const T&& operator*()const&&{
            return static_cast<const T&&>(*m_ptr);
        }

        //So are these
        template<typename U,std::enable_if_t<std::is_base_of_v<U,T>>* = 0>
            operator U&()&{
            return *m_ptr;
        }

        template<typename U,std::enable_if_t<std::is_base_of_v<U,T>>* = 0>
            operator U&&()&&{
            return *m_ptr;
        }

        template<typename U,std::enable_if_t<std::is_base_of_v<U,T>>* = 0>
            operator const U&(){
            return *m_ptr;
        }

        template<typename U,std::enable_if_t<std::is_base_of_v<T,U>>* =0>
            explicit operator U&()&{
            return dynamic_cast<U&>(*m_ptr);
        }
        template<typename U,std::enable_if_t<std::is_base_of_v<T,U>>* =0>
            explicit operator const U&()const{
            return dynamic_cast<const U&>(*m_ptr);
        }
        template<typename U,std::enable_if_t<std::is_base_of_v<T,U>>* =0>
        explicit operator U&&()&&{
            return dynamic_cast<U&&>(*m_ptr);
        }

        template<typename U,std::enable_if_t<std::is_base_of_v<T,U>>* =0>
         U& checked_cast()&{
            return dynamic_cast<U&>(*m_ptr);
        }
        template<typename U,std::enable_if_t<std::is_base_of_v<T,U>>* =0>
        const U& checked_cast()const{
            return dynamic_cast<const U&>(*m_ptr);
        }
        template<typename U,std::enable_if_t<std::is_base_of_v<T,U>>* =0>
        U&& checked_cast()&&{
            return dynamic_cast<U&&>(*m_ptr);
        }
        template<typename U,std::enable_if_t<std::is_base_of_v<T,U>&&!std::is_same_v<T,U>>* = 0>
            bool instanceof()const noexcept{
                return dynamic_cast<U*>(m_ptr);
            }
        template<typename U,std::enable_if_t<std::is_base_of_v<U,T>>* =0>
            bool instanceof()const noexcept{
                return m_ptr; //Short circuit out a potentially expensive upcast to virtual base.
            }
    };

    template<typename T> PolymorphicWrapper(const T&)->PolymorphicWrapper<T>;
    template<typename T> PolymorphicWrapper(T&&)->PolymorphicWrapper<T>;
    template<typename T,typename... Args> explicit PolymorphicWrapper(std::in_place_type_t<T>,Args&&...)->PolymorphicWrapper<T>;

}

namespace std{
    template<typename T,typename U>
    struct common_type<lightningcreations::lclib::polymorphic::PolymorphicWrapper<T>,lightningcreations::lclib::polymorphic::PolymorphicWrapper<U>>{
        using type = std::enable_if_t<std::has_virtual_destructor_v<std::remove_pointer_t<std::common_type_t<T*,U*>>>,
                lightningcreations::lclib::polymorphic::PolymorphicWrapper<std::remove_pointer_t<std::common_type_t<T*,U*>>>>;
    };
}

#endif //LCLIB_POLYMORPHIC_HPP
