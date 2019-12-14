//
// Created by chorm on 2019-11-03.
//

#ifndef LCLIB_RANGES_HPP
#define LCLIB_RANGES_HPP

#include <lclib-c++/TypeTraits.hpp>
#include <limits>
#include <utility>
#include <iterator>

namespace lightningcreations::lclib::ranges{
    template<typename T> struct numeric_range{
        static_assert(std::is_trivially_copyable_v<T>,"T must be trivially copyable");
        static_assert(std::numeric_limits<T>::is_integer(),"T must satisfy IntegerType");
        using difference_type = type_traits::conditional_substitute_t<std::is_unsigned_v<T>,std::make_signed_t,type_traits::type_identity_t,std::conditional_t<std::numeric_limits<T>::is_signed(),T,std::ptrdiff_t>>;

    private:
        T start;
        T _end;
    public:
        struct iterator{
        private:
            T val;
        public:
            using value_type = T;
            using reference = T;
            using pointer = void;
            using difference_type = numeric_range::difference_type;
            using iterator_category = std::random_access_iterator_tag;

            constexpr iterator(T val)noexcept(std::is_nothrow_copy_constructible_v<T>):val{val}{}

            constexpr T operator*()const noexcept(std::is_nothrow_copy_constructible_v<T>){
                return val;
            }
            constexpr iterator operator++(int) noexcept(noexcept(val++)){
                return iterator{val++};
            }
            constexpr iterator& operator++() noexcept(noexcept(++val)){
                ++val;
                return *this;
            }
            constexpr iterator operator--(int) noexcept(noexcept(val--)){
                return iterator{val--};
            }
            constexpr iterator& operator--() noexcept(noexcept(--val)){
                --val;
                return *this;
            }
            constexpr iterator operator+(difference_type n)const noexcept(noexcept(val+n)){
                return iterator{val+n};
            }
            constexpr iterator& operator+=(difference_type n)const noexcept(noexcept(val+=n)){
                val+=n;
                return *this;
            }
            constexpr iterator operator-(difference_type n)const noexcept(noexcept(val-n)){
                return iterator{val-n};
            }
            constexpr iterator& operator-=(difference_type n) noexcept(noexcept(val-=n)){
                val-=n;
                return *this;
            }
            constexpr reference operator[](difference_type idx)const noexcept(val+idx){
                return val+idx;
            }

            constexpr difference_type operator-(const iterator& it)const noexcept(val-it.val){
                return val-it.val;
            }
        };

        constexpr friend bool operator==(const iterator& it1,const iterator& it2)noexcept(it1.val==it2.val){
            return it1.val==it2.val;
        }

        constexpr friend bool operator!=(const iterator& it1,const iterator& it2)noexcept(it1.val!=it2.val){
            return it1.val!=it2.val;
        }

        constexpr friend bool operator<(const iterator& it1,const iterator& it2)noexcept(it1.val<it2.val){
            return it1.val<it2.val;
        }

        constexpr friend bool operator<=(const iterator& it1,const iterator& it2)noexcept(it1.val<=it2.val){
            return it1.val<=it2.val;
        }
        constexpr friend bool operator>(const iterator& it1,const iterator& it2)noexcept(it1.val>it2.val){
            return it1.val>it2.val;
        }

        constexpr friend bool operator>=(const iterator& it1,const iterator& it2)noexcept(it1.val>=it2.val){
            return it1.val>=it2.val;
        }

        using const_iterator = iterator;

        constexpr numeric_range():start{},_end{std::numeric_limits<T>::max()}{}
        constexpr numeric_range(T end):start{},_end{end}{}
        constexpr numeric_range(T begin,T end):start{begin},_end{end}{}

        template<typename U,U Start,typename S,S End,
            std::enable_if_t<std::is_convertible_v<U,T>&&type_traits::is_list_constructible_v<T,U>&&std::is_convertible_v<U,T>&&type_traits::is_list_constructible_v<T,U>>* =0>
        constexpr numeric_range(std::integral_constant<U,Start>,std::integral_constant<S,End>)
            noexcept(std::is_nothrow_constructible_v<T,U>&&std::is_nothrow_constructible_v<T,S>):start{Start},_end{End}{}
        template<typename U,U Start,typename S,S End,
            std::enable_if_t<std::is_constructible_v<T,U>&&std::is_constructible_v<T,S>&&!(std::is_convertible_v<U,T>&&type_traits::is_list_constructible_v<T,U>&&std::is_convertible_v<U,T>&&type_traits::is_list_constructible_v<T,U>)>* =0>
        constexpr explicit numeric_range(std::integral_constant<U,Start>,std::integral_constant<S,End>)
            noexcept(std::is_nothrow_constructible_v<T,U>&&std::is_nothrow_constructible_v<T,S>):start{Start},_end{End}{}

        template<typename U,U End,typename=std::enable_if_t<std::is_constructible_v<T,U>>>
            constexpr explicit numeric_range(std::make_integer_sequence<U,End>):start{},_end{}{}

        iterator begin()const{
            return iterator{start};
        }
        iterator end()const{
            return iterator{_end};
        }
        iterator cbegin()const{
            return iterator{start};
        }
        iterator cend()const{
            return iterator{_end};
        }
    };
    template<typename T,T Start,T End> numeric_range(std::integral_constant<T,Start>,std::integral_constant<T,End>) -> numeric_range<T>;
    template<typename S,typename U,S Start,U End> numeric_range(std::integral_constant<S,Start>,std::integral_constant<U,End>) -> numeric_range<std::common_type_t<S,U>>;
    template<typename T> numeric_range(T,T) -> numeric_range<T>;
    template<typename S,typename U> numeric_range(S,U)->numeric_range<std::common_type_t<S,U>>;
    template<typename T> numeric_range(T) -> numeric_range<T>;
    numeric_range() -> numeric_range<int>;
}

#endif //LCLIB_RANGES_HPP
