#ifndef LCLIB_CXX_DYNAMIC_ARRAY_HPP_2020_11_26_10_35_48
#define LCLIB_CXX_DYNAMIC_ARRAY_HPP_2020_11_26_10_35_48

#include <lclib-c++/Config.hpp>

#include <memory>
#include <iterator>
#include <cstddef>
#include <type_traits>
#include <initializer_list>
#include <array>
#include <algorithm>

#ifdef LCLIB_CXX_HAS_20_SPACESHIP
#include <compare>
#endif

namespace lclib::array{

    template<typename T,typename Alloc=std::allocator<T>> struct DynamicArray{
    public:
        static_assert(std::is_same_v<T,typename std::allocator_traits<Alloc>::value_type>);
        
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using allocator_type = Alloc;
        using pointer = typename std::allocator_traits<Alloc>::pointer;
        using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using difference_type = typename std::iterator_traits<iterator>::difference_type;
        using size_type = std::make_unsigned_t<difference_type>;
    private:
        pointer _m_ptr;
        size_type _m_size;
        size_type _m_constructed;
        Alloc _m_alloc;
    public:
        DynamicArray(const Alloc& alloc=Alloc()) noexcept(std::is_nothrow_copy_constructible_v<Alloc>) : _m_ptr{}, _m_size{},_m_constructed{},_m_alloc{alloc}{}
        template<std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const DynamicArray& a) : _m_size{a._m_size}, _m_ptr{}, _m_constructed{}, _m_alloc(std::allocator_traits<Alloc>::select_on_container_copy_construction(a._m_alloc)){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,a._m_size);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const DynamicArray& a,const Alloc& alloc) : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,a._m_size);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<std::enable_if_t<std::is_move_constructible_v<T>>* =nullptr> DynamicArray(DynamicArray&& a,const Alloc& alloc) : _m_size{}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,a._m_size);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,std::move(a[_m_constructed]));
            }
        }

        template<std::size_t N,std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const T(&a)[N],const Alloc& alloc=Alloc()) : _m_size{N}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,N);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<std::size_t N,std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const std::array<T,N>& a,const Alloc& alloc=Alloc()) : _m_size{N}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,N);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<std::size_t N,std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const std::array<const T,N>& a,const Alloc& alloc=Alloc()) : _m_size{N}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,N);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,a[_m_constructed]);
            }
        }

        template<std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr> DynamicArray(const std::initializer_list<T>& il,const Alloc& alloc = Alloc())  : _m_size{il.size()}, _m_ptr{}, _m_constructed{}, _m_alloc(alloc){
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,_m_size);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,il.begin()[_m_constructed]);
            }
        }

        DynamicArray(DynamicArray&& a) noexcept : _m_ptr{std::exchange(a._m_ptr,nullptr)}
            ,_m_size(std::exchange(a._m_size,0)), _m_alloc{std::move(a._m_alloc)}, _m_constructed(a._m_constructed){}



        ~DynamicArray(){
            if(_m_ptr){
                for(;_m_constructed>0;_m_constructed--)
                    std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_ptr+_m_constructed-1);
                std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_ptr,this->_m_size);
            }
        }

        reference operator[](size_type t){
            return _m_ptr[t];
        }

        const_reference operator[](size_type t)const{
            return _m_ptr[t];
        }

        size_type size()const{
            return _m_size;
        }

        pointer data(){
            return _m_ptr;
        }

        const_pointer data()const{
            return _m_ptr;
        }

        iterator begin(){
            return _m_ptr;
        }

        iterator end(){
            return _m_ptr?_m_ptr+_m_size:_m_ptr;
        }


        const_iterator begin()const{
            return _m_ptr;
        }

        const_iterator end()const{
            return _m_ptr?_m_ptr+_m_size:_m_ptr;
        }

        const_iterator cbegin()const{
            return _m_ptr;
        }

        const_iterator cend()const{
            return _m_ptr?_m_ptr+_m_size:_m_ptr;
        }

        reverse_iterator rbegin(){
            return reverse_iterator(end());
        }

        reverse_iterator rend(){
            return reverse_iterator(begin());
        }

        const_reverse_iterator rbegin()const{
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend()const{
            return reverse_iterator(begin());
        }

        const_reverse_iterator crbegin()const{
            return const_reverse_iterator(end());
        }

        const_reverse_iterator crend()const{
            return reverse_iterator(begin());
        }

        template<std::enable_if_t<std::is_copy_constructible_v<T>>* =nullptr>
        DynamicArray& operator=(const DynamicArray& arr){
            if(this==&arr)
                return *this; // No Self-assignment
            if(_m_ptr){
                for(;_m_constructed>0;_m_constructed--)
                    std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_ptr+_m_constructed-1);
                std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_ptr,this->_m_size);
                this->_m_ptr = nullptr; // Alloc::allocate can throw. which would cause a double-free
                this->_m_constructed = 0; // What's better, copy-initialization can throw, so reset the construction pointer
            }
            this->_m_size = arr.size();
            if constexpr(std::allocator_traits<Alloc>::propagate_on_container_copy_assignment::value){
                this->_m_alloc = arr._m_alloc;
            }
            this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,this->_m_size);
            for(;_m_constructed<_m_size;_m_constructed++){
                std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,arr[_m_constructed]);
            }
            return *this;
        }

        template<std::enable_if_t<
            std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value
            || std::is_move_constructible_v<T>
        >* =nullptr> 
            DynamicArray& operator=(DynamicArray&& arr) noexcept(std::allocator_traits<Alloc>::propageate_on_container_move_assignment::value){
            if constexpr(std::allocator_traits<Alloc>::propageate_on_container_move_assignment::value){
                this->~DynamicArray();
                ::new(this) DynamicArray(std::move(arr));
                return *this;
            }else{
                if(_m_ptr){
                    for(;_m_constructed>0;_m_constructed--)
                        std::allocator_traits<Alloc>::destroy(this->_m_alloc,this->_m_ptr+_m_constructed-1);
                    std::allocator_traits<Alloc>::deallocate(this->_m_alloc,this->_m_ptr,this->_m_size);
                    this->_m_ptr = nullptr; // Alloc::allocate can throw. which would cause a double-free
                    this->_m_constructed = 0; // What's better, copy-initialization can throw, so reset the construction pointer
                }
                this->_m_size = arr.size();
                this->_m_ptr = std::allocator_traits<Alloc>::allocate(this->_m_alloc,this->_m_size);
                for(;_m_constructed<_m_size;_m_constructed++){
                    std::allocator_traits<Alloc>::construct(this->_m_alloc,this->_m_ptr+_m_constructed,std::move(arr[_m_constructed]));
                }
                return *this;
            }
        }
        
        void swap(DynamicArray& arr) noexcept(std::is_nothrow_swappable_v<Alloc>||!std::allocator_traits<Alloc>::propagate_on_container_swap::value){
            using std::swap;
            if constexpr(std::allocator_traits<Alloc>::propagate_on_container_swap::value)
                swap(this->_m_alloc,arr._m_alloc);
            swap(this->_m_ptr,arr._m_ptr);
            swap(this->_m_size,arr._m_size);
            swap(this->_m_constructed,arr._m_constructed);
        }

        friend void swap(DynamicArray& a1,DynamicArray& a2) noexcept(noexcept(a1.swap(a2))){
            a1.swap(a2);
        }

        friend auto begin(DynamicArray& a)noexcept{
            return a.begin();
        }
        
        friend auto begin(const DynamicArray& a)noexcept{
            return a.begin();
        }

        friend auto end(DynamicArray& a)noexcept{
            return a.end();
        }
        
        friend auto end(const DynamicArray& a)noexcept{
            return a.end();
        }

        friend auto cbegin(const DynamicArray& a)noexcept{
            return a.cbegin();
        }

        friend auto cend(const DynamicArray& a)noexcept{
            return a.cend();
        }

        friend auto rbegin(DynamicArray& a)noexcept{
            return a.rbegin();
        }
        
        friend auto rbegin(const DynamicArray& a)noexcept{
            return a.rbegin();
        }

        friend auto rend(DynamicArray& a)noexcept{
            return a.rend();
        }
        
        friend auto rend(const DynamicArray& a)noexcept{
            return a.rend();
        }

        friend auto crbegin(const DynamicArray& a)noexcept{
            return a.crbegin();
        }

        friend auto crend(const DynamicArray& a)noexcept{
            return a.crend();
        }
    };

    template<typename T,std::void_t<decltype(std::declval<const T&>()==std::declval<const T&>())>* =nullptr>
        bool operator==(const DynamicArray<T>& a1,const DynamicArray<T>& a2) noexcept(noexcept(a1[0]==a2[0])){
            return std::equal(begin(a1),end(a1),begin(a2),end(a2));
        }

#ifdef LCLIB_CXX_HAS_20_SPACESHIP
    template<typename T,std::void_t<decltype(std::declval<const T&>()<=>std::declval<const T&>())>* =nullptr>
        auto operator<=>(const DynamicArray<T>& a1,const DynamicArray<T>& a2){
            return std::lexicographical_compare_three_way(begin(a1),end(a1),begin(a2),end(a2));
        }
#else
    template<typename T,std::void_t<decltype(std::declval<const T&>()<std::declval<const T&>())>* =nullptr>
        bool operator<(const DynamicArray<T>& a1,const DynamicArray<T>& a2) noexcept(noexcept(a1[0]<a2[0])){
            return std::lexicographical_compare(begin(a1),end(a1),begin(a2),end(a2));
        }

    template<typename T,std::void_t<decltype(std::declval<const T&>()<std::declval<const T&>())>* =nullptr>
        bool operator>(const DynamicArray<T>& a1,const DynamicArray<T>& a2) noexcept(noexcept(a1[0]<a2[0])){
            return a2<a1;
        }

    template<typename T,std::void_t<decltype(std::declval<const T&>()<std::declval<const T&>()||std::declval<const T&>()==std::declval<const T&>())>* =nullptr>
        bool operator<=(const DynamicArray<T>& a1,const DynamicArray<T>& a2) noexcept(noexcept(a1[0]<a2[0]||a1[0]==a2[0])){
            return a1<a2||a1==a2;
        }
    template<typename T,std::void_t<decltype(std::declval<const T&>()<std::declval<const T&>()||std::declval<const T&>()==std::declval<const T&>())>* =nullptr>
        bool operator>=(const DynamicArray<T>& a1,const DynamicArray<T>& a2) noexcept(noexcept(a1[0]<a2[0]||a1[0]==a2[0])){
            return a1>a2||a1==a2;
        }
    template<typename T,std::void_t<decltype(std::declval<const T&>()==std::declval<const T&>())>* =nullptr>
        bool operator!=(const DynamicArray<T>& a1,const DynamicArray<T>& a2) noexcept(noexcept(a1==a2)){
            return !(a1==a2);
        }
#endif
}

#endif